# ByteC 🚀

ByteC is a new low-level programming language that emulates a virtual 8-bit processor. The compiler and interpreter are written in pure C for maximum performance.

## 💻 Architecture & Specifications
Since ByteC emulates an 8-bit processor, it has strict hardware-like constraints:
* **Registers:** 5 general-purpose registers: `a`, `b`, `c`, `d`, and `e`.
* **Memory Limits:** Registers store numbers from `0` to `155` (emulating a custom 8-bit range).

## 🛠️ Instruction Set (Syntax)
* `MOV <reg> <val/reg>` — Move a value or another register's content into the target register.
* `ADD <reg> <val/reg>` — Add a value or register content to the target register. *(Example: `ADD a 89` or `ADD a b`)*
* `SUB <reg> <val/reg>` — Subtract a value or register content from the target register.
* `MUL <reg> <val/reg>` — Multiply the target register by a value or another register.
* `DIV <reg> <val/reg>` — Divide the target register by a value or another register.
* `NEG <reg>` — Negate the number inside the specified register (makes it negative).
* `PR <reg>` — Print the register value directly to the screen/terminal.

## 🚀 How to Run
Currently, the compiler is fully optimized for **Windows**.
*(If you are using macOS or Linux, please open an Issue or email me, and I will compile a binary for your operating system).*

1. Download the `bytec` compiler.
2. Create a source file with your code and place it inside the compiler directory.
3. Open CMD/Terminal in that directory.
4. Run commands:
   ```bash
   bytec --version  # To check the compiler version
   bytec            # To compile and execute your program
   ```

## 🐛 Have an Issue?
If you find any bugs or edge cases, please feel free to open a **GitHub Issue** in this repository.

## 🤝 Want to Code with Me?
I am looking for contributors to develop ByteC together! If you love low-level programming, compiler design, and C, please **send me an email** or **open an issue**. I will gladly add you to our GitHub Organization as a team member! 
