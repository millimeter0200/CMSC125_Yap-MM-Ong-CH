# CMSC125_Yap-MM-Ong-CH

CMSC 125-1 LAB 1
ONG, CHRISTEL HOPE
YAP, MAE MARICAR

I. Compilation and usage instructions
    1. Open Ubuntu
    2. Compile with: "gcc -Wall -Wextra src/*.c -Iinclude -o mysh"
    3. Run with: "./mysh"
    4. Should display "mysh >"
    5. Enter commands
    6. Exit with Ctrl C to stop

II. List of implemented features
    
    1. Shell continuously accepts user input, cleans up finished bg processes before each prompt, then ignores empty input
    
    2. Built-in Commands are exit, cd, pwd execute in the parent process.
    
    3. Execute external command; uses fork() to create child process, child executes command via execvp(), and the parent waits for foreground processes and does not wait for bg processes

    4. Background Execution
    -commands followed by & run in background
    -background PIDs are stored in a job list
    -completed background jobs are reaped using waitpid(..., WNOHANG)
    -prevents zombie processes

    5. Command Parsing
    The parser tokenizes input using whitespacem, detects special operators, and populates a Command structure containing the command name, argument list, input/output file, append flag, background flag

    6. Input/output redirection for standard input (<), output (> overwrite and >> append) applied in child proces before execvp so executed programs inherit meodified file descriptors.

III. Known limitations or bugs
    No pipeline and quoting support. Limited argument count, Basic error reporting, and no job control commands.
    
IV. Design decisions and architecture overview
    shell divided into 5 modules: main, parser, executor, jobs, and command in C. 
    
V. Screenshots showing functionality

DESIGN NOTES (Lab1)

I. Problem Refinement
For Week 2, the focus shifted from planning to concrete implementation of the core shell workflow. The primary objective was to complete command parsing and integrate it with execution while maintaining modular separation between components.

The shell must accept raw input, parse input into a structured form, execute commands correctly, support background execution, and prevent zombie processes.

II. Completed Features (Week 2)
1. Full Command Parsing Implementation
  The parser module was implemented to:
    - Remove newline characters from input
    - Tokenize input using strtok() with whitespace delimiters
    - Detect and validate special operators:
      < for input redirection
      > for output redirection
      >> for append mode
      & for background execution
    - Populate the Command structure fields accordingly
    - Ensure arguments are NULL-terminated for execvp()
    - Reject malformed operator usage
  (establishes structured data transfer between parsing & execution layers)

2. Main Shell Workflow Integration
Main loop now performs: 
    1. Reap completed background processes
    2. Display prompt
    3. Read input using fgets
    4. Ignore empty input
    5. Initialize Command structure
    6. Parse input
    7. Execute parsed command
    8. Free command resources
cleanup-> prompt -> read -> parse-> execute -> repeat

3. Execution Module Improvements
  - Detects built-in commands exit, cd, pwd
  - Executes built-ins in the parent process
  - Uses fork() to create child processes for external commands
  - Executes programs using execvp()
  - Waits for foreground processes
  - Registers background processes in job list
  (align with the standard UNIX shell execution flow)

4. Background Job Management Refactoring
    The background job system was modularized into jobs.c:
    - Maintains an internal array of background PIDs
    - Uses waitpid(..., WNOHANG) to detect completed jobs
    - Removes finished jobs from tracking list
    - Prevents zombie processes
    (For improving the separation of concerns and modular design)

V. Timeline
Week 1:
-Design notes (problem, requirements, and timeline)
-initial commits + skeleton of header files and src files 
     
Week 2:
-Parser fully implemented
-Executor integrated with parser
-Bg job management functional
-Modular structure stabilized

Week 3:
-Implement redirection execution
-Perform testing and debugging
-Improve code documentation

Week 4:
-Final refactoring
-Optimization
-Defense preparation
-Submission of complete documentation



