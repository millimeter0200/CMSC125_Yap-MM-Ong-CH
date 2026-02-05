# CMSC125_Yap-MM-Ong-CH

CMSC 125-1 LAB 1
ONG, CHRISTEL HOPE
YAP, MAE MARICAR


I. Compilation and usage instructions
II. List of implemented features
III. Known limitations or bugs
IV. Design decisions and architecture overview
V. Screenshots showing functionality


WEEK 1: DESIGN NOTES

I. Problem Analysis
- The objective of Lab 1 is to implement a simplified UNIX Shell in C that demonstrates core operating concepts, particularly:
  a) Process management: fork(), exec(), wait(), waitpid(), getpid(), getpid()
  b) I/O: dup2(), open(), close()
  c) File system: chdir(), getcwd()
- Additionally, the shell must continuously receive user input, interpret commands, and execute them while remaining responsive, similar to a basic version of bash.

II. Features
The shell will support the following required features:
  1. Interactive Command Loop
  2. Built-in Commands
    2.1 exit
    2.2 Cd <directory>
    2.3 pwd
  3. External Command Execution
    3.1 Execution via fork() and exec()
  4. I/O Redirection
  5. Background Execution
Background jobs will be periodically reaped using waitpid(..., WNOHANG) at the beginning of each shell loop iteration to guarantee zombie processes don’t accumulate.

III. Solution Architecture
The shell is structured into clearly separated modules:
  1. Main loop
    1.1 Cleanup background jobs
    1.2 Display prompt
    1.3 Read user input
    1.4 Parse command
    1.5 Execute Command
  2. Command Parsing
    2.1 Tokenize input using whitespace
    2.2 Detect special operands
    2.3 Populate a command structure
  3. Execution Layer
    3.1 Built-ins handled without forking
    3.2 External commands
      3.2.a. fork() child
      3.2.b. Apply redirection using open () + dup2()
      3.2.c. Execute using exec()
    3.3 Parent
      3.3.a. waitpid() if foreground
      3.3.b. Register job if background
  4. Background Job Management
      4.1 Maintain an array/list of background PIDs
  The shell maintains a job table containing PID, job ID, and command string. Completed jobs are removed after detection using waitpid(..., WNOHANG).

IV. Error Handling
  A. All system calls will check return values
  B. Errors reported using perror()
  C. Invalid commands display: [mysh: command not found: <command>]

V. Estimated Implementation Timeline
- The estimated implementation timeline of the laboratory activity for each week is as follows:

  A) Week 1 (February 3-5): The design notes are written in a document to be submitted and apply initial commits of folder creation and README file in the group’s designated GitHub repository.

  B) Week 2 (February 9-11): Before the second PR appointment, initial progress on the activity is expected; the main features of the program will be applied as the draft version of the output. The code should have meaningful comments even in the early stages of progress. GitHub repositories are to have meaningful commit messages and comments from both members.

  C) Week 3 (February 12-18): Before the third PR appointment, the output is expected to be fully implemented and functional, and can run consistently as per the laboratory activity. The code would have better documentation, suggestions from the previous consultation meeting are seen to be applied, and the repository would have progressively clean commit history from both members, stating issues and concerns.

  D) Week 4 (February 21-26): Code is expected to be finished and refactored from the previous week’s consultation appointment, and ready to be defended. The repository’s Members are expected to have their peer.txt files ready and their commits fully up to date with their local file copies (as well as additional refractors during defense), as well as have other required laboratory deliverables submitted on or before the last day of the laboratory 1 defense window.



