# Contributing to ByteC

Thank you for your interest in ByteC!

## Before you start

- Read the project documentation: https://bytecompilier.github.io/ByteC/
- Search existing issues and pull requests before starting work.
- For significant changes, open an issue first so the proposed direction can be discussed.

## Development guidelines

- ByteC is implemented in C11. Keep contributions consistent with the existing C codebase.
- Keep pull requests focused. Avoid unrelated formatting changes or large refactors.
- Preserve existing ByteC syntax and documented behavior unless the change intentionally updates them.
- Do not silently change VM or standard-library behavior as part of an unrelated feature.
- Add or update tests when changing language behavior, commands, modules, or error handling.
- Update documentation and examples when a user-visible feature changes.

## Running tests

Use the project's normal CMake build process, then run the test runner against the built executable:

```sh
python tests/run_tests.py path/to/ByteC
```

On Windows, the executable may be named `ByteC.exe`:

```powershell
python tests\run_tests.py build\ByteC.exe
```

Use the toolchain and build instructions documented by the project for your platform.

## Pull requests

1. Create a focused branch for your change.
2. Explain the motivation and summarize the implementation.
3. Include test results and any relevant limitations.
4. Keep formatting consistent with nearby files.
5. Be responsive to review feedback.

By contributing, you agree that your contributions are provided under the project's existing license.
