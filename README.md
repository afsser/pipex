# pipex Project Overview

The **pipex** project offers a deep dive into process handling, pipes, and managing file descriptors (fds) in a UNIX-like environment. The goal is to replicate the behavior of shell piping (`< file1 cmd1 | cmd2 > file2`), leveraging system calls like `fork()`, `pipe()`, and `execve()`. This project teaches you how to create and synchronize processes while managing input/output redirection efficiently.

You will learn to work with file descriptors, ensuring that each one is correctly handled—opened, duplicated, and closed—without leaving any file descriptor unintentionally open after execution. Additionally, it’s crucial to handle memory allocations safely, avoiding memory leaks throughout the program's lifecycle.

The program takes four arguments: two file names (`file1`, `file2`) and two commands (`cmd1`, `cmd2`). It reads from `file1`, passes the data through `cmd1`, pipes it into `cmd2`, and then writes the output into `file2`. 

For example:

$> ./pipex infile "ls -l" "wc -l" outfile

This should behave the same as:

$> < infile ls -l | wc -l > outfile

## Key System Functions Used:
- **open**, **close**, **read**, **write**: To manage file input/output.
- **malloc**, **free**: For dynamic memory management, ensuring no leaks.
- **dup**, **dup2**: To duplicate file descriptors and redirect input/output streams.
- **execve**: To execute shell commands.
- **fork**: To create child processes.
- **pipe**: For inter-process communication (connecting the output of one process to the input of another).
- **wait**, **waitpid**: For process synchronization and ensuring proper execution order.
- **access**, **perror**, **strerror**, **exit**, **unlink**: For error handling and process termination.

## Requirements:
- The project must be written in C, and follow the coding Norm.
- The Makefile must compile the project without unnecessary relinking, including the standard rules (`all`, `clean`, `fclean`, `re`).
- **Global variables are forbidden.**
- All memory allocated on the heap must be properly freed to avoid leaks, and no file descriptors should remain open after execution.
- You must thoroughly handle errors (segmentation faults, bus errors, double free, etc.).
- The program must behave exactly like a shell command.

## Example Usage:
To run the program:
```bash
./pipex infile "cmd1" "cmd2" outfile
