n/*
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
} data;
typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

typedef struct queueMsgbuf {
    long    mtype;
    int    queueNumber;
} queueMessage_buf;

time_t start, stop; /* time for stopping prog after some time*/
pid_t wpid;
pid_t myPid, childPid;
FILE *file;
//int cpn = 0;
int status;
int numberOfSlaves = 5;
int numberOfIncrements = 1;
int terminationTime = 30;
char fileName[];
int totalProcessCount = 0;

key_t sendQueueMsgKey;
sendQueueMsgKey = 1948;
int sendQueueMsgFlag = 1;
int totalNumberOfLogs = 0;
key_t logMsgKey;
logMsgKey = 1235;





void help(){
    printf("Usage: ./main [-ha:s:l:i:t:n] [args]\n");
    printf("\t -h --help: to get help\n");
    printf("\t -s --number of slaves\n");
    printf("\t -t --total time for termination of program\n");
    printf("\t -i --number of times slave writes to file\n");
    printf("\t -l: to specify the log file name. defaut value is logfile.txt\n");
    printf("\t args: takes the message to be posted in log\n");
    
}
void cleanUp(){
    //Delete the message queues
    msgctl(sendQueueMsgKey, IPC_RMID, NULL);
    msgctl(logMsgKey, IPC_RMID, NULL);
    printf("***************Cleaned up queue******************");
}

void killProcess() {
    kill(-getpgrp(), SIGQUIT);
    cleanUp();
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
void sendQueueMsg(int queueId){
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
    
    if ((msqid = msgget(sendQueueMsgKey, msgflg )) < 0) {
        perror("msgget");
        //exit(1);
    }
    
    sbuf.mtype = 1;

    sbuf.queueNumber = queueId;
    buf_length = sizeof(sbuf.queueNumber);
    
    
    
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
int checkMsgReceived(int seconds, int nanoSeconds){
    int msqid;
    
    message_buf  rbuf;
    //
    //
        //
    if ((msqid = msgget(logMsgKey, 0666)) < 0) {
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

        strcat(str, "\n");
        (void) strcpy(str,rbuf.mtext);

        strcat(str, "\n");
        file = fopen(fileName, "a");
        fprintf(file,str);
        totalNumberOfLogs + 1;
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
        /* creating slaves*/
        totalProcessCount =totalProcessCount +1;
        childPid = fork();
        int processId = childPid;
//        printf("processNumber = %d \n", processId);
        if(childPid < 0) {
            perror("Fork Failure");
            exit(1);
        }else if(childPid == 0) {
            /////////////////
            //OSS: Generating process with PID 3 and putting it in queue 1 at time 0:5000015
            ///////////////
            char str[150];
            totalNumberOfLogs = totalNumberOfLogs + 1;
            strcpy(str, "\nOSS: Generating process with PID");
            char temp1[15];
            sprintf(temp1,"%d",  getpid());
            strcat(str, temp1);
            strcat(str, " and putting it in queue 1");
            
            
            strcat(str, "\n");
            file = fopen(fileName, "a");
            fprintf(file,str);
            
            if(fclose(file)) {
                perror("    Error closing file");
            }
            /////////////////////
            /////////////////////

            pid_t gpid = getpgrp();
            char *nValue = malloc(20);
//            printf("MASTER::processNumber = %d \n", processId);
            sprintf(nValue, "%d", getpid());
            //            sprintf(iValue, "%d", numberOfIncrements);
            char *slaveOptions[] = {"./slave", "-n", nValue, (char *)0};
            
            int execCmd = execv("./slave", slaveOptions);
            
        }
    }
}
void test(){
    int key, mask, msgid;
    
    key = getuid();
    mask = 0666;
    msgid = msgget(key, mask);
    
    if (msgid == -1) {
        printf("Message queue does not exist.\n");
        //exit(EXIT_SUCCESS);
    }
    
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        fprintf(stderr, "Message queue could not be deleted.\n");
        //exit(EXIT_FAILURE);
    }
    
    printf("Message queue was deleted.\n");
}
int main(int argc, char *argv[]) {
    printf("**************Program Started****************************");
//    test();
    signal(SIGALRM, handleInterrupts);
    signal(SIGINT, handleInterrupts);
    start = time(NULL);
    int shmid;
    key_t key;
    char *shm;
    char *s;
    key = 9878;
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
//    printf("number of precesses are %d", numberOfSlaves);
    spawnProcess(numberOfSlaves);
    
    int j = 1;
    sharedStates->seconds = 0;
    sharedStates -> nanoSeconds = 0;
    int tempFlagQueue = 1;
    int tempFlagQueueSecs = 0;
    while (1) {
        
        sharedStates -> nanoSeconds = sharedStates -> nanoSeconds + 125000000;//31250000
        
        if (sharedStates -> nanoSeconds >= 1000000000) {
            sharedStates -> seconds = sharedStates -> seconds + 1;
            sharedStates -> nanoSeconds = 0;
            tempFlagQueueSecs = tempFlagQueueSecs + 1;
        }
        
        if(checkMsgReceived(sharedStates->seconds, sharedStates->nanoSeconds) == 1){
            if (totalProcessCount <= 20) {
                spawnProcess(1);
            }
            
        }
        printf("seconds = %d",sharedStates -> seconds);
        if (sharedStates -> seconds >= terminationTime || totalNumberOfLogs >= 150) {
            printf("Inside condition break");
            printf("totalProcessCount = %d",totalProcessCount);
            printf("terminationTime = %d",terminationTime);
            printf("sharedStates -> seconds = %d",sharedStates -> seconds);
            cleanUp();
            break;
        }
        
        if (sendQueueMsgFlag == 1 ) {
            sendQueueMsg(2);
            sendQueueMsgFlag =0;
            //            sleep(1);
            //            sendQueueMsg(3);
            //            sendQueueMsgFlag = 0;
        }
        //        sleep(0.1);
        if (sendQueueMsgFlag == 0) {
            sendQueueMsg(3);
            sendQueueMsgFlag = 1;
            //            sleep(1);
            //            sendQueueMsg(3);
            //            sendQueueMsgFlag = 0;
        }
        
        /*
        if (sendQueueMsgFlag == 1 && sharedStates -> nanoSeconds <= 500000000) {
            sendQueueMsg(2);
//            sleep(1);
//            sendQueueMsg(3);
//            sendQueueMsgFlag = 0;
        }
//        sleep(0.1);
        if (sendQueueMsgFlag == 1 && sharedStates -> nanoSeconds > 500000000) {
            sendQueueMsg(3);
            //            sleep(1);
            //            sendQueueMsg(3);
            //            sendQueueMsgFlag = 0;
        }
         */
        if (tempFlagQueueSecs >10) {
            tempFlagQueueSecs = 0;
        }
        
    }
    while ((wpid = wait(&status)) > 0);
    wait(NULL);
    cleanUp();
    return 0;
}

