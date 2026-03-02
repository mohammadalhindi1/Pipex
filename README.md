# Pipex

**Pipex** is a simple project written in **C** that recreates the behavior of a shell pipe (`|`).  
It teaches how processes communicate using **pipes** and how to manage **file descriptors** with system calls.

---

## 🧠 Overview
Your program should behave like this shell command:
```bash
< file1 cmd1 | cmd2 > file2

It takes an input file, runs two commands, and writes the result to an output file.

⚙️ How It Works

1.Open the input and output files.
2.Create a pipe to connect two processes.
3.Use fork() to create child processes.
4.Redirect input/output using dup2().
5.Execute commands with execve().
6.Wait for both processes to finish.

```
./pipex infile "ls -l" "wc -l" outfile
# Same as:
< infile ls -l | wc -l > outfile
```

```
pipex/
│── src/
│   ├── main.c
│   ├── process.c
│   ├── exec_cmd.c
│   ├── error.c
│── include/
│   └── pipex.h
│── Makefile
└── README.md
```

🧰 Allowed Functions

open, close, read, write,
malloc, free, pipe, fork,
dup2, execve, waitpid, perror, access

🧾 Example Output

If infile contains:

```
hello world
42 pipex project
```
and you run:

```
./pipex infile "grep pipex" "wc -w" outfile
```
then outfile will contain:
```
2
```
🎯 Goal

Learn process management in UNIX.

Understand how pipes, fork, and execve work together.

Produce clean, leak-free, and norm-compliant C code.
```

**Mohammad Alhindi (malhendi)**

- GitHub: https://github.com/mohammadalhindi1
- LinkedIn: www.linkedin.com/in/mohammad-alhendi13
```
───────────────────────────────
© 2025 Mohammad Alhindi — All Rights Reserved  
Reusing or copying this code without permission is not cool — be original.
───────────────────────────────
