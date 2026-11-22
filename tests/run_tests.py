#!/usr/bin/env python3
"""Discover and run ByteC tests using expectations stored in each .bytec file."""

from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
TEST_ROOT = ROOT / "tests"
INTEGER_LINE = re.compile(r"^-?\d+$")


def read_expectations(test_path: Path) -> dict:
    text = test_path.read_text(encoding="utf-8")
    expectations = {}
    for line in text.splitlines():
        match = re.match(r"^\s*;\s*@expect-([a-z-]+)\s*:\s*(.*?)\s*$", line, re.IGNORECASE)
        if match:
            key = match.group(1).lower()
            if key in expectations:
                raise ValueError(f"duplicate @expect-{key} directive")
            expectations[key] = match.group(2)
    return expectations


def numeric_output(output: str) -> list[int]:
    values = []
    for line in output.splitlines():
        stripped = line.strip()
        if INTEGER_LINE.fullmatch(stripped):
            values.append(int(stripped))
    return values


def check_test(executable: Path, test_path: Path) -> tuple[bool, str]:
    relative = test_path.relative_to(ROOT).as_posix()
    try:
        expected = read_expectations(test_path)
    except (OSError, UnicodeError, ValueError) as exc:
        return False, f"invalid test metadata: {exc}"

    if not expected:
        return False, "missing expectation; add an @expect-* directive"

    allowed = {"output", "range", "exit", "error"}
    unknown = set(expected) - allowed
    if unknown:
        return False, "unknown expectation(s): " + ", ".join(sorted(unknown))

    (ROOT / "prep.bc").unlink(missing_ok=True)
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
    except subprocess.TimeoutExpired as exc:
        output = exc.stdout or ""
        if isinstance(output, bytes):
            output = output.decode(errors="replace")
        return False, "execution timed out after 20 seconds\n" + output
    except OSError as exc:
        return False, f"could not start ByteC: {exc}"
    finally:
        (ROOT / "prep.bc").unlink(missing_ok=True)

    output = result.stdout or ""
    actual_numbers = numeric_output(output)
    problems = []

    if "exit" in expected:
        mode = expected["exit"].lower()
        if mode == "zero" and result.returncode != 0:
            problems.append(f"expected exit code 0, got {result.returncode}")
        elif mode == "nonzero" and result.returncode == 0:
            problems.append("expected a non-zero exit code, got 0")
        elif mode not in {"zero", "nonzero"}:
            problems.append(f"unsupported @expect-exit value: {mode}")
    elif result.returncode != 0:
        problems.append(f"unexpected exit code {result.returncode}")

    if "output" in expected:
        try:
            wanted = [int(part.strip()) for part in expected["output"].split(",")]
        except ValueError:
            problems.append("invalid @expect-output; use comma-separated integers")
        else:
            if actual_numbers != wanted:
                problems.append(f"expected numeric output {wanted}, got {actual_numbers}")

    if "range" in expected:
        match = re.fullmatch(r"(-?\d+)\s*\.\.\s*(-?\d+)", expected["range"])
        if not match:
            problems.append("invalid @expect-range; use MIN..MAX")
        else:
            low, high = map(int, match.groups())
            if len(actual_numbers) != 1:
                problems.append(f"expected exactly one numeric output, got {actual_numbers}")
            elif not low <= actual_numbers[0] <= high:
                problems.append(f"expected output in [{low}, {high}], got {actual_numbers[0]}")

    if "error" in expected:
        try:
            pattern = re.compile(expected["error"], re.IGNORECASE)
            if not pattern.search(output):
                problems.append(f"expected diagnostic matching /{expected['error']}/")
        except re.error as exc:
            problems.append(f"invalid @expect-error regular expression: {exc}")

    if problems:
        details = "\n".join(f"      {problem}" for problem in problems)
        if output.strip():
            details += "\n      program output:\n" + "\n".join(
                f"        {line}" for line in output.rstrip().splitlines()
            )
        return False, details

    return True, f"exit={result.returncode}, numeric_output={actual_numbers}"


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

    test_files = sorted(TEST_ROOT.rglob("*.bytec"))
    if not test_files:
        print("ERROR: no .bytec tests found under tests/")
        return 2

    passed = 0
    failed = 0
    print(f"Discovered {len(test_files)} ByteC test(s).")
    for test_path in test_files:
        relative = test_path.relative_to(ROOT).as_posix()
        ok, details = check_test(executable, test_path)
        if ok:
            print(f"PASS  {relative} ({details})")
            passed += 1
        else:
            print(f"FAIL  {relative}")
            print(details)
            failed += 1

    print(f"\nResults: {passed} passed, {failed} failed, 0 skipped")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
