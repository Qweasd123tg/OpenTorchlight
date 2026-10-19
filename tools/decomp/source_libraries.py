"""Pinned upstream C inputs and original recovery targets, never decomp wrappers.

Library classification is independent of the fixed original target set. Source
availability creates no acceptance: only actual emitted production objects can
bind completed call-pair receipts, through the ordinary acceptance policy.
"""
from pathlib import Path
import hashlib
import json

ORIGINAL = '91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b'
COMMIT = '3b3a1ef38db579210074b9c3cea98fdc67d0a2f6'
TARGET_SET_SHA256 = '89450d597eee22d268e821ffc387a16dac8d1f05c003ac0536f65544f537032a'
WRITTEN = {'function', 'ctor', 'dtor', 'static'}

def digest(data):
    return hashlib.sha256(data).hexdigest()

def inside(base, relative):
    relative = Path(relative)
    path = base / relative
    if relative.is_absolute() or '..' in relative.parts or not path.resolve().is_relative_to(base.resolve()):
        raise ValueError('redirected source-library input: ' + str(relative))
    return path

def read_json(path, expected=None):
    raw = path.read_bytes()
    if expected is not None and digest(raw) != expected:
        raise ValueError('source-library input hash differs: ' + str(path))
    return json.loads(raw)

def target_functions(root, db):
    path = Path(root) / 'decomp/recovery-targets.json'
    if not path.exists():
        game = {t['id'] for t in db['tus'] if t['kind'] == 'game'}
        return [f for f in db['functions'].values() if f['tu'] in game and f['kind'] in WRITTEN]
    saved = read_json(path)
    addresses = saved.get('addresses', [])
    if (saved.get('schema') != 1 or saved.get('original_elf_sha256') != ORIGINAL
            or db.get('original_elf_sha256') != ORIGINAL or len(addresses) != 5247
            or addresses != sorted(set(addresses), key=lambda a:int(a,16))
            or any(a not in db['functions'] or db['functions'][a]['kind'] not in WRITTEN for a in addresses)):
        raise ValueError('original recovery target set changed or invalid')
    if (saved.get('addresses_sha256') != TARGET_SET_SHA256
            or digest('\n'.join(addresses).encode()) != TARGET_SET_SHA256):
        raise ValueError('recovery target ledger digest differs')
    return [db['functions'][a] for a in addresses]

def load(root, db, image):
    root = Path(root)
    config_path=root/'decomp/config.json'
    if not config_path.exists():
        return []
    cfg = read_json(config_path)
    result = []
    for name in cfg.get('source_libraries', []):
        specpath = inside(root, name)
        if not specpath.is_relative_to(root / 'decomp/source-libraries'):
            raise ValueError('source-library spec must be a staged decomp input')
        spec = read_json(specpath)
        if (spec.get('schema') != 1 or spec.get('name') != 'fltk-1.3.0'
                or spec.get('commit') != COMMIT or spec.get('original_elf_sha256') != ORIGINAL
                or db.get('original_elf_sha256') != ORIGINAL or image.sha256 != ORIGINAL):
            raise ValueError('unreviewed source-library identity')
        vendor = root / 'third_party/fltk-1.3.0'
        provenance = read_json(inside(vendor, 'source-inputs.json'), spec['provenance_sha256'])
        if provenance.get('commit') != COMMIT or len(provenance.get('files', {})) != 230:
            raise ValueError('source-library provenance differs')
        files = {}
        for relative, expected in provenance['files'].items():
            path = inside(vendor, relative)
            raw = path.read_bytes()
            if digest(raw) != expected:
                raise ValueError('upstream source/header differs: ' + relative)
            files[str(path.relative_to(root))] = expected
        proofpath = inside(root, spec['native_proof'])
        proof = read_json(proofpath, spec['native_proof_sha256'])
        if proof.get('original_elf_sha256') != ORIGINAL or len(proof['functions']) != 34 or len(proof['local_data']) != 36:
            raise ValueError('source-library native proof differs')
        targets = {f['address'] for f in target_functions(root, db)}
        for pin in proof['functions']:
            f = db['functions'].get(pin['address'])
            if (not f or f['address'] not in targets or f['names'] != [pin['name']]
                    or f['size'] != pin['size'] or f['tu'] != pin['owner_id']
                    or digest(image.read(int(pin['address'],16), pin['size'])) != pin['sha256']):
                raise ValueError('source-library function identity/ownership differs: ' + pin['address'])
        for pin in proof['local_data']:
            syms = [s for s in image.symbols if s.name == pin['name'] and s.file == pin['owner']]
            if (len(syms) != 1 or syms[0].type != 1 or syms[0].bind != 0
                    or not syms[0].defined or syms[0].value != int(pin['address'],16)
                    or syms[0].size != pin['size'] or image.sections[syms[0].shndx].name != pin['section']
                    or digest(image.read(syms[0].value, syms[0].size)) != pin['sha256']):
                raise ValueError('source-library local data identity differs: ' + pin['name'])
        platform = inside(root, spec['platform_header'])
        if digest(platform.read_bytes()) != spec['platform_header_sha256']:
            raise ValueError('source-library platform config differs')
        sources = []
        for relative in spec['sources']:
            if relative not in provenance['files'] or not relative.endswith('.c'):
                raise ValueError('unreviewed C production source: ' + relative)
            source = inside(vendor, relative)
            tus = [t for t in db['tus'] if t['name'] == source.name]
            if len(tus) != 1 or tus[0]['id'] not in proof['tu_ids'].values():
                raise ValueError('C production source has no exact native TU')
            sources.append((source, ('-x', 'c', '-std=gnu99', '-fno-inline', '-I', str(platform.parent))))
        if len(sources) != 4 or len({s for s, _ in sources}) != 4:
            raise ValueError('source-library requires its four upstream C units')
        result.append(dict(spec=spec, specpath=specpath, provenance=provenance,
                           files=files, proof=proof, sources=sources))
    return result

