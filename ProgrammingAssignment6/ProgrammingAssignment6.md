#Operating System
##Programming Assignment - 6

###Algorithm Used
First In First Out, Least Recently Used and Optimal Policy

###Programing Language Used
Python

###Operating System 
Mac OS

### First In First Out:
Code output-

Page Request:
####[10, 8, 10, 2, 15, 14, 6, 13, 11, 13, 10, 12, 8, 13, 2, 8]


```
Performing FIFO
Page request  10  =>  [10] 
Page request  08  =>  [10, 8] 
Page request  10  =>  [10, 8] 
Page request  02  =>  [10, 8, 2] 
Page request  15  =>  [10, 8, 2, 15] 
Page request  14  =>  [10, 8, 2, 15, 14] 
Page request  06  =>  [8, 2, 15, 14, 6]    ---->PageFault
Page request  13  =>  [2, 15, 14, 6, 13]    ---->PageFault
Page request  11  =>  [15, 14, 6, 13, 11]    ---->PageFault
Page request  13  =>  [15, 14, 6, 13, 11] 
Page request  10  =>  [14, 6, 13, 11, 10]    ---->PageFault
Page request  12  =>  [6, 13, 11, 10, 12]    ---->PageFault
Page request  08  =>  [13, 11, 10, 12, 8]    ---->PageFault
Page request  13  =>  [13, 11, 10, 12, 8] 
Page request  02  =>  [11, 10, 12, 8, 2]    ---->PageFault
Page request  08  =>  [11, 10, 12, 8, 2] 
```
####Total number of page faults in FIFO =  7

###Least Recently Used:
Code output-

Page Request:
####[10, 8, 10, 2, 15, 14, 6, 13, 11, 13, 10, 12, 8, 13, 2, 8]

```
Performing LRU
Page request  10  =>  [10] 
Page request  08  =>  [10, 8] 
Page request  10  =>  [10, 8] 
Page request  02  =>  [10, 8, 2] 
Page request  15  =>  [10, 8, 2, 15] 
Page request  14  =>  [10, 8, 2, 15, 14] 
Page request  06  =>  [10, 2, 15, 14, 6]    ---->PageFault
Page request  13  =>  [10, 15, 14, 6, 13]    ---->PageFault
Page request  11  =>  [10, 14, 6, 13, 11]    ---->PageFault
Page request  13  =>  [10, 14, 6, 13, 11] 
Page request  10  =>  [10, 14, 6, 13, 11] 
Page request  12  =>  [10, 6, 13, 11, 12]    ---->PageFault
Page request  08  =>  [10, 13, 11, 12, 8]    ---->PageFault
Page request  13  =>  [10, 13, 11, 12, 8] 
Page request  02  =>  [10, 13, 12, 8, 2]    ---->PageFault
Page request  08  =>  [10, 13, 12, 8, 2] 
```
####Total number of page faults in LRU =  6

###Optimal Policy:
Code output-

Page Request:
####[10, 8, 10, 2, 15, 14, 6, 13, 11, 13, 10, 12, 8, 13, 2, 8]

```
Performing Optimal Policy
Page request  10  =>  [10] 
Page request  08  =>  [10, 8] 
Page request  10  =>  [10, 8] 
Page request  02  =>  [10, 8, 2] 
Page request  15  =>  [10, 8, 2, 15] 
Page request  14  =>  [10, 8, 2, 15, 14] 
Page request  06  =>  [10, 8, 2, 15, 6]    ---->PageFault
Page request  13  =>  [10, 8, 2, 15, 13]    ---->PageFault
Page request  11  =>  [10, 8, 2, 13, 11]    ---->PageFault
Page request  13  =>  [10, 8, 2, 13, 11] 
Page request  10  =>  [10, 8, 2, 13, 11] 
Page request  12  =>  [10, 8, 2, 13, 12]    ---->PageFault
Page request  08  =>  [10, 8, 2, 13, 12] 
Page request  13  =>  [10, 8, 2, 13, 12] 
Page request  02  =>  [10, 8, 2, 13, 12] 
Page request  08  =>  [10, 8, 2, 13, 12] 
```
###Total number of page faults in OPT =  4

Running for 10 cases:

| PageRequest  | FIFO PageFaults#  | LRU PageFaults# | Optimal Policy PageFaults#
|:------------- |:---------------:| -------------:| -----------------------------:|
| [13, 15, 12, 8, 13, 2, 2, 2, 2, 13, 7, 11, 15, 8, 1, 1]     | 4 |         5 | 3
| [8, 7, 13, 10, 15, 2, 1, 2, 6, 12, 3, 4, 2, 12, 10, 6]     | 9 |         8 | 6
| [15, 2, 15, 6, 13, 7, 15, 3, 13, 5, 15, 3, 11, 6, 9, 9]     | 6 |         5 | 4
| [8, 15, 9, 6, 10, 11, 6, 1, 2, 9, 8, 9, 3, 7, 7, 15]     | 8 |         8 | 5
| [15, 5, 3, 5, 8, 14, 10, 9, 8, 4, 5, 10, 12, 5, 2, 15]     | 7 |         6 | 5
| [3, 3, 10, 11, 6, 1, 10, 9, 14, 5, 10, 3, 13, 5, 15, 4]     | 8 |         6 | 6
| [4, 6, 3, 6, 7, 7, 2, 4, 10, 6, 8, 14, 4, 2, 6, 5]     | 6 |         5 | 4
| [10, 7, 10, 5, 4, 4, 9, 13, 9, 8, 11, 12, 11, 6, 2, 13]     | 7 |         7 | 6
| [15, 4, 10, 1, 11, 9, 15, 8, 15, 10, 14, 3, 10, 1, 9, 4]     | 9 |         9 | 5
| [13, 9, 10, 3, 8, 3, 14, 11, 5, 14, 12, 6, 10, 8, 14, 13]     | 9 |         8 | 5
| Average Page Faults | 7.3| 6.7| 4.9


###Conclusion:
As per above results, It can be concluded that:

Optimal policy is better than LRU and FIFO.

LRU is better than FIFO.
