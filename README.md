# CUSTOM SHELL

This project is a custom shell implementationusing system calls.This shell is capable of parsing user's input and executes the necessary system calls, it also handles input output redirection.

# Features
1. Input parsing :
    Tokenizing the user input by splitting at the white space.

2. Handling builtin commands seperately:
    Identifying the user's command.Handle it seperately if it is a builtin function.

3. Check and Handle input output Redirection:
    Checking if the command needs input/output redirection and making necessary changes to the file descriptor table.

3. Run Executables using system calls.
    Using System calls to run the executables.

# Process Tree Snapshot
![Process Tree](pstreeSnapshot.png "Optional Title")

# Usage 
1. Run 'make' to build the binary.

2. Run 'make run' to execute the custom shell. 

3. Try commands like cd,ls,help,echo or try to run custom programs.