# minibusybox
Simple busybox clone. Just like the real one, it uses symlinks to execute a certain command. All available commands were implemented by me and are contained as functions inside the program.
## Available commands
- cat
- mkdir
- sleep
- touch
## How does it work?
It uses command line arguments to determine which function to execute. `argv[0]` contains the name of the executable, changing if it was executed from a symlink, and if the name matches any of the available commands, it executes the corresponding function.
## Compiling
Just use the Makefile to automate the process. Alternatively, you can use `gcc` to manually compile the program, it doesn't need any external libraries or anything, but you'd have to create the symlinks yourself.