def production_sources(root, db, image):
    return [entry for library in load(root, db, image) for entry in library['sources']]

def comparison_units(root, db, image, out):
    """Bind only actual emitted production definitions to complete object bytes."""
    libraries=load(root,db,image)
    if not libraries:
        return []
    out = Path(out)
    manifest = read_json(out / 'manifest.json')
    if manifest.get('original_elf_sha256') != db['original_elf_sha256']:
        raise ValueError('source-library build belongs to another original')
    entries = {(row['original'], row['symbol']) for row in manifest['comparison_only']}
    units = []
    residual = manifest['standalone_residual']
    for library in libraries:
        for source, flags in library['sources']:
            relative = str(source.relative_to(root))
            if (residual['source_sha256'].get(relative) != digest(source.read_bytes())
                    or residual['library_source_compile_flags'].get(relative) != list(flags)
                    or residual['original_data_redirects'].get(relative)
                    or residual['original_initializers_omitted'].get(relative)
                    or any(h['unit'] == relative for h in manifest['hooks'])):
                raise ValueError('source-library production identity or native isolation differs')
            obj = out / (source.stem + '.o')
            objhash = digest(obj.read_bytes())
            if residual['production_object_sha256'].get(relative) != objhash:
                raise ValueError('source-library complete production object differs')
            rows = []
            for pin in library['proof']['functions']:
                if pin['owner'] != source.name:
                    continue
                f = db['functions'][pin['address']]
                local = dict(zip(f['names'], f['bind'])).get(pin['name']) == 'local'
                symbol = '__tlhybrid_local_%s_%s' % (f['tu'], pin['name']) if local else pin['name']
                if (f['address'], symbol) not in entries:
                    raise ValueError('upstream production definition was not emitted: ' + pin['name'])
                rows.append(dict(address=f['address'],name=pin['name'],status='DIFF',weak=False,
                                 original_size=f['size'],object_digest=objhash))
            units.append(dict(source=str(source),tu=source.name,object_digest=objhash,
                              source_library=library['spec']['name'],functions=rows,unknown=[]))
    return units

def select(root, db, image, tu, addresses=(), limit=16, max_size=4096):
    libraries = load(root, db, image)
    matches = [(library, source) for library in libraries for source, _ in library['sources'] if source.name == tu]
    if len(matches) != 1 or Path(tu).name != tu:
        raise ValueError('expected one configured upstream source TU')
    library, source = matches[0]
    functions = [db['functions'][pin['address']] for pin in library['proof']['functions'] if pin['owner'] == tu]
    names = {name:f for f in functions for name in [f['address'], *f['names']]}
    if addresses:
        try:
            functions = list({names[a]['address']:names[a] for a in addresses}.values())
        except KeyError as exc:
            raise ValueError('address is outside the owning upstream source: ' + str(exc)) from exc
    import acceptance
    already_compared=acceptance.prior_compared(root,db)
    if addresses and any(f['address'] in already_compared for f in functions):
        raise ValueError('source-library target already has accepted comparison evidence')
    functions = sorted((f for f in functions if f['address'] not in already_compared), key=lambda f:int(f['address'],16))
    if not functions or len(functions) > limit or any(f['size'] > max_size for f in functions):
        raise ValueError('source-library selection exceeds explicit count/size bounds')
    return library, source, functions

