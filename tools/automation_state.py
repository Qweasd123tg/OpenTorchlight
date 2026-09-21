"""Content identity shared by local automation. No network or model calls."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import subprocess


def git(root: Path, *args: str) -> bytes:
    result = subprocess.run(["git", "-C", str(root), *args], capture_output=True)
    if result.returncode:
        raise ValueError(result.stderr.decode(errors="replace").strip())
    return result.stdout


def source_snapshot(root: Path) -> dict:
    """Hash tracked + nonignored untracked files, including dirty/deleted files.

    Git is only the file enumerator: HEAD alone cannot identify a dirty checkout.
    Symlinks are hashed as links, never followed to external game inputs.
    Generated output must be outside the source set (ignored build dir or /tmp).
    """
    names = git(root, "ls-files", "-z", "--cached", "--others", "--exclude-standard")
    files = {}
    for name in sorted(set(os.fsdecode(n) for n in names.split(b"\0") if n)):
        path = root / name
        if path.is_symlink():
            data = os.fsencode(os.readlink(path))
            mode = "symlink"
        elif path.is_file():
            data = path.read_bytes()
            mode = "executable" if path.stat().st_mode & 0o111 else "file"
        elif not path.exists():
            files[name] = {"kind": "missing"}
            continue
        else:
            raise ValueError(f"Unsupported source entry (e.g. submodule): {name}")
        files[name] = {"kind": mode, "sha256": hashlib.sha256(data).hexdigest()}
    payload = json.dumps(files, sort_keys=True, ensure_ascii=True).encode()
    return {"schema": 1, "head": git(root, "rev-parse", "HEAD").decode().strip(),
            "sha256": hashlib.sha256(payload).hexdigest(), "files": files}


def changed_paths(root: Path, revision: str) -> list[str]:
    # Resolve to a commit first; no revision ranges or option injection.
    commit = git(root, "rev-parse", "--verify", "--end-of-options",
                 revision + "^{commit}").decode().strip()
    tracked = git(root, "diff", "--name-only", "--no-renames", "-z", commit, "--")
    others = git(root, "ls-files", "--others", "--exclude-standard", "-z")
    return sorted(set(os.fsdecode(n) for n in (tracked + others).split(b"\0") if n))


def snapshot_changes(previous: dict, current: dict) -> list[str]:
    """A saved full-run snapshot is useful while the checkout remains dirty."""
    old, new = previous["files"], current["files"]
    return sorted(path for path in old.keys() | new.keys() if old.get(path) != new.get(path))


def validate_output(root: Path, path: Path, protected: list[Path] = (), *, directory: bool = False) -> None:
    """Reports/build outputs cannot overwrite sources or external input trees."""
    resolved = path.resolve()
    for item in protected:
        if resolved == item.resolve() or resolved.is_relative_to(item.resolve()):
            raise ValueError(f"Output overlaps read-only input: {path}")
    if resolved == root.resolve() or root.resolve().is_relative_to(resolved):
        raise ValueError(f"Output cannot contain the source tree: {path}")
    if resolved.is_relative_to(root.resolve()):
        relative = str(resolved.relative_to(root.resolve()))
        tracked = git(root, "ls-files", "-z", "--", relative).strip(b"\0")
        ignored = subprocess.run(["git", "-C", str(root), "check-ignore", "-q", "--",
                                  relative + "/" if directory else relative])
        if tracked or ignored.returncode:
            raise ValueError(f"Output inside repository must be ignored, not source: {path}")


def write_json(path: Path, value: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    # Same-directory atomic publication. Avoid fixed temporary paths/symlinks.
    import tempfile
    with tempfile.NamedTemporaryFile(mode="w", encoding="utf-8", dir=path.parent,
                                     prefix=path.name + ".", delete=False) as stream:
        temporary = Path(stream.name)
        json.dump(value, stream, indent=2, ensure_ascii=False)
        stream.write("\n")
    temporary.replace(path)
