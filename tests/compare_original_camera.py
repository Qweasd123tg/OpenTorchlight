#!/usr/bin/env python3
"""CPU-only differential camera tests; never launch Torchlight's main()."""
import argparse
import ctypes as c
import hashlib
import json
import math
import os
from pathlib import Path
import random
import subprocess
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from camera_reference import OriginalCamera

OGRE_SHA256 = "bef109bfdc1210ede92731ead4a2b3fae76a8905f10bac14d5fdb54ae5474c31"
FloatPtr = c.POINTER(c.c_float)


def bind(lib, name, args):
    fn = getattr(lib, name)
    fn.restype = c.c_bool
    fn.argtypes = args
    return fn


def floats(values):
    return (c.c_float * len(values))(*values)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    parser.add_argument("--library", type=Path, required=True)
    parser.add_argument("--ogre-reference", type=Path, required=True)
    parser.add_argument("--scene-dump", type=Path, required=True)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    ogre_path = args.original.parent / "lib64/libOgreMain-1.6.5.so"
    if hashlib.sha256(ogre_path.read_bytes()).hexdigest() != OGRE_SHA256:
        raise ValueError("Unsupported original OGRE build")
    # Resolve original OgreMain's private dependencies in a fresh process.
    if os.environ.get("TORCHLIGHT_CAMERA_REFERENCE_CHILD") != str(ogre_path.resolve()):
        env = dict(os.environ)
        env["TORCHLIGHT_CAMERA_REFERENCE_CHILD"] = str(ogre_path.resolve())
        env["LD_LIBRARY_PATH"] = str(ogre_path.parent.resolve())
        os.execve(sys.executable, [sys.executable, *sys.argv], env)
    recovered = c.CDLL(str(args.library.resolve()))
    reference = c.CDLL(str(args.ogre_reference.resolve()))
    game = bind(recovered, "recovered_game_camera",
                [FloatPtr, c.c_float, c.c_bool, c.c_float, FloatPtr, FloatPtr])
    projection_args = [FloatPtr, FloatPtr, c.c_float, c.c_float, c.c_float,
                       c.c_float, FloatPtr, FloatPtr]
    projection = bind(recovered, "recovered_camera_projection", projection_args)
    ground = bind(recovered, "recovered_camera_ground",
                  [FloatPtr, FloatPtr, *([c.c_float] * 5), FloatPtr])
    open_reference = bind(reference, "reference_open", [c.c_char_p, c.c_char_p])
    original_projection = bind(reference, "reference_camera", projection_args)
    original_ground = bind(reference, "reference_ground", [*([c.c_float] * 3), FloatPtr])
    reference.reference_close.argtypes = []
    reference.reference_close.restype = None
    rng = random.Random(0xCA4E)
    maximum_errors = {}

    def compare(label, actual, expected, absolute=0.00015, relative=0.00001):
        error = max(abs(a - b) for a, b in zip(actual, expected))
        maximum_errors[label] = max(error, maximum_errors.get(label, 0))
        for a, b in zip(actual, expected):
            if not math.isfinite(a) or not math.isfinite(b) or not math.isclose(
                    a, b, abs_tol=absolute, rel_tol=relative):
                raise AssertionError(f"{label}: {list(actual)} != {list(expected)}")

    fixtures = []
    counts = {"controller": 0, "projection": 0, "ground_rays": 0, "scene_nodes": 0}
    landmarks = []
    with tempfile.TemporaryDirectory(prefix="torchlight-camera-") as temporary:
        if not open_reference(os.fsencode(ogre_path.resolve()),
                              os.fsencode(Path(temporary) / "ogre.log")):
            raise RuntimeError("Cannot initialize headless OGRE reference")
        try:
            with OriginalCamera(args.original) as original:
                # Explicit endpoints and normal/Netbook mode precede varied targets,
                # dolly and distance multipliers. First-update and settled normal
                # camera geometry are equivalent with an empty previous offset.
                cases = [(d, n, 1.0) for d in (14.0, 20.0, 24.795, 28.5) for n in (False, True)]
                cases += [(rng.uniform(14, 40), bool(rng.getrandbits(1)),
                           rng.uniform(0.75, 1.5)) for _ in range(1000)]
                for index, (dolly, netbook, multiplier) in enumerate(cases):
                    target = floats([rng.uniform(-100, 100), rng.uniform(-5, 5),
                                     rng.uniform(-100, 100)])
                    expected = original.sample(target, dolly, netbook, multiplier)
                    position, look_at = floats([0] * 3), floats([0] * 3)
                    if not game(target, dolly, netbook, multiplier, position, look_at):
                        raise AssertionError("Recovered game camera rejected valid input")
                    compare("camera_position", position, expected["position"])
                    compare("camera_target", look_at, expected["target"])
                    counts["controller"] += 1
                    aspect, fov = rng.choice((4 / 3, 16 / 9, 9 / 16, 21 / 9)), rng.choice((35, 45, 60))
                    near_clip, far_clip = rng.choice((0.1, 0.5, 1.0)), rng.choice((100, 500, 1000))
                    actual_view, actual_projection = floats([0] * 16), floats([0] * 16)
                    expected_view, expected_projection = floats([0] * 16), floats([0] * 16)
                    if not projection(position, look_at, aspect, fov, near_clip, far_clip,
                                      actual_view, actual_projection):
                        raise AssertionError("Recovered projection failed")
                    if not original_projection(position, look_at, aspect, math.radians(fov),
                                               near_clip, far_clip, expected_view, expected_projection):
                        raise AssertionError("Original OGRE projection failed")
                    compare("view_matrix", actual_view, expected_view)
                    compare("projection_matrix", actual_projection, expected_projection)
                    counts["projection"] += 1
                    for x, y in ((0, 0), (-0.5, 0), (0.5, 0), (0, -0.25), (0, 0.25)):
                        actual, expected_ground = floats([0] * 3), floats([0] * 3)
                        if not ground(position, look_at, aspect, fov, x, y, target[1], actual):
                            raise AssertionError("Recovered ground ray failed")
                        if not original_ground((x + 1) / 2, (1 - y) / 2, target[1], expected_ground):
                            raise AssertionError("Original OGRE ground ray failed")
                        # OGRE unprojects two points through a float inverse matrix;
                        # it loses precision for small near planes far from origin.
                        compare("ground_ray", actual, expected_ground, absolute=0.03)
                        def ndc(point):
                            eye = [sum(expected_view[r * 4 + k] * point[k] for k in range(3)) +
                                   expected_view[r * 4 + 3] for r in range(3)]
                            return [eye[0] * expected_projection[0] / -eye[2],
                                    eye[1] * expected_projection[5] / -eye[2]]
                        compare("ground_ray_ndc", ndc(expected_ground), [x, y],
                                absolute=0.001, relative=0)
                        counts["ground_rays"] += 1
                    if index < 8:
                        fixtures.append({"input_target": list(target), "dolly": dolly,
                            "netbook": netbook, "original": expected, "view": list(expected_view),
                            "projection": list(expected_projection), "aspect": aspect, "fov": fov,
                            "near_clip": near_clip, "far_clip": far_clip})
            scene = json.loads(subprocess.check_output(
                [str(args.scene_dump.resolve()), str(args.original.parent / "pak.zip")], text=True))
            node_reference = reference.reference_node
            node_reference.restype = c.c_void_p
            node_reference.argtypes = [c.c_void_p, FloatPtr, FloatPtr, FloatPtr, FloatPtr]
            objects = {item["id"]: item for item in scene["objects"]}
            nodes = {}
            active = set()

            def create_node(identifier):
                if identifier in nodes:
                    return nodes[identifier]
                if identifier in active:
                    raise AssertionError("Scene parent cycle")
                active.add(identifier)
                obj = objects[identifier]
                parent = create_node(obj["parent"]) if obj["parent"] != "-1" else None
                matrix = floats([0] * 16)
                node = node_reference(parent, floats(obj["local_position"]),
                    floats(obj["local_rotation"]), floats(obj["local_scale"]), matrix)
                if not node:
                    raise AssertionError("Original OGRE node creation failed")
                actual = [obj["world_rotation"][r * 3 + col] * obj["world_scale"][col]
                          if col < 3 else obj["world_position"][r]
                          for r in range(3) for col in range(4)] + [0, 0, 0, 1]
                compare("scene_world_matrix", actual, matrix)
                expected_landmark = [sum(matrix[r * 4 + k] * [0.25, 0.5, 1][k]
                                         for k in range(3)) + matrix[r * 4 + 3] for r in range(3)]
                compare("scene_landmark", obj["landmark_world"], expected_landmark)
                counts["scene_nodes"] += 1
                if obj["descriptor"] == "Room Piece" and obj["landmark_ndc"] is not None:
                    landmarks.append({"id": identifier, "name": obj["name"],
                                      "world": expected_landmark, "ndc": obj["landmark_ndc"]})
                nodes[identifier] = node
                active.remove(identifier)
                return node

            for obj in scene["objects"]:
                create_node(obj["id"])
            if sum(obj["authored_orientation"] for obj in scene["objects"]
                   if obj["descriptor"] == "Room Piece") < 300:
                raise AssertionError("Town orientation data was lost")
            # Boundary rejection is part of the exposed portable API contract.
            invalid = floats([math.nan, 0, 0])
            zero, output = floats([0, 0, 0]), floats([0, 0, 0])
            if game(invalid, 28.5, True, 1, output, output) or game(zero, 0, True, 1, output, output):
                raise AssertionError("Invalid camera input was accepted")
        finally:
            reference.reference_close()
    report = {"scope": "normal camera, no shake/collision, yaw=0; original OGRE CPU projection",
              "original_sha256": original.original.sha256, "ogre_sha256": OGRE_SHA256,
              "counts": counts, "maximum_absolute_errors": maximum_errors, "fixtures": fixtures}
    report["town_landmarks"] = sorted(landmarks, key=lambda item: sum(v*v for v in item["ndc"][:2]))[:3]
    if args.report:
        args.report.write_text(json.dumps(report, indent=2) + "\n")
    print("PASS: original camera comparison", json.dumps(counts), json.dumps(maximum_errors))


if __name__ == "__main__":
    main()
