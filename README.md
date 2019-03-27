# Starbucks Simulator


## Compiling
- The compiling computer must have the ncurses dev libraries installed
    `sudo apt-get install libncurses5-dev` on the CMPUT 274 VM
    `libncursesw10, libncurses-devel` in Cygwin installer
- Must be compiled with g++ (not gcc)
- Must include the ncurses library when linking (`-lncurses`)
Note that the two points directly above are handled by the Makefile


## Sources
- posMod() in choices class: https://stackoverflow.com/a/14997413


## Limitations
Much of ncurses' functionality relies on the terminal being used.
