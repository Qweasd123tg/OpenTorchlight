# Correct read-induced trial-cache invalidation

The incoming resource audit identified full stat_result comparison in StaticInputs.
Independently reproduced on this host using an unchanged temporary header: only
st_atime_ns changed during hashing, but the original guard returned no token.
This was conservative false invalidation, not acceptance of incorrect code.

Compare device, inode, mode, link count, uid/gid, size, nanosecond mtime and ctime;
exclude access time. Continue hashing full contents, checking directory membership
and rejecting volatile source macros. Include each resolved target path in the
version-two key and check it again after hashing, so symlink retargeting with
identical bytes remains visible. No persistent acceptance receipt is cached.

Nine new regression tests cover cold access, each protected metadata field,
same-size edits with restored mtime, inode replacement, symlink retargeting both
between and during calls, and additions/deletions during hashing. The existing
trial memo/corruption coverage is retained. Final Python suite: 599 tests OK,
one skip. Combined current-tree game check: 202 tests pass with unchanged prior
acceptances plus the separately documented five recovered StatsMenuFill entries.

The narrow fix was written locally; neither script from the supplied audit archive
was executed. The first isolated Python harness attempt used stdin (incompatible
with spawn-based tests); a file runner and the pinned environment corrected the
harness. No failed or environment-blocked run was counted as validation.

This does not make the optional whole-snapshot TrialMemo cheap or enable it by
default. It does not change the compiler, comparison rules, resource-slot policy,
final evidence scope, or runtime test caching. No end-to-end speedup percentage
is claimed. Common immutable manifests and host-wide backend reuse require
separate correctness and performance validation.

Audit source: https://drive.google.com/file/d/1f8P5xtEmpxrSF6xVGNIZ0Ns6GcT9DvSM/view
Archive SHA256: c21544d548878ff73f729963097ebfe7f3de9653feb07dd110640501ac2c4ab8
