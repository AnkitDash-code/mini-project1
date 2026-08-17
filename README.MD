# CS3.301 Mini Project 1 - Dash Shell

> **Author:** Ankit Dash LCD (2026121015)   
> **Course:** Operating Systems and Networks (CS3.301)  
> **Status:** In Progress (Part A–C Initialized)

Repository for CS3.301 (Operating Systems and Networks) Mini Project 1. 
I have named it as Dash Shell.

## Current Progress & Summary

This repository currently consists of my work in progress for the POSIX C Shell and setting up the overall repo.

- Current work:- Implemented dynamic prompt display (A1) and basic user input loop (A2).
- Test Script:- Checking for compilation using WSL and make

### Current Primary Goals (Part A)

- `[x]` A1 - Shell Prompt: Dynamic prompt showing <user@host:path>, treating the initial launch directory as home (~).
- `[x]` A2 - User Input: Basic REPL loop consuming input using getline(), stripping newlines, handling Ctrl+D, and re-prompting.
- `[ ]` A3 - Lexer & Input Syntax Parsing:
  - Lexer: Tokenize input into operators (`|`, `&`, `;`, `<`, `>`, `>>`) and `WORD` tokens using maximal munch. Handle single/double quotes and backslash escapes.
  - Grammar Parser: Validate token sequences against the right-linear grammar (`LINE`, `CMD`, `TGT`, `ARG`, `BG`).
  - Error Handling: Print `cshell: invalid syntax` for unclosed quotes, trailing backslashes, or grammar rule violations.



## Structure

```text
mini-project1/
├── c-shell/
│   ├── src/
│   |   ├── main.c
│   |   └── prompt.c
│   ├── include/
│   |   ├── shell.h
│   |   └── prompt.h
│   └── Makefile
├── xv6/
│   ├── user/
│   ├── mkfs/
│   ├── kernel/
│   ├── Makefile
│   └── report.md    # Or report.pdf
└── README.md
```

## Current Sprint (Deadline: August 24)

Focusing exclusively on **Mid-Submission** requirements for Parts A–C.

| Milestone / Sub-Task | Target Date | Status |
| :--- | :---: | :---: |
| Repo setup & directory structure | Aug 17 | `[x]` |
| Custom prompt display & command loop (Part A) | Aug 18 | `[2/3]` |
| Built-in commands & process execution (Part B) | Aug 19 | `[ ]` |
| Input/Output redirection `<` `>` `>>` & Piping `\|` (Part C) | Aug 20 | `[ ]` |
| Sanity testing & Mid-Submission push | Aug 22 | `[ ]` |

---

## C - Shell ( WIP )

### Code Structure & File Responsibilities

- **`include/shell.h`**: Global header file providing core standard library headers (`stdio.h`, `stdlib.h`, `unistd.h`) needed across the shell system.
- **`include/prompt.h`**: Header file declaring function prototypes for prompt state initialization (`capture_prompt`) and prompt rendering (`show_prompt`).
- **`src/prompt.c`**: Handles User prompt generation. Stores the initial launch directory as `home_dir`, retrieves system information (`USER`, `gethostname`), calculates relative paths against `home_dir` to substitute `~`, and flushes standard output to ensure immediate rendering.
- **`src/main.c`**: Implements the shell's Read-Eval-Print Loop (REPL). Calls initialization routines, prompts for user input, processes input streams using `getline()`, strips trailing newlines with `strcspn()`, handles empty input lines, and handles `Ctrl+D` (EOF) exits.
- **`Makefile`**: Automates compilation using `gcc` configured with `-std=c23`, strict warnings (`-Wall -Wextra -Werror`), POSIX compatibility macros, and compiles source files into `shell.out`.

### Part A1: Shell Prompt
- Dynamic prompt formatted as `<username@hostname:currentpath>`.
- Stores launch directory as home (`~`) and replaces subpaths relative to it.

### Part A2: User Input
- Line-by-line input consumption using `getline()`.
- Strips trailing newlines, ignores empty inputs, and exits on `Ctrl+D`.

## Setup & Compiling ( Pending)

To build and run the shell:

```bash
cd c-shell
make         # Compiles using GCC with POSIX/C23 flags
./shell.out  # Launches Dash Shell
make clean   # Cleans up the make files
```

## xv6 MLFQ Scheduler ( Pending )

## Status

* **Mid-submission:** Parts A–C (Shell input, intrinsics, redirection, pipes) - Work Started


* **End-submission:** Parts D–F & xv6 MLFQ Scheduler implementation - Will Start post mid-sem

---

## References

- [POSIX.1-2017 Base Specifications (IEEE Std 1003.1)](https://pubs.opengroup.org/onlinepubs/9699919799/idx/head.html) – Reference for POSIX system calls (`getcwd`, `gethostname`, `getline`), library interfaces, and signal handling.
- [GNU Bash Source Mirror](https://github.com/gitGNU/gnu_bash) – Reference for shell execution flow, REPL design patterns, and standard prompt/tokenization strategies.
- [GeeksforGeeks C Programming Articles & Guides](https://www.geeksforgeeks.org/c-programming-language/) – Reference for Standard C library functions (`string.h`, `stdio.h`, `stdlib.h`) and standard memory management patterns.

---

## AI Usage Declaration

AI tools were utilized as an educational assistant, documentation aid, and debugging tool throughout this project:

- **Specification Clarification:** Deconstructing project requirements, POSIX standards, and understanding formal automata concepts for the A3 grammar parser.
- **API & Documentation Lookup:** Searching standard library functions and POSIX system calls (`getcwd`, `gethostname`, `getline`, `strcspn`).
- **Debugging & Error Diagnostics:** Troubleshooting compiler flags (`-std=c23`), Makefile build issues, and standard edge cases.
- **Documentation & Formatting:** Structuring, drafting, and formatting the `README.md` file.

*Note: AI was used strictly for conceptual guidance, documentation drafting, and debugging support. All final architectural decisions, logic, and code implementations were written, tested, and integrated manually.*

