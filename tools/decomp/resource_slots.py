"""Host-wide limits for compiler and headless game subprocesses.

All worktrees use the same cache directory. flock releases a slot after a
worker crash; changing capacity is allowed only while the pool is idle.
"""
from contextlib import contextmanager
import fcntl
import json
import math
import os
from pathlib import Path
import time


POOLS = {"compiler": "OTL_COMPILER_SLOTS", "selftest": "OTL_SELFTEST_SLOTS"}


def directory():
    base = Path(os.environ.get("OTL_DECOMP_CACHE", Path.home() / ".cache/opentorchlight/decomp"))
    return base / "resource-slots"


def _positive(value):
    value = int(value)
    if not 1 <= value <= 64:
        raise ValueError("resource capacity must be between 1 and 64")
    return value


@contextmanager
def _policy(name, root):
    if name not in POOLS:
        raise ValueError("unknown resource pool: " + name)
    pool = Path(root or directory()) / name
    pool.mkdir(parents=True, exist_ok=True)
    with (pool / "policy.lock").open("a+") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        try:
            yield pool
        finally:
            fcntl.flock(lock, fcntl.LOCK_UN)


def _capacity(pool, name, requested=None):
    if requested is None and POOLS[name] in os.environ:
        requested = _positive(os.environ[POOLS[name]])
    if requested is not None:
        requested = _positive(requested)
    path = pool / "capacity.json"
    if path.exists():
        data = json.loads(path.read_text())
        if data.get("schema") != 1:
            raise ValueError("unsupported resource pool policy")
        count = _positive(data["slots"])
        if requested is not None and requested != count:
            raise ValueError("resource pool %s already has %d slots; configure it while idle" % (name, count))
        return count
    count = requested or min(2, os.cpu_count() or 1)
    path.write_text(json.dumps({"schema": 1, "slots": count}) + "\n")
    return count


def _try_lock(path):
    stream = path.open("a+")
    try:
        fcntl.flock(stream, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except BlockingIOError:
        stream.close()
        return None
    return stream


@contextmanager
def slot(name, *, slots=None, root=None, timeout=None):
    """Acquire one shared subprocess slot; time waiting is not execution time."""
    timeout = float(os.environ.get("OTL_SLOT_TIMEOUT", "1800")) if timeout is None else float(timeout)
    if not math.isfinite(timeout) or timeout < 0:
        raise ValueError("slot timeout must be finite and nonnegative")
    started = time.monotonic()
    stream = None
    while stream is None:
        with _policy(name, root) as pool:
            count = _capacity(pool, name, slots)
            for index in range(count):
                stream = _try_lock(pool / (str(index) + ".lock"))
                if stream is not None:
                    break
        if stream is None:
            if time.monotonic() - started >= timeout:
                raise RuntimeError("timed out waiting for a %s resource slot" % name)
            time.sleep(min(0.05, max(0, timeout - (time.monotonic() - started))))
    try:
        yield
    finally:
        stream.close()


def configure(name, count, *, root=None):
    """Resize an idle pool, never create a second capacity for existing workers."""
    count = _positive(count)
    held = []
    with _policy(name, root) as pool:
        path = pool / "capacity.json"
        old = _positive(json.loads(path.read_text())["slots"]) if path.exists() else count
        try:
            for index in range(max(count, old)):
                stream = _try_lock(pool / (str(index) + ".lock"))
                if stream is None:
                    raise RuntimeError("cannot resize active resource pool: " + name)
                held.append(stream)
            temporary = pool / "capacity.json.tmp"
            temporary.write_text(json.dumps({"schema": 1, "slots": count}) + "\n")
            os.replace(temporary, path)
        finally:
            for stream in held:
                stream.close()
    return count


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("pool", choices=tuple(POOLS))
    parser.add_argument("slots", type=int)
    args = parser.parse_args()
    print("%s: %d host-wide slots" % (args.pool, configure(args.pool, args.slots)))
