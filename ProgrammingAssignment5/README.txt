Name: Dheeraj Arremsetty
StudentId: 18157201
Date of Submission: 05-01-2017
Assignment 5



This program simulates process accessing resources and gets into deadlock state. 
Sample output:
OSS: Generating process with PID16352
OSS: Generating process with PID16353
OSS: Generating process with PID16354
OSS: Generating process with PID16356
OSS: Generating process with PID16355
Process with PID16352 waiting for resources.
Process with PID16353 waiting for resources.
Resources allocated to PID16353 waiting for resources.
Process with PID16352 accesing resources.
Process with PID16353 accesing resources.
Process with PID16352 is terminating.
Process with PID16353 is terminating.
Process with PID16352 is terminating.
Process with PID16356 waiting for resources.
Process with PID16354 waiting for resources.
Resources allocated to PID16354 waiting for resources.
Process with PID16356 is in deadlock.
Process with PID16354 accesing resources.
Process with PID16354 is terminating.
Process with PID16355 waiting for resources.
Resources allocated to PID16355 waiting for resources.
Process with PID16355 accesing resources.
Process with PID16355 is terminating.



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

