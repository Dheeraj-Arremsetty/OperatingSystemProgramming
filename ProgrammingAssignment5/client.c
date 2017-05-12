/*
 *Author: o1-arremsetty
 *Name: Dheeraj Arremsetty
 *Student Id: 18157201
 */
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <getopt.h>
#define SHSIZE 100

typedef struct data_struct {
    int sharedInt;
    int turn;
    int semid;
    int seconds;
    int nanoSeconds;
    int resource1;
    int resource2;
} data;
int processNumber = 0;
char fileName[];
FILE *file;

#define MSGSZ     128

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

typedef struct queueMsgbuf {
    long    mtype;
    int    processNumber;
} queueMessage_buf;

key_t sendQueueMsgKey;
sendClientMsgKey = 1948;


int checkQueueMessageReceived(){
    int msqid;
    
    queueMessage_buf  rbuf;
    if ((msqid = msgget(sendClientMsgKey, 0666)) < 0) {
        //perror("msgget");
        //exit(1);
    }
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        return 0;
    }
    else{
        //        printf("Received Queue numnber = %d", rbuf.queueNumber);
        return rbuf.processNumber;
    }
    return -1;
}

writeToFile(char strContent[]){
    char str[150];
    strcpy(str, strContent);
    file = fopen(fileName, "a");
    fprintf(file,str);
    if(fclose(file)) {
        perror("    Error closing file");
    }

}

sendMsg(int processNumber){
    
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    size_t buf_length;
    
    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 1236;
    
    //(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,%#o)\n",key, msgflg);
    
    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
    }
    sbuf.mtype = 1;
    
    ///////////
    char str[150];
    strcpy(str,"");
    char temp[15];
    sprintf(temp,"%d", processNumber);
    strcat(str, temp);
    (void) strcpy(sbuf.mtext, str);
    buf_length = strlen(sbuf.mtext) + 1 ;
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    //printf("comming in client");
    int shmid;
    key_t key;
    char *shm;
    char *s;
    key = 9876;
    data *sharedStates;
    int numberOfTimesNeedToWriteToFile = 1;
    int randomnumber;
    shmid = shmget(key, SHSIZE,0666);
    int cmdOptions;
    int helpFlag = 0;
    while ((cmdOptions = getopt(argc, argv, "h:s:l:i:t:n:x")) != -1) {
        switch (cmdOptions) {
                
            case 'n':
                if (optarg != NULL) {
                    processNumber = atoi(optarg);
                }
                break;
                
            case 'i':
                if (optarg != NULL) {
                    numberOfTimesNeedToWriteToFile = atoi(optarg);
                }
                break;
                
            case 'l':
                if (optarg != NULL) {
                    strcpy(fileName,optarg);
                }
                break;
        }
    }
    if (strlen(fileName) <1) {
        strcpy(fileName,"logfile.txt");
    }
    
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    if((sharedStates = (data *)shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("some memory problem...");
        exit(1);
    }
    time_t times = time(NULL);
    int x =0;
    
    while (1) {
        randomnumber = (rand() % (2 + 1 - 1)) + 1;
        if (sharedStates->turn == 1 || 1) {
            
            sharedStates->turn = 0;//lock
            if (sharedStates -> resource1 == -1) {
                sharedStates->resource1 = processNumber;
            }
            sleep(randomnumber);
            int seconds = sharedStates->seconds;
            int nanoSeconds = sharedStates->nanoSeconds;
//            sharedStates->turn = 1;//Unlock
            if (sharedStates -> resource2 == -1) {
                sharedStates->resource2 = processNumber;
            }
//            sleep(1);
//            if (sharedStates -> resource1 == -1) {
//                sharedStates->resource1 = processNumber;
//            }
//            printf("\n sharedStates->resource2 = %d sharedStates->resource1 =%d",sharedStates->resource1,sharedStates->resource2);
            char str[150];
            strcpy(str, "\nProcess with PID");
            char temp1[15];
            sprintf(temp1,"%d",  getpid());
            strcat(str, temp1);
            strcat(str, " waiting for resources.");
            writeToFile(str);
            if (sharedStates->resource1 == processNumber && sharedStates->resource2 == processNumber) {
//                printf("\nprocess number %d accessing resources",processNumber);
                strcpy(str, "");
                strcat(str, "\nProcess with PID");
                sprintf(temp1,"%d",  getpid());
                strcat(str, temp1);
                strcat(str, " accesing resources.");
                writeToFile(str);
                sharedStates->resource1 = -1;
                sharedStates->resource2 = -1;
                char str1[150];
                strcpy(str1, "\nProcess with PID");
                char temp2[15];
                sprintf(temp2,"%d",  getpid());
                strcat(str1, temp2);
                strcat(str1, " is terminating.");
                writeToFile(str1);
                kill(1);
                break;

            }
            
            if ( (sharedStates->resource1 == processNumber && sharedStates->resource2 != processNumber) || (sharedStates->resource1 != processNumber && sharedStates->resource2 == processNumber)) {
//                printf("\nprocess number %d is in deadlock",processNumber);
                sprintf(temp1,"%d",  processNumber);
                strcpy(str,"");
                strcpy(str, "\nProcess with PID");
                strcat(str, temp1);
                strcat(str, " is in deadlock.");
                writeToFile(str);
                sendMsg(processNumber);
                kill(1);
//                sleep(0.5);
                
            }else{
            
                char str[150];
                strcpy(str, "\nResources allocated to PID");
                char temp1[15];
                sprintf(temp1,"%d",  getpid());
                strcat(str, temp1);
                strcat(str, " waiting for resources.");
                writeToFile(str);
                
                strcpy(str, "");
                strcat(str, "\nProcess with PID");
                sprintf(temp1,"%d",  getpid());
                strcat(str, temp1);
                strcat(str, " accesing resources.");
                writeToFile(str);

                
                break;
            }
            sleep(rand());
            
//            break;
        }
    }
    char str[150];
    strcpy(str,"");
    strcpy(str, "\nProcess with PID");
    char temp1[15];
    sprintf(temp1,"%d",  getpid());
    strcat(str, temp1);
    strcat(str, " is terminating.");
    writeToFile(str);
    return 0;
}
