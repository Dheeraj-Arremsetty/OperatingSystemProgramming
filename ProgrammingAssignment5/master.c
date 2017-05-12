/*
 *  *Author: o1-arremsetty
 *   *Name: Dheeraj Arremsetty
 *    *Student Id: 18157201
 **/
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#define SHSIZE 100
#define MSGSZ     128
/* Below is the struct for shared memory*/
typedef struct data_struct {
    int sharedInt;
    int turn;
    int semid;
    int seconds;
    int nanoSeconds;
    int resource1;
    int resource2;
} data;
typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

typedef struct queueMsgbuf {
    long    mtype;
    int    processNumber;
} queueMessage_buf;

time_t start, stop; /* time for stopping prog after some time*/
pid_t wpid;
pid_t myPid, childPid;
FILE *file;
key_t sendQueueMsgKey;
sendClientMsgKey = 1948;
//int cpn = 0;
int status;
int numberOfSlaves = 5;
int numberOfIncrements = 1;
int terminationTime = 2;
char fileName[];
int totalProcessCount = 0;
int status;





void help(){
    printf("Usage: ./main [-ha:s:l:i:t:n] [args]\n");
    printf("\t -h --help: to get help\n");
    printf("\t -s --number of slaves\n");
    printf("\t -t --total time for termination of program\n");
    // printf("\t -i --number of times slave writes to file\n");
    printf("\t -l: to specify the log file name. defaut value is logfile.txt\n");
    printf("\t args: takes the message to be posted to generate sys clock\n");
    
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
        strcpy(str,"\n");
        strcat(str,"PID");
        strcat(str,rbuf.mtext);
        char temp[15];
//        sprintf(temp,"%d", childPid);
//        strcat(str, temp);
        strcat(str,": is in deadlock.");
//        sprintf(temp,"%d", seconds);
//        strcat(str, temp);
//        strcat(str,".");
//        sprintf(temp,"%d", nanoSeconds);
//        strcat(str, temp);
//        strcat(str, rbuf.mtext);
//        strcat(str, "\n");
        printf("%s \n", str);
        
        file = fopen(fileName, "a");
        fprintf(file,str);
        
        if(fclose(file)) {
            perror("    Error closing file");
        }
        
        
        
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
            
            
            char str[150];
            strcpy(str, "\nOSS: Generating process with PID");
            char temp1[15];
            sprintf(temp1,"%d",  getpid());
            strcat(str, temp1);
            file = fopen(fileName, "a");
            fprintf(file,str);
            if(fclose(file)) {
                perror("    Error closing file");
            }
            
            childPid = getpid();
            pid_t gpid = getpgrp();
            
            
            char *nValue = malloc(20);
            sprintf(nValue, "%d", getpid());
            char *slaveOptions[] = {"./slave", "-n", nValue, (char *)0};
            
            int execCmd = execv("./slave", slaveOptions);
            
        }
    }
}

void sendMsgTwoClient(int processNumber){
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    queueMessage_buf sbuf;
    size_t buf_length;
    
    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    
    
    //(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,%#o)\n",key, msgflg);
    
    if ((msqid = msgget(sendClientMsgKey, msgflg )) < 0) {
        perror("msgget");
        //exit(1);
    }
    
    sbuf.mtype = 1;
    
    sbuf.processNumber = processNumber;
    buf_length = sizeof(sbuf.processNumber);
    
    
    
    /*
     * Send a message.
     */
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
        //perror("msgsnd");
        exit(1);
    }
    
    //    else
    //printf("Message: \"%s\" Sent\n", sbuf.mtext);
    
    //exit(0);
    
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
    
    sharedStates -> resource1 = -1;
    sharedStates -> resource2 = -1;
    while (1) {
        printf("sharedStates -> seconds = %d",sharedStates -> seconds);
        sharedStates -> nanoSeconds = sharedStates -> nanoSeconds + 125000000;//31250000
        //        sharedStates -> nanoSeconds = sharedStates -> nanoSeconds + 125000000;//31250000
        
        if (sharedStates -> nanoSeconds >= 1000000000) {
            sharedStates -> seconds = sharedStates -> seconds + 1;
            sharedStates -> nanoSeconds = 0;
        }
        
        
//        totalProcessCount >= 10 ||
        
        if ( totalProcessCount >= 10 || sharedStates -> seconds >= terminationTime) {
            break;
        }
        if(checkMsgReceived(sharedStates->seconds, sharedStates->nanoSeconds) == 1){
            spawnProcess(1);
        }
        
    }
//    while ((wpid = wait(&status)) > 0);
    wait(NULL);
    return 0;
}
