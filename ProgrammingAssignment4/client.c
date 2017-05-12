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
} data;

#define MSGSZ     128

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

typedef struct queueMsgbuf {
    long    mtype;
    int    queueNumber;
} queueMessage_buf;

int processNumber = 0;
char fileName[];
FILE *file;


key_t sendQueueMsgKey;
sendQueueMsgKey = 1948;

int checkQueueMessageReceived(){
    int msqid;
    
    queueMessage_buf  rbuf;
        if ((msqid = msgget(sendQueueMsgKey, 0666)) < 0) {
        //perror("msgget");
        //exit(1);
    }
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        return 0;
    }
    else{
//        printf("Received Queue numnber = %d", rbuf.queueNumber);
        return rbuf.queueNumber;
    }
    return -1;
}
void sendMsg(int seconds, int nanoSeconds, int queueId){
    
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
    key = 1235;
    
    //(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,%#o)\n",key, msgflg);
    
    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        //exit(1);
    }
    
    sbuf.mtype = 1;
    
    if (queueId == 2) {
        
        ///////////
        //OSS: Dispatching process with PID 2 from queue 1 at time 0:5000805
        char str[150];
        strcpy(str,"\n OSS: Dispatching process with ");
        char temp[15];
        sprintf(temp,"%d", processNumber);
        strcat(str, temp);
        strcat(str," from queue 1 at time ");
        sprintf(temp,"%d", seconds);
        strcat(str, temp);
        strcat(str," : ");
        sprintf(temp,"%d", nanoSeconds);
        strcat(str, temp);
        strcat(str, "\n");

//        strcat(str, " in slave");
        (void) strcpy(sbuf.mtext, str);
        //printf("%s \n", sbuf.mtext);
        buf_length = strlen(sbuf.mtext) + 1 ;
        
        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            //perror("msgsnd");
            exit(1);
        }
        
        ///////
        //OSS: Putting process with PID 2 into queue 2
        char str1[150];
        strcpy(str1,"\n OSS: Putting process with ");
        char temp1[15];
        sprintf(temp1,"%d", processNumber);
        strcat(str1, temp1);
        strcat(str1," into queue 2 \n");
        (void) strcpy(sbuf.mtext, str1);
        buf_length = strlen(sbuf.mtext) + 1 ;
        printf("%s \n", str1);
        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            //perror("msgsnd");
            exit(1);
        }
        
    }else if(queueId == 3){
        ///////////
        //OSS: Dispatching process with PID 2 from queue 1 at time 0:5000805
        char str[150];
        strcpy(str,"\n OSS: Dispatching process with ");
        char temp[15];
        sprintf(temp,"%d", processNumber);
        strcat(str, temp);
        strcat(str," from queue 2 at time ");
        sprintf(temp,"%d", seconds);
        strcat(str, temp);
        strcat(str," : ");
        sprintf(temp,"%d", nanoSeconds);
        strcat(str, temp);
        strcat(str, "\n");
        
        //        strcat(str, " in slave");
        (void) strcpy(sbuf.mtext, str);
        //printf("%s \n", sbuf.mtext);
        buf_length = strlen(sbuf.mtext) + 1 ;
        
        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            //perror("msgsnd");
            exit(1);
        }
        ////////////////
        //OSS: Putting process with PID 2 into queue 2
        char str1[150];
        strcpy(str1,"\n OSS: Putting process with ");
        char temp1[15];
        sprintf(temp1,"%d", processNumber);
        strcat(str1, temp1);
        strcat(str1," into queue 3 \n");
        (void) strcpy(sbuf.mtext, str1);
        buf_length = strlen(sbuf.mtext) + 1 ;
        printf("%s \n", str1);
        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            //perror("msgsnd");
            exit(1);
        }
        
    }else if(queueId == 99){
        //Dummy queueId to send msg that time quantum is not used
        //OSS: not using its entire time quantum
        char str[150];
        strcpy(str," \nOSS: not using its entire time quantum");
      
        buf_length = strlen(sbuf.mtext) + 1 ;
        
        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            //perror("msgsnd");
            exit(1);
        }

    
    }else{
//        OSS: total time spent in dispatch was 7000 nanoseconds
        char str[150];
        strcpy(str," \nOSS: total time spent in dispatch was ");
        char temp[15];
        sprintf(temp,"%d", seconds+125000000);
        strcat(str, temp);
        strcat(str,"nanoseconds.");
//        sprintf(temp,"%d", nanoSeconds);
//        strcat(str, temp);
//        strcat(str, " in slave");
        (void) strcpy(sbuf.mtext, str);
        buf_length = strlen(sbuf.mtext) + 1 ;
        
        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            //perror("msgsnd");
            exit(1);
        }
        
        
    }
    
    
    
    
    
    
    /*
     * Send a message.
     */
    
    
//    else
        //printf("Message: \"%s\" Sent\n", sbuf.mtext);
    
    //exit(0);
}

int main(int argc, char *argv[]) {
    //printf("comming in client");
    int shmid;
    key_t key;
    char *shm;
    char *s;
    key = 9878;
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
    int totalDispatchTime = 0;
    int sleepCounter = 0;
//    printf("processNumber = %d \n", processNumber);
        while (1) {
            randomnumber = (rand() % (2 + 1 - 1)) + 1;
            //sendMsg(99, 99, 99);
            if (sharedStates->turn == 1) {
                
                
                int temp = checkQueueMessageReceived();
                if ( temp == -1) {
//                    sleep(1);
                }
//                checkQueueMessageReceived();
                sharedStates->turn = 0;//lock
                int seconds = sharedStates->seconds;
                int nanoSeconds = sharedStates->nanoSeconds;
                ///////
                if (totalDispatchTime == 0) {
                    totalDispatchTime = totalDispatchTime + seconds*1000000000;
                    totalDispatchTime = totalDispatchTime + nanoSeconds;
                }
                ////////////
                sendMsg(seconds, nanoSeconds, temp);
                sharedStates->turn = 1;//Unlock
                if (temp == 3) {
                    sendMsg(seconds, nanoSeconds, temp);
//                    printf("RECEIVEDDD QUEUE 3");
                    int tempTime = sharedStates->seconds * 1000000000;
                    tempTime = tempTime + sharedStates->nanoSeconds;
                    sendMsg(tempTime-totalDispatchTime , tempTime-totalDispatchTime, -100);
                    break;
                }
                
//                break;
            }
//            if (sleepCounter >= 3) {
//                exit(1);
//            }
//            sleep(0.2);
//            sleepCounter =sleepCounter +1;

        }
    
    
    return 0;
}

