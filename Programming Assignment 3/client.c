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
int processNumber = 0;
char fileName[];
FILE *file;

#define MSGSZ     128

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

sendMsg(int seconds, int nanoSeconds){
    
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
        //exit(1);
    }
//    else
//        (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
    
    
    /*
     * We'll send message type 1
     */
    
    sbuf.mtype = 1;
    
    //(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
    
    ///////////
    char str[150];
    strcpy(str," because it reached ");
    char temp[15];
    sprintf(temp,"%d", seconds);
    strcat(str, temp);
    strcat(str,".");
    sprintf(temp,"%d", nanoSeconds);
    strcat(str, temp);
    strcat(str, " in slave");
//    printf("%s\n ",str);
    
    
    ///////////////
    (void) strcpy(sbuf.mtext, str);
    
    //(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
    
    buf_length = strlen(sbuf.mtext) + 1 ;
    
    
    
    /*
     * Send a message.
     */
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
        //printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
        //perror("msgsnd");
        exit(1);
    }
    
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
            if (sharedStates->turn == 1) {
                
                sharedStates->turn = 0;//lock
                //Accesing shared memory
//                file = fopen(fileName, "a");
//                sharedStates->sharedInt = sharedStates->sharedInt + 1;
                //fprintf(file,"    File modified by process number %d at time %lu with shared number = %d\n", processNumber + 1, times, sharedStates->sharedInt);
                
//                if(fclose(file)) {
//                    perror("    Error closing file");
//                }
                int seconds = sharedStates->seconds;
                int nanoSeconds = sharedStates->nanoSeconds;
                sendMsg(seconds, nanoSeconds);
                sharedStates->turn = 1;//Unlock
                break;
            }
            
        
        
        
    }
    
    
    return 0;
}

