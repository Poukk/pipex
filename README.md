## Project scope

The idea of this project is to understand how pipes work. Trying to copy the usage in shells of `|`. The mandatory part asks for the following structure:

```bash
< file1 cmd1 | cmd2 > file2
```

| Program name   | pipex                                                                                                                        |
| -------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| Turn in files  | Makefile, .h, .c                                                                                                             |
| Makefile       | NAME, all, clean, fclean, re                                                                                                 |
| Arguments      | file1 cmd1 cmd2 file2                                                                                                        |
| External func. | open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid |

---

## Project Visualization
The objective here is to create two children that will become the commands that we want to executing. We use `dup2()` to change STDIN and STDOUT as needed, then, wait for the children to terminate.

![pipex_flow](https://github.com/Poukk/pipex/blob/main/pipex_flow.png)

---

## Starting points
### Understanding System Calls
A system call is a request for service that a program makes of the kernel. The service is generally something that only the kernel has the privilege to do, such as doing I/O. Programmers don’t normally need to be concerned with system calls because there are functions in the GNU C Library to do virtually everything that system calls do. These functions work by making system calls themselves.

For example, the C function `exit()` is not a syscall, but calls `_exit()` to terminate a process, besides doing additional cleanup.

### Understanding Processes
**Processes in UNIX represent running instances of programs**, each with its own unique Process ID (PID) and allocated system resources. They are created through several mechanisms: when a user runs a command, through system initialization, or when an existing process spawns a new one using the `fork()` system call, which creates a child process as an exact copy of its parent. After forking, the child process typically executes a new program using exec(), replacing its memory space with the new program's code. 

### A fork() in the road
The `fork()` system call is a fundamental mechanism in Unix-like operating systems that enables process creation through a unique parent-child relationship model. When a process calls fork(), the operating system creates an exact copy of that process, including its memory space, file descriptors, and program counter, with the child process receiving its own unique Process ID (PID). The key distinction lies in the return value of fork(): the parent process receives the child's PID as the return value, while the child process receives 0, allowing each process to determine its role and execute different code paths accordingly.

### Inter-process communication
Inter-Process Communication (IPC) refers to mechanisms that allow processes to share data and coordinate their actions in Unix systems. The kernel provides several IPC methods: shared memory allows processes to map the same memory region into their address spaces for direct data exchange - it's the fastest IPC method since no data copying is needed. Message queues provide a way to exchange discrete messages between processes in a structured format with different priorities. Semaphores are synchronization primitives used to control access to shared resources and prevent race conditions. Signals enable asynchronous notifications between processes for event handling. Sockets allow both local (Unix domain) and network communication between processes. Each IPC mechanism has different characteristics - shared memory offers speed but requires careful synchronization, message queues provide structure but have size limits, semaphores enable coordination but can lead to deadlocks if misused.

### Understanding Pipes
Pipes represent one of the simplest IPC mechanisms in Unix, providing unidirectional byte stream communication between processes. When created using pipe(), the system returns two file descriptors - a read end and a write end. Data flows one way through the pipe: what's written to the write end becomes available for reading at the read end. Pipes are typically used with fork() - a parent process creates a pipe, then forks a child, and each process uses only the end it needs. The kernel manages a buffer for the pipe (usually 64KB) and handles flow control automatically: writes block when the pipe is full, reads block when empty. Pipes are commonly used to implement shell command pipelines and to establish parent-child process communication channels. Their simplicity and automatic buffering make them ideal for streaming data between related processes.
