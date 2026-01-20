*This project has been created as part of the 42 curriculum by hfandres, torakoto.*

# Description
## Title :
	minishell

## Summary :
	This project is about creating a small, interactive UNIX shell that emulates bash. It focuses on the fundamentals of command parsing and execution: tokenization, quotes, environment variable expansion, pipelines, redirections, and process/signal handling.

	At a high level, this minishell:
	- Displays a prompt and reads user input using GNU Readline.
	- Parses commands with support for single/double quotes and environment expansion.
	- Executes binaries found in PATH and several built-in commands.
	- Implements redirections (<, >, >>, <<) and pipelines (|).
	- Handles interactive signals (Ctrl-C, Ctrl-\, Ctrl-D) in a bash-like way.

	Implemented builtin commands: echo, cd, pwd, export, unset, env, exit.

# Instructions

## To compile:
```bash
make
```
## Usage:

### Requirements (Linux)
- A C compiler and make (e.g. cc/clang/gcc, make)
- GNU Readline development headers (because the project links with -lreadline)
  - Debian/Ubuntu: `sudo apt-get install libreadline-dev`
  - Fedora: `sudo dnf install readline-devel`

### Run the shell :
```bash
./minishell
```

### Clean / rebuild
```bash
make clean
make fclean
make re
```

### Run with memory leaks checking :

#### 1. Create a file to suppress known Readline leaks:
```bash
make rlsupp
```

#### 2. Run the shell like this:
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=rl.supp ./minishell
```
### Or just :
```bash
make valgo
```
## Features
* The shell displays a prompt and waits for a command line.
* It provides history navigation using the **UP** and **DOWN** arrows.
* It handles quoting:
	- Single quotes (') prevent interpretation of all metacharacters.
	- Double quotes (") prevent interpretation of metacharacters except `$` (environment variables).
* Handle the following **redirections**:
	- < should redirect input.
	- \> should redirect output.
	- << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
	- \>\> should redirect output in append mode.
* It supports **pipelines** (| character).
* It expands **environment variables** (`$VAR`) and supports the common special case `$?` (last exit status).
* Interactive signals:
	- Ctrl-C displays a new prompt on a new line.
	- Ctrl-\\ does nothing.
	- Ctrl-D exits the shell.
```bash
#exit the shell
exit
```
# Resources
- Processes, fork/exec/wait:
	- [linux/man-pages/man2/fork](https://man7.org/linux/man-pages/man2/fork.2.html)
	- [linux/man-pages/man2/execve](https://man7.org/linux/man-pages/man2/execve.2.html)
	- [linux/man-pages/man2/waitpid](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- Pipes and file descriptors:
	- [linux/man-pages/man2/pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)
	- [linux/man-pages/man2/dup](https://man7.org/linux/man-pages/man2/dup.2.html)
	- [Pipes, Forks, & Dups: Understanding Command Execution and Input/Output Data Flow](https://www.rozmichelle.com/pipes-forks-dups/)
- Signals (interactive behavior):
	- [linux/man-pages/man7/signal](https://man7.org/linux/man-pages/man7/signal.7.html)
- Bash manual (reference behavior):
	- https://www.gnu.org/software/bash/manual/bash.html

AI usage
- Used GitHub Copilot to find duplicate functions and to refactor long functions (over 25 lines) into 2 or 3 smaller functions.
- Reviewed the codebase to identify and remove leftover debug functions or old function unused.
- Using chatGpt to understand new concepts more quickly.
