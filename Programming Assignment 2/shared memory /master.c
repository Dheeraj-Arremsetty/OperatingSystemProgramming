/*
 *Author: o1-arremsetty
 *Name: Dheeraj Arremsetty
 *Student Id: 18157201
 */

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#define SHSIZE 100
/* Below is the struct for shared memory*/
typedef struct data_struct {
    int sharedInt;
    int turn;
    int semid;
} data;
pid_t myPid, childPid;
int status;
int numberOfSlaves = 5;
int numberOfIncrements = 1;
int terminationTime = 20;
char fileName[];

time_t start, stop; /* time for stopping prog after some time*/
void help(){
    printf("Usage: ./main [-ha:s:l:i:t:n] [args]\n");
    printf("\t -h --help: to get help\n");
    printf("\t -s --number of slaves\n");
    printf("\t -t --total time for termination of program\n");
    printf("\t -i --number of times slave writes to file\n");
    printf("\t -l: to specify the log file name. defaut value is logfile.txt\n");
    printf("\t args: takes the message to be posted in log\n");
    
}
void killProcess() {
    kill(-getpgrp(), SIGQUIT);
    printf("**************Killing all the process****************");
}

void handleInterrupts(int SIG){
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    
    if(SIG == SIGINT) {
        printf( "\n%sCTRL-C received. Calling shutdown functions.%s\n");
    }
    
    if(SIG == SIGALRM) {
        printf( "%sMaster has timed out. Initiating shutdown sequence.%s\n");
    }
    
    killProcess();
    abort();
}


int main(int argc, char *argv[]) {
    printf("**************Program Started****************************");
    signal(SIGALRM, handleInterrupts);
    signal(SIGINT, handleInterrupts);
    start = time(NULL);
    int shmid;
    key_t key;
    char *shm;
    char *s;
    key = 9876;
    data *sharedStates;
    char *iValue = malloc(20);
    char *nValue = malloc(20);
    shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
    int randomnumber;
    
    
    int cmdOptions;
    int helpFlag = 0;
    while ((cmdOptions = getopt(argc, argv, "ha:s:l:i:t:n:k")) != -1) {
        switch (cmdOptions) {
            case 'h' :
                helpFlag = 1;
                break;
            case 's':
                if (optarg != NULL) {
                    numberOfSlaves = atoi(optarg);
                }
                break;
            case 'l' :
                if(optarg != NULL){
                    
                    strcpy(fileName, optarg);
                    
                }
            case 'i':
                if (optarg != NULL) {
                    numberOfIncrements = atoi(optarg);
                }
                break;
            case 't':
                if (optarg != NULL) {
                    terminationTime = atoi(optarg);
                }
                break;
        }
    }
    
    
    if (strlen(fileName) <1) {
        strcpy(fileName,"logfile.txt");
    }
    if (helpFlag == 1) {
        help();
        return NULL;
    }
    
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    

    
    if((sharedStates = (data *)shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("some memory problem...");
        exit(1);
    }

    sharedStates->sharedInt = 0;
    sharedStates->turn = 1;
    int processNumber =0;
    for (processNumber =0; processNumber < numberOfSlaves; processNumber++) {
        /*random number between 1 to 3*/
        randomnumber = (rand() % (2 + 1 - 1)) + 1;
        /* creating slaves*/
        if((childPid = fork()) < 0) {
            perror("Fork Failure");
            exit(1);
        }
        
        if(childPid == 0) {

            childPid = getpid();
            pid_t gpid = getpgrp();
            sprintf(nValue, "%d", processNumber);
            sprintf(iValue, "%d", numberOfIncrements);
            char *slaveOptions[] = {"./client", "-n", nValue,"-i", iValue, "-l",fileName ,(char *)0};

            int execCmd = execv("./client", slaveOptions);
            
            }
    }
    
    int j = 1;
    for(j = 1; j <= numberOfSlaves; j++) {
        
        stop = time(NULL);
        /* aborts when time ends*/
        if(stop-start > terminationTime) {
            printf("\nYour %d seconds is reached killing Master and slaves\n",terminationTime);
            killProcess();
            abort();

        }

        printf("Master: Child %d has died....\n", childPid);

    }
    
    wait(NULL);
    return 0;
}



