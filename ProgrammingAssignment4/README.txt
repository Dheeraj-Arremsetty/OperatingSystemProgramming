Name: Dheeraj Arremsetty
StudentId: 18157201
Date of Submission: 04-23-2017
Assignment 4

OSS

This program simulates process scheduling where process enters into different queues and executes with time quantum. Which continuesly compete to acces shared memory. 
Sample output:
OSS: Generating process with PID17287 and putting it in queue 1
OSS: Generating process with PID17289 and putting it in queue 1
OSS: Generating process with PID17290 and putting it in queue 1
 OSS: Dispatching process with 17286 from queue 1 at time 18 : 750000000
 OSS: Putting process with 17286 into queue 2 
OSS: Generating process with PID17291 and putting it in queue 1
 OSS: Dispatching process with 17286 from queue 2 at time 18 : 750000000
OSS: Generating process with PID17292 and putting it in queue 1
 OSS: Putting process with 17286 into queue 3 
 OSS: Dispatching process with 17286 from queue 2 at time 18 : 750000000
 OSS: Putting process with 17286 into queue 3 
OSS: Generating process with PID17288 and putting it in queue 1
OSS: Generating process with PID17293 and putting it in queue 1
 OSS: Dispatching process with 17290 from queue 1 at time 18 : 875000000
OSS: Generating process with PID17294 and putting it in queue 1
 OSS: Putting process with 17290 into queue 2 
 OSS: Dispatching process with 17290 from queue 2 at time 19 : 0
OSS: Generating process with PID17299 and putting it in queue 1
OSS: Dispatching process with 17290 from queue 2 at time 19 : 0
OSS: Generating process with PID17300 and putting it in queue 1



Build:
Application is integrated with makefile. Run 'make' in src directory to generate binaries.
Usage is discussed in the next section.

Usage:
./oss [-ha:s:l:i:t:n] [args]
     -h --help: to get help\n");
     -s --number of slaves\n");
     -t --total time for termination of program\n");
     -l: to specify the log file name. defaut value is logfile.txt in append mode.

Command to run:

./oss

-OR-

./oss -l filename.txt

