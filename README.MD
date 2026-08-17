# CS3.301 Mini Project 1

> **Author:** Ankit Dash LCD (2026121015)   
> **Course:** Operating Systems and Networks (CS3.301)  
> **Status:** In Progress (Part A–C Initialized)

Repository for CS3.301 (Operating Systems and Networks) Mini Project 1.

## Current Progress & Summary

This repository currently consists of my work in progress for the POSIX C Shell and setting up the overall repo.

- Current work:- Beginning Implementation of C Shell baseline architecture for Parts A - C.
- Test Script:- Checking for compilation using WSL and make

### Current Primary Goals (Part A)

- Prompt Display: Implement a dynamic shell prompt showing the user, hostname, and current working directory relative to home (`~`).
- Command Parsing & Execution: Parse single-line user input, handle whitespace/delimiters, and execute system commands using `fork()` and `execvp()`.
- Built-in Intrinsics: Support essential built-in commands natively:
  - `cd` (directory navigation, including `~`, `.`, `..`, and previous directory `-`)
  - `echo` (string output with space normalization)
  - `pwd` (print absolute path)
- Basic Error Handling: Manage invalid commands, missing arguments, and system call failures gracefully without crashing the shell loop.



## Structure

```text
mini-project1/
├── c-shell/
│   ├── src/
│   |   ├── main.c
│   |
│   ├── include/
│   |   ├── shell.h
│   |
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
| Custom prompt display & command loop (Part A) | Aug 18 | `[ ]` |
| Built-in commands & process execution (Part B) | Aug 19 | `[ ]` |
| Input/Output redirection `<` `>` `>>` & Piping `\|` (Part C) | Aug 20 | `[ ]` |
| Sanity testing & Mid-Submission push | Aug 22 | `[ ]` |

---

## C - Shell ( WIP )

## Setup & Compiling ( Pending)

## xv6 MLFQ Scheduler ( Pending )

## Status

* **Mid-submission:** Parts A–C (Shell input, intrinsics, redirection, pipes) - Work Started


* **End-submission:** Parts D–F & xv6 MLFQ Scheduler implementation - Will Start post mid-sem