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
//    printf("inside client");
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
//    printf("Inside client for process number = %d", processNumber);
//    printf("\nNumber of increments = %d",numberOfTimesNeedToWriteToFile);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
//    shm = shmat(shmid, NULL, 0);
//    
//    if (shm == (char *) -1) {
//        perror("shmat");
//        exit(1);
//    }
    if((sharedStates = (data *)shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("some memory problem...");
        exit(1);
    }
    
//    int res = (data) *shm;
//    for (s = shm; *s != 0; s++) {
//        printf("%c",*s);
//        //        cout <<*s<<"\n";
//    }
//    printf("\n ********result %d", sharedStates->sharedInt);
//    printf("\n ******** = %s",shm);
    
//    *shm = "*";
    
//    printf("File Name in Client = %s",fileName);
//    file = fopen(fileName, "a");
//    if(!file) {
//        perror("    Error opening file");
//        exit(-1);
//    }
    
    time_t times = time(NULL);
    
    for (int x=0; x < numberOfTimesNeedToWriteToFile; x++) {
        
        while (1) {
            randomnumber = (rand() % (2 + 1 - 1)) + 1;
            if (sharedStates->turn == 1) {
//            if(semop(shmid, &sharedStates, 1)== 0) {
//                semop(shmid, &sharedStates, 1);
                sharedStates->turn = 0;//lock
//                shmctl(shmid, SHM_LOCK, (struct shmid_ds *) NULL);
                file = fopen(fileName, "a");
                sharedStates->sharedInt = sharedStates->sharedInt + 1;
                fprintf(file,"    File modified by process number %d at time %lu with shared number = %d\n", processNumber + 1, times, sharedStates->sharedInt);

                if(fclose(file)) {
                    perror("    Error closing file");
                }
//                shmctl(shmid, SHM_UNLOCK, (struct shmid_ds *) NULL);
                
                sharedStates->turn = 1;//Unlock
//                if(semop(shmid, &sharedStates, 1)== 0)
//                    printf("UnLocking: Resource…\n");
                


                break;
            }
            
        }
        
        
//        sharedStates->turn = 0;//lock
//        fprintf(file,"    File modified by process number %d at time %lu with shared number %d\n", processNumber + 1, times, sharedStates->sharedInt);
//        sharedStates->sharedInt = sharedStates->sharedInt + 1;
//        sharedStates->turn = 1;
    }

    
//    if(fclose(file)) {
//        perror("    Error closing file");
//    }
    
//    printf("\n completed in client");
    return 0;
}
/* 
 
 int shmid;
 key_t key;
 char *shm;
 char *s;
 key = 9876;
 
 shmid = shmget(key, SHSIZE,0666);
 
 if (shmid == -1) {
 perror("shmget");
 exit(1);
 }
 
 shm = shmat(shmid, NULL, 0);
 
 if (shm == (char *) -1) {
 perror("shmat");
 exit(1);
 }
 
 for (s = shm; *s != 0; s++) {
 printf("%c",*s);
 //        cout <<*s<<"\n";
 }
 
 *shm = "*";
 
 return 0;
 */
