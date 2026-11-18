# ByteC 🚀

ByteC is a lightweight low-level programming language that emulates a custom virtual 64-bit processor. The entire toolchain (compiler, interpreter, installer, and uninstaller) is written in pure C11 for maximum performance and zero dependencies.

## 💻 Architecture & Specifications
Since ByteC emulates an 64-bit architecture, it operates with strict hardware-like constraints:
* **Registers:** 5 general-purpose 64-bit registers: `a`, `b`, `c`, `d`, and `e` and 1 8-bit condition register `ZS`.
* **Memory Type:** Strict fixed-width data types via `<stdint.h>` (`int64_t`).

## 🛠️ Instruction Set (Syntax)

### Data & Math
* `MOV <reg> <val/reg>` — Move a value or another register's content into the target register.
* `ADD <reg> <val/reg>` — Add a value or register content to the target register *(Example: `ADD a 89` or `ADD a b`)*.
* `SUB <reg> <val/reg>` — Subtract a value or register content from the target register.
* `MUL <reg> <val/reg>` — Multiply the target register by a value or another register.
* `DIV <reg> <val/reg>` — Divide the target register by a value or another register.
* `NEG <reg>` — Negate the number inside the specified register (makes it negative).
* `PR <reg>` — Print the current register value to the screen/terminal.
* `JMP <label>` — Jump to label.
* `JIT <label>` — Jump to label if CMP return's 1.
* `JIF <label>` — Jump to label if CMP return's 0.
* `CMP <reg/val> <operator> <reg/val>` — If condition true it move's 1 to ZS register else move's 0(Example: `CMP a > 56`).
* `INC <reg>` — Increment a register.
* `DEC <reg>` — Decrement a register.
* `CALL <function name> <arg1> <arg2>` — Call a function with optional arguments.
* `RET <reg>` — Return to function call and return value of register.
* `ARG <reg> <arg number> ` — Put argument to register.
* `INCLUDE <lib>` — Include a library code.
### Syscall
* `__syscall__->SETRANDOM` — SRAND but in ByteC!
* `__syscall__->RANDOM` — RAND but in ByteC!
> [!CAUTION] 
> Syscalls are not safe and not be tested! NOT use these! Use random.bytec standart library functions!

---

## 🚀 How to Install & Run (Windows)

1. Download the standalone `bytec_installer.exe`.
2. Run the installer. It will safely extract the compiler into `C:\Program Files\ByteC`.
3. Open CMD/Terminal directly in the installation directory (`C:\Program Files\ByteC`).
4. Run commands:
   ```bash
   bytec --version  # To verify your installation
   bytec <filename> # To compile and execute your ByteC code files
   ```

## ❌ How to Uninstall
1. Run `bytec_uninstaller.exe` inside your installation folder.
2. The uninstaller will safely wipe out the binary files and clean up the directory automatically.

---

## 🐛 Have an Issue?
If you find any bugs, edge cases, or memory issues, please feel free to open a **GitHub Issue** in this repository. Our code is automatically analyzed by GitHub CodeQL to ensure top-tier code quality!
## 🤝 Want to Code with Me?
I am looking for contributors to develop ByteC together! If you love low-level programming, compiler design, and pure C, please send me an email or open an issue. I will gladly add you to our GitHub Organization as a team member!
## 📑 License
Distributed under the MIT License. See `LICENSE` for more information.

---
## 📦 ByteC Package Manager (`bpm`)

**BPM** is the official lightweight package manager for ByteC. It automatically downloads, unpacks, tracks versions, and updates community libraries from the [BPM-registry](https://github.com/bytecompilier/bpm-registry).

### Commands

| Command | Description |
| :--- | :--- |
| `bpm install <pkg1> [pkg2 ...]` | Download and install one or more libraries into `.\libs\` |
| `bpm remove <pkg1> [pkg2 ...] [-y]` | Remove installed libraries (use `-y` to skip confirmation) |
| `bpm update` | Check all installed libraries and update outdated ones |
| `bpm list` | Display all installed packages and their local versions |
| `bpm help` | Show the colored CLI help menu |

### Examples

```cmd
:: Install multiple libraries at once
bpm install add std

:: View installed packages and versions
bpm list

:: Update all installed libraries to their latest versions
bpm update

:: Remove libraries without confirmation prompts
bpm remove add std -y
```

### Package Metadata Format

Packages in `BPM-registry` use a clean `key=value` INI format:
```ini
url=https://github.com
version=1.0.0
author=username
description=Short description of the ByteC library
```