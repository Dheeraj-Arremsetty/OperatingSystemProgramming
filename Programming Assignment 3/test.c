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
#define MSGSZ     128
/* Below is the struct for shared memory*/
typedef struct data_struct {
    int sharedInt;
    int turn;
    int semid;
    int seconds;
    int nanoSeconds;
} data;
typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;
time_t start, stop; /* time for stopping prog after some time*/

pid_t myPid, childPid;
//int cpn = 0;
int status;
int numberOfSlaves = 5;
int numberOfIncrements = 1;
int terminationTime = 20;
char fileName[];
int totalProcessCount = 0;





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
int checkMsgReceived(int seconds, int nanoSeconds){
    int msqid;
    key_t key;
    message_buf  rbuf;
    //
    //
    key = 1236;
    //
    if ((msqid = msgget(key, 0666)) < 0) {
        //perror("msgget");
        //exit(1);
    }
    //
    //
    //    /*
    //     * Receive an answer of message type 1.
    //     */
    //    printf("Comming here");
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        //perror("msgrcv");
        //        //exit(1);
        return 0;
    }
    else{
        //
//        printf("RECEIVED = %s\n", rbuf.mtext);
//        printf("childPid = %d",childPid);
        
        //Child pid is terminating at my time xx.yy
        char str[150];
        strcpy(str,"Master: Child ");
        char temp[15];
        sprintf(temp,"%d", childPid);
        strcat(str, temp);
        strcat(str," is terminating at my time ");
        sprintf(temp,"%d", seconds);
        strcat(str, temp);
        strcat(str,".");
        sprintf(temp,"%d", nanoSeconds);
        strcat(str, temp);
        strcat(str, rbuf.mtext);
        printf("%s \n", str);
        
        
        
        
        return 1;
    }
    return 0;
}

void spawnProcess(int numberOfSlaves){
    
    int processNumber =0;
    for (processNumber =0; processNumber < numberOfSlaves; processNumber++) {
        /*random number between 1 to 3*/
        //randomnumber = (rand() % (2 + 1 - 1)) + 1;
        /* creating slaves*/
        totalProcessCount =totalProcessCount +1;
        childPid = fork();
        if(childPid < 0) {
            perror("Fork Failure");
            exit(1);
        }else if(childPid == 0) {
            printf("childPid ------------= %d",childPid);
            childPid = getpid();
            pid_t gpid = getpgrp();
//            sprintf(nValue, "%d", processNumber);
//            sprintf(iValue, "%d", numberOfIncrements);
            char *slaveOptions[] = {"./slave", (char *)0};
            
            int execCmd = execv("./slave", slaveOptions);
            
        }
    }
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
    spawnProcess(numberOfSlaves);
    
    int j = 1;
    sharedStates->seconds = 0;
    sharedStates -> nanoSeconds = 0;
    while (1) {
        
        sharedStates -> nanoSeconds = sharedStates -> nanoSeconds + 31250000;
        
        if (sharedStates -> nanoSeconds >= 1000000000) {
            sharedStates -> seconds = sharedStates -> seconds + 1;
            sharedStates -> nanoSeconds = 0;
        }
        
        if(checkMsgReceived(sharedStates->seconds, sharedStates->nanoSeconds) == 1){
            spawnProcess(1);
        }
        if (totalProcessCount >= 100 || sharedStates -> seconds >=2) {
            break;
        }
        
    }
    
    wait(NULL);
    return 0;
}
