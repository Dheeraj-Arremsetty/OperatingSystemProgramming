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
} data;
int processNumber = 0;
char fileName[];
FILE *file;
int main(int argc, char *argv[]) {
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
    for (x=0; x < numberOfTimesNeedToWriteToFile; x++) {
        while (1) {
            randomnumber = (rand() % (2 + 1 - 1)) + 1;
            if (sharedStates->turn == 1) {

                sharedStates->turn = 0;//lock
                //Accesing shared memory
                file = fopen(fileName, "a");
                sharedStates->sharedInt = sharedStates->sharedInt + 1;
                fprintf(file,"    File modified by process number %d at time %lu with shared number = %d\n", processNumber + 1, times, sharedStates->sharedInt);

                if(fclose(file)) {
                    perror("    Error closing file");
                }
                sharedStates->turn = 1;//Unlock
                break;
            }
            
        }
        
        
    }

    
    return 0;
}

