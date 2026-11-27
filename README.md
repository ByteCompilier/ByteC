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
* `MODULE <module name>` — Enable a built-in module (for example, `MODULE audio`).
* `IN <reg>` — Input user to register

### Internal Modules: `MODULE`

The `MODULE` instruction enables built-in ByteC modules, which provide additional commands. It is distinct from `INCLUDE`, which inserts source-library code.

```bytec
MODULE audio
```

Place the module declaration before commands belonging to that module.

### 🔊 Audio Module

ByteC's Audio module is built on Raylib audio functionality. Enable it with `MODULE audio` before using Audio commands:

```bytec
MODULE audio
AUDIO_INIT
; Audio commands here
AUDIO_CLOSE
```

**Audio device and master volume**

| Command | Description |
| :--- | :--- |
| `AUDIO_INIT` | Initialize the audio device and set initial master volume. |
| `AUDIO_CLOSE` | Close the audio device. |
| `AUDIO_READY` | Store audio-device readiness (1/0) in register `a`. |
| `AUDIO_VOLUME <value>` | Set master volume using ByteC's 0–10 scale (5 = 50%). |
| `AUDIO_GET_VOLUME` | Read master volume into register `a`, scaled to 0–10. |

**Wave and Sound resources**

| Command | Description |
| :--- | :--- |
| `AUDIO_LOAD_WAVE <file>` | Load a Wave file. |
| `AUDIO_UNLOAD_WAVE <index>` | Unload a Wave resource. |
| `AUDIO_IS_WAVE_VALID <index>` | Check Wave validity; result is stored in register `a`. |
| `AUDIO_WAVE_CROP <index> <start frame> <end frame>` | Crop Wave data to a frame range; use a range suitable for the loaded file. |
| `AUDIO_LOAD_SOUND <file>` | Load a Sound file. |
| `AUDIO_LOAD_SOUND_FROM_WAVE <wave index>` | Create a Sound from a loaded Wave. |
| `AUDIO_LOAD_SOUND_ALIAS <sound index>` | Create an alias of an existing Sound. |
| `AUDIO_UNLOAD_SOUND <index>` | Unload a Sound resource. |
| `AUDIO_UNLOAD_SOUND_ALIAS <index>` | Unload a Sound alias. |
| `AUDIO_IS_SOUND_VALID <index>` | Check Sound validity; result is stored in register `a`. |
| `AUDIO_EXPORT_WAVE <index> <file>` | Export Wave data to an audio file. |
| `AUDIO_EXPORT_WAVE_AS_CODE <index> <file>` | Export Wave data as source code. |

**Playback and sound settings**

| Command | Description |
| :--- | :--- |
| `AUDIO_PLAY_SOUND <index>` | Play a Sound. ByteC currently waits for the sound to finish before continuing. |
| `AUDIO_STOP_SOUND <index>` | Stop a Sound. |
| `AUDIO_PAUSE_SOUND <index>` | Pause a Sound. |
| `AUDIO_RESUME_SOUND <index>` | Resume a paused Sound. |
| `AUDIO_IS_SOUND_PLAYING <index>` | Check playback status; result is stored in register `a`. |
| `AUDIO_SET_SOUND_VOLUME <index> <volume>` | Set Sound volume from 0.0 to 1.0. |
| `AUDIO_SET_SOUND_PITCH <index> <pitch>` | Set Sound pitch (1.0 is normal). |
| `AUDIO_SET_SOUND_PAN <index> <pan>` | Set stereo pan from -1.0 (left) to 1.0 (right). |

Wave and Sound resources use separate index lists starting at `0`. Sound aliases have their own list and must be released with `AUDIO_UNLOAD_SOUND_ALIAS`. Unload resources when finished and close the audio device before exiting.

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


## 📚 Examples

The `examples/` directory contains runnable, focused ByteC programs. Existing examples are preserved.

### Language basics

- [`calc.bytec`](examples/calc.bytec) — interactive calculator with arithmetic and branches.
- [`arithmetics.bytec`](examples/arithmetics.bytec) — arithmetic operations and register values.
- [`comparison.bytec`](examples/comparison.bytec) — comparison and conditional jumps.
- [`count_loop.bytec`](examples/count_loop.bytec) — counting loop.
- [`factorial.bytec`](examples/factorial.bytec) — factorial calculation using a loop.
- [`functions.bytec`](examples/functions.bytec) — function calls, arguments, and return values.
- [`input_compare.bytec`](examples/input_compare.bytec) — input and branching based on comparison.
- [`rand_game.bytec`](examples/rand_game.bytec) — random number guessing game.
- [`random_number.bytec`](examples/random_number.bytec) — generate and print a random number.

### Audio examples

Audio samples require a supported audio file in the program's working directory; the example filenames can be changed to match your file.

- [`audio_device.bytec`](examples/audio_device.bytec) — initialize/check the device and set master volume.
- [`audio_play_sound.bytec`](examples/audio_play_sound.bytec) — load, validate, and play a sound.
- [`audio_sound_settings.bytec`](examples/audio_sound_settings.bytec) — adjust Sound volume, pitch, and pan.
- [`audio_wave_export.bytec`](examples/audio_wave_export.bytec) — load/validate Wave and export audio and code.
- [`audio_wave_crop.bytec`](examples/audio_wave_crop.bytec) — crop Wave frames and export the result; adjust the frame range for your audio file.
- [`audio_alias.bytec`](examples/audio_alias.bytec) — create and unload a Sound alias.

Example execution from the repository root:

```cmd
bytec examples\\count_loop.bytec
```

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