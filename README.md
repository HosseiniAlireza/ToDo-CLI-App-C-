
ToDo CLI (C) — README


NAME
    todo — a lightweight command-line To-Do manager written in C

SYNOPSIS
    todo <command> [arguments]

DESCRIPTION
    A simple CLI utility to add, list, mark-as-done, remove, and clear tasks.
    Tasks are persisted in a plain text file in the user’s home directory:
        $HOME/tdl

FEATURES
    - Incremental IDs for tasks
    - List tasks with completion status (0 = pending, 1 = done)
    - Mark a task as done by ID
    - Remove a task by ID
    - Clear all tasks
    - Helpful usage and error messages

FILES
    $HOME/tdl
        Plain-text task database. Each line format:
            <ID>    <STATUS>        <TASK_DESCRIPTION>
        Example:
            1    0        Finish C project
            2    1        Submit final report

PLATFORM
    Works on Linux and macOS (with a POSIX-like shell). On Windows, use MSYS2/MinGW.

--------------------------------------------------------------------
BUILD
--------------------------------------------------------------------

Quick build (GCC):
    $ gcc ToDo.c function.c -o todo

Recommended (with warnings & optimizations):
    $ gcc -Wall -Wextra -O2 ToDo.c function.c -o todo

Optional Makefile (save as Makefile):
    CC = gcc
    CFLAGS = -Wall -Wextra -O2
    OBJ = ToDo.o function.o

    todo: $(OBJ)
    	$(CC) $(CFLAGS) -o $@ $(OBJ)

    %.o: %.c function.h
    	$(CC) $(CFLAGS) -c $<

    clean:
    	rm -f $(OBJ) todo

Build with make:
    $ make

--------------------------------------------------------------------
USAGE
--------------------------------------------------------------------

General form:
    $ ./todo <command> [arguments]

Commands:
    -a <task>       --add <task>        Add a new task
    -l              --list              List all tasks
    -d <id>         --done <id>         Mark a task as done
    -r <id>         --remove <id>       Remove a task by ID
    -c              --clear             Clear all tasks
    -h              --help              Show help and usage

--------------------------------------------------------------------
EXAMPLES
--------------------------------------------------------------------

Add tasks:
    $ ./todo -a "Finish C project"
    Added a new task (id=1)

    $ ./todo --add "Fix issue #42"
    Added a new task (id=2)

List tasks:
    $ ./todo -l
    ////////// Show All //////////
    ID   Done     Task
    1    0        Finish C project
    2    0        Fix issue #42
    ==============================

Mark done:
    $ ./todo -d 1
    Task 1 marked as done.

Remove by ID:
    $ ./todo --remove 2
    Removed task 2.

Clear all:
    $ ./todo -c
    Cleared all tasks.

Help:
    $ ./todo -h
    Usage: todo <command> [arguments]
    Commands:
    -a <task>  or    --add    <task>    Add a new task
    -l         or    --list             List all tasks
    -c         or    --clear            Clear all tasks
    -d <id>    or    --done   <id>      Mark task as done
    -r <id>    or    --remove <id>      Remove task from list
    -h         or    --help             Show this help message

--------------------------------------------------------------------
RETURN CODES
--------------------------------------------------------------------
    0   Success
    1   Error (invalid command/args, file errors, not found, etc.)

--------------------------------------------------------------------
ERRORS & NOTES
--------------------------------------------------------------------
    - Missing argument (e.g., ID for --done/--remove) → clear stderr message.
    - Invalid ID (non-numeric or <= 0) → error.
    - If $HOME/tdl does not exist, it is created on first --add.
    - File updates use a temporary file and atomic rename for safety.

--------------------------------------------------------------------
PROJECT LAYOUT
--------------------------------------------------------------------
    ToDo.c         CLI entry point and argument parsing
    function.c     Core logic (add/list/done/remove/clear)
    function.h     Function declarations
    README         This document

--------------------------------------------------------------------
LIMITATIONS
--------------------------------------------------------------------
    - No concurrency control on the data file.
    - IDs are incremental; they are not re-numbered after removals.
    - No advanced features (sorting, filters, due dates, tags).

--------------------------------------------------------------------
LICENSE
--------------------------------------------------------------------
    MIT License. You may use, modify, and distribute with attribution.

AUTHOR
    Your Name <you@example.com> — contributions welcome.
