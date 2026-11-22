#!/usr/bin/env python3
"""Run the deterministic ByteC smoke/regression tests on Windows."""

from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
TESTS = [
    ("tests/vm/test_jmp.bytec", ["10"]),
    ("tests/vm/test_jit.bytec", ["10"]),
    ("tests/vm/test_jif.bytec", ["10"]),
    ("tests/vm/test_multiple_operations.bytec", ["590"]),
    ("tests/vm/test_call.bytec", ["42"]),
    ("tests/vm/test_arg.bytec", ["42"]),
    ("tests/vm/test_nested_operations.bytec", ["9"]),
    ("tests/std/test_math_abs.bytec", ["15"]),
    ("tests/std/test_math_pow.bytec", ["32"]),
]

SKIPPED = {
    "tests/vm/test_cmp_less.bytec": "PR ZS output is not currently supported by the VM.",
    "tests/std/test_math_min_max.bytec": "Known max() implementation issue; tracked separately.",
    "tests/std/test_random.bytec": "Random output needs range-aware assertions, not fixed output.",
    "tests/errors/test_div_zero.bytec": "Current VM may terminate abnormally on integer division by zero.",
    "tests/errors/test_invalid_register.bytec": "Negative-test behavior needs a stable diagnostic contract.",
    "tests/errors/test_invalid_instruction.bytec": "Unknown-instruction rejection is not yet guaranteed by the VM.",
}

def main() -> int:
    if len(sys.argv) != 2:
        print("Usage: python tests/run_tests.py <path-to-ByteC.exe>")
        return 2

    executable = Path(sys.argv[1])
    if not executable.is_absolute():
        executable = (Path.cwd() / executable).resolve()
    if not executable.is_file():
        print(f"ERROR: ByteC executable not found: {executable}")
        return 2

    passed = 0
    failed = 0
    for relative_path, expected in TESTS:
        test_path = ROOT / relative_path
        (ROOT / 'prep.bc').unlink(missing_ok=True)
        try:
            result = subprocess.run(
                [str(executable), str(test_path.relative_to(ROOT))],
                cwd=ROOT,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                timeout=20,
                check=False,
            )
            output = result.stdout
            actual = [line.strip() for line in output.splitlines() if re.fullmatch(r'-?\d+', line.strip())]
            ok = result.returncode == 0 and actual == expected
            if ok:
                print(f"PASS  {relative_path}")
                passed += 1
            else:
                print(f"FAIL  {relative_path} (exit={result.returncode})")
                print(f"      expected numeric output: {expected}")
                print(f"      actual numeric output:   {actual}")
                if output.strip():
                    print("      program output:")
                    for line in output.rstrip().splitlines():
                        print(f"        {line}")
                failed += 1
        except subprocess.TimeoutExpired:
            print(f"FAIL  {relative_path} (timeout)")
            failed += 1
        finally:
            (ROOT / 'prep.bc').unlink(missing_ok=True)

    print("\nSkipped tests:")
    for path, reason in SKIPPED.items():
        print(f"SKIP  {path}: {reason}")

    print(f"\nResults: {passed} passed, {failed} failed, {len(SKIPPED)} skipped")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
