This is a Branch Target Buffer project.
The idea is that the program will scan through a .txt trace of program 
counter addresses from some program being run. Each time a branch or 
jump occurs, the program calculates an entry number basesd on the program
counter's current value, then stores in a 1024-length array the current and 
next values of the program counter. Also features a 2-bit state machine to
try to predict at each branch/jump address if the branch/jump will actually
be made or not, and if it will be made to the same place as last time.

BTB's are used in processors to mark when programs utilize loops so that 
a guess on what instructions will be processed next will be made. This helps
efficiency greatly because if the processor is exeucting something like a for loop,
it can know what to expect next.
