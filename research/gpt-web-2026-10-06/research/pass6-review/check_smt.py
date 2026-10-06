import ctypes,json,pathlib
p=pathlib.Path('/workspace/scratch/3ba0fff8d310/otl-restore-20261006/incoming-pass6/OpenTorchlight_pass6/results/loops')
z=ctypes.CDLL('/lib/x86_64-linux-gnu/libz3.so.4')
z.Z3_mk_config.restype=ctypes.c_void_p
z.Z3_mk_context.argtypes=[ctypes.c_void_p];z.Z3_mk_context.restype=ctypes.c_void_p
z.Z3_del_config.argtypes=[ctypes.c_void_p];z.Z3_del_context.argtypes=[ctypes.c_void_p]
z.Z3_eval_smtlib2_string.argtypes=[ctypes.c_void_p,ctypes.c_char_p];z.Z3_eval_smtlib2_string.restype=ctypes.c_char_p
z.Z3_get_full_version.restype=ctypes.c_char_p
out={'z3_version':z.Z3_get_full_version().decode(),'checks':[]}
expected={r['name']:r['expected'] for r in json.loads((p/'loop-results.json').read_text())['obligations']}
for f in sorted(p.glob('*.smt2')):
 c=z.Z3_mk_config();ctx=z.Z3_mk_context(c);z.Z3_del_config(c)
 try: result=z.Z3_eval_smtlib2_string(ctx,f.read_bytes()).decode().strip()
 finally:z.Z3_del_context(ctx)
 out['checks'].append({'name':f.stem,'expected':expected[f.stem],'actual':result})
 assert result==expected[f.stem]
print(json.dumps(out,indent=2))
