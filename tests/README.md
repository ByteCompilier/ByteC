# ByteC tests

This directory contains small ByteC programs grouped by the component they exercise.

## Directories

- `vm/` — arithmetic, registers, comparisons, jumps, calls, and argument passing.
- `std/` — programs that include and exercise files from `STD/`.
- `errors/` — negative inputs that should be run separately to inspect error handling.

## Running a test

Run a file with the ByteC executable, for example:

```cmd
bytec tests\\vm\\test_add.bytec
bytec tests\\vm\\test_call.bytec
bytec tests\\std\\test_math_abs.bytec
```

Run negative tests one at a time. A process crash is not a successful error-handling result.

## Notes

- Labels use the ByteC syntax `: label_name` (colon, one space, then the label name).
- The test programs are independent; run each file in a fresh process.
- Expected output is recorded in comments where it is deterministic.
- Random-number tests must be checked by range, not by comparing against one fixed output.
- `test_math_min_max.bytec` is also a regression check: the current `STD/math.bytec` implementation of `max` appears to return the first argument for the tested input, so its expected second output may currently fail.
- These are source-level test cases, not yet an automated test runner. They have been added to the repository but have not been executed against a Windows ByteC binary in this environment.