def prepare(root, db, image, args, asm):
    """Source-only packet branch of llm_loop --prepare-only; no model or build.

    No C++ declaration/context exemption is installed. All upstream files are
    immutable referenced artifacts with checked hashes, full owning C source and
    original ASM are included; mandatory packet overflow blocks preparation.
    """
    from types import SimpleNamespace
    root = Path(root)
    library, source, functions = select(root, db, image, args.tu, args.address, args.limit, args.max_size)
    metadata = read_json(root / 'stage.json')
    canonical = Path(metadata['root']).resolve()
    if (metadata.get('schema') != 1 or not isinstance(metadata.get('baseline'),dict)
            or root.absolute() != root.resolve() or root.parent != (canonical/'build-decomp/attempts').resolve()):
        raise ValueError('source-library Stage metadata/path differs')
    work = root/'build-decomp/llm-loop'/args.tu
    prompts = work/'prompts'
    prompts.mkdir(parents=True,exist_ok=True)
    for path in (work,prompts,root/'decomp/hybrid/tests'):
        if path.absolute() != path.resolve():
            raise ValueError('redirected source-library handoff artifact')
    if (work/'checkpoint.json').exists():
        raise ValueError('source-library attempt already prepared; prepare a fresh attempt')
    status, blockers, packets = {}, [], []
    artifact_rows = [dict(path=str(root/name),sha256=value) for name,value in sorted(library['files'].items())]
    source_raw=source.read_bytes()
    if digest(source_raw)!=library['files'][str(source.relative_to(root))]:
        raise ValueError('upstream owning source changed during preparation')
    payload = dict(source_library=library['spec'],upstream_artifacts=artifact_rows,
                   native_ownership_proof=library['proof'],acceptance_credit=0)
    (work/'library-inputs.json').write_text(json.dumps(payload,indent=2))
    artifact = work/'library-inputs.json'
    for f in functions:
        text = ('Authentic upstream C source packet; do not decompile or modify the vendor source.\n'
                'Add production differential fixtures only. Ready denotes source availability, not acceptance.\n'
                'All dependencies are explicit hash-checked artifacts in library-inputs.json; no host SDK.\n'
                'The original fixed target set remains 5247 addresses.\n\n'
                + json.dumps(dict(function=f,source_sha256=digest(source_raw),
                                  source=str(source),inputs_artifact=str(artifact),
                                  inputs_artifact_sha256=digest(artifact.read_bytes())),indent=2)
                + '\n\nOriginal native ASM:\n```asm\n'+asm(f)+'\n```\n\n'
                + 'Full untouched upstream owning source:\n```c\n'+source_raw.decode()+'\n```\n')
        if len(text) > args.max_prompt_chars:
            status[f['address']]='blocked'
            blockers.append(f['address']+': complete source packet exceeds --max-prompt-chars; no truncation')
            continue
        prompt = prompts/(f['address']+'.md')
        prompt.write_text(text)
        if prompt.absolute()!=prompt.resolve() or not prompt.stat().st_size:
            raise ValueError('invalid source-library prompt artifact')
        packets.append(dict(address=f['address'],prompt=str(prompt),sha256=digest(prompt.read_bytes())))
    checkpoint = work/'checkpoint.json'
    checkpoint.write_text(json.dumps(dict(schema=1,mode='authentic-source-library',
        settings=dict(tu=args.tu,selected=functions,max_prompt_chars=args.max_prompt_chars),
        existing=source_raw.decode(),accepted={},round=0,status=status,
        inputs_artifact_sha256=digest(artifact.read_bytes()),
        upstream_source_sha256=digest(source_raw)),indent=2))
    # Recheck borrowed immutable vendor bytes before reporting a ready handoff.
    load(root,db,image)
    result = work/'result.json'
    handoff = dict(schema=1,status='blocked' if blockers else 'ready',blockers=blockers,
        attempt=str(root),cwd=str(canonical),targets=packets,existing_addresses=[],staged_implemented_addresses=[],
        checkpoint=str(checkpoint),prepared_checkpoint_sha256=digest(checkpoint.read_bytes()),
        stage_metadata_sha256=digest((root/'stage.json').read_bytes()),cycle_argv_template=None,
        owner_environment='OTL_OWNER must match decomp/owners.json',acceptance_credit=0,
        source_library_inputs=str(artifact),source_library_inputs_sha256=digest(artifact.read_bytes()),
        submission=dict(kind='authentic_source_library',source=str(source),prepared_source_exists=True,
            prepared_source_sha256=digest(source_raw),preserve_existing_definitions=True,
            fixtures_directory=str(root/'decomp/hybrid/tests'),allowed_edits='fixtures only; immutable upstream source',
            headers_or_tools_changes='prepare_new_attempt',
            validation='canonical production hybrid comparisons and complete-object receipts; not C++ candidate.py'))
    result.write_text(json.dumps(dict(prepared=True,status=status,external_handoff=handoff,published=[],
        existing=[],artifacts=dict(stage=str(root),work=str(work),source=str(source),
                                   prompts=str(prompts),checkpoint=str(checkpoint))),indent=2))
    return SimpleNamespace(work=work,status=status,accepted={})
