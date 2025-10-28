
# ToDo CLI (C) — README


NAME
  todo — a lightweight command-line To-Do manager written in C.

REPO
  Clone the repository and enter the project directory.

CLONE
  $ git clone <REPO_URL>
  $ cd <REPO_DIR>

BUILD
  # Quick build (GCC)
  $ gcc -Wall -Wextra -O2 ToDo.c function.c -o todo

  # Optional: install system-wide (may require sudo)
  $ install -m 0755 ./todo /usr/local/bin/todo

USAGE
  $ ./todo <command> [arguments]

COMMANDS
  -a <task>       --add <task>        Add a new task
  -l              --list              List all tasks
  -d <id>         --done <id>         Mark a task as done
  -r <id>         --remove <id>       Remove a task by ID
  -c              --clear             Clear all tasks
  -h              --help              Show help and usage

EXAMPLES
  $ ./todo --add "Finish C project"
  Added a new task (id=1)

  $ ./todo --list
  ////////// Show All //////////
  ID   Done     Task
  1    0        Finish C project
  ==============================

  $ ./todo --done 1
  Task 1 marked as done.

  $ ./todo --remove 1
  Removed task 1.

  $ ./todo --clear
  Cleared all tasks.

NOTES
  • Data is stored in a plain-text file at: $HOME/tdl
    Format per line: <ID>    <STATUS>        <TASK_DESCRIPTION>
    STATUS: 0 = pending, 1 = done
  • If the data file does not exist, it is created on first --add.
  • Return code: 0 on success; non-zero on error.

STRUCTURE
  ToDo.c        CLI entry point and argument parsing
  function.c    Core logic (add/list/done/remove/clear)
  function.h    Function declarations

PLATFORM
  Linux / macOS (POSIX shell). On Windows, use MSYS2/MinGW.
