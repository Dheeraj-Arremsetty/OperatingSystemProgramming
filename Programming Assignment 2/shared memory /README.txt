Name: Dheeraj Arremsetty
StudentId: 18157201
Date of Submission: 03-11-2017
Assignment 2

Shared Memory

This program creates multiple processes, which shares common shared memory.
Sample output:
        File modified by process number 6 at time 1489270277 with shared number = 17
    File modified by process number 6 at time 1489270277 with shared number = 18
    File modified by process number 10 at time 1489270277 with shared number = 19
    File modified by process number 10 at time 1489270277 with shared number = 20
    File modified by process number 10 at time 1489270277 with shared number = 21
    File modified by process number 8 at time 1489270277 with shared number = 22
    File modified by process number 8 at time 1489270277 with shared number = 23
    File modified by process number 8 at time 1489270277 with shared number = 24
    File modified by process number 9 at time 1489270277 with shared number = 25
    File modified by process number 9 at time 1489270277 with shared number = 26
    File modified by process number 9 at time 1489270277 with shared number = 27
    File modified by process number 5 at time 1489270277 with shared number = 28
    File modified by process number 5 at time 1489270277 with shared number = 29
    File modified by process number 5 at time 1489270277 with shared number = 30


Build:
Application is integrated with makefile. Run 'make' in src directory to generate binaries.
Usage is discussed in the next section.

Usage:
./main [-ha:s:l:i:t:n] [args]
     -h --help: to get help\n");
     -s --number of slaves\n");
     -t --total time for termination of program\n");
     -i --number of times slave writes to file\n");
     -l: to specify the log file name. defaut value is logfile.txt

Command to run:

./master

-OR-

./master -s 10 -i 3
