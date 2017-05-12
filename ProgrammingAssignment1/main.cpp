#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <cstdio>
#include <string>

#include "loglib.c"
extern int errno;
char file[100]; //= "logfile.txt";
int number=37;
int buggyCodeFlag = 0;
char buggyCode[100] = "./";

void help() {
    printf("Usage: ./main [-hln] [args]\n");
    printf("\t -h --help: to get help\n");
    printf("\t -n: --specify  variable value. Takes an argument. defaults value 37.\n");
    printf("\t -l: to specify the log file name. defaut value is logfile.txt\n");
    printf("\t args: takes the message to be posted in log\n");
}

char* geterrMsg1(char* msg, int time, char* ret) {
    if (buggyCodeFlag == 0) {
        sprintf(ret, "./debugger: %d: %s ", time,msg);
    }else{
        sprintf(ret, "%s: %d: %s ",buggyCode, time,msg);
    }
    
    return ret;
}

void logMessageWithErrorNumber(int errNumber){
    data_t current;
    current.string = strerror(errNumber);
    current.time = time(NULL);
    char tmp[1000];// = malloc(strlen(command) + 10);
    int errnum = 0;
    
        strcpy(tmp,"");

        strcat(tmp, ": Error: ");
        strcat(tmp, ":nValue = ");
        char str[15];
        sprintf(str, "%d", number);
        strcat(tmp, str);
        strcat(tmp, " - ");
        strcat(tmp, strerror(errNumber));

    char ret[100];
        current.string = geterrMsg1(tmp, current.time, ret);
    
        addmsg(current);

    

}
void logMessage(char* command){
    data_t current;
    current.string = command;
    current.time = time(NULL);
    char tmp[1000];// = malloc(strlen(command) + 10);
    int errnum = 0;
    if (system(command) != 0) {
        errnum = system(command);
        strcpy(tmp,"");
        strcat(tmp, ": Error: ");
        strcat(tmp, ":nValue = ");
        char str[15];
        sprintf(str, "%d", number);
        strcat(tmp, str);
        strcat(tmp, " - ");
        
        if (buggyCodeFlag == 1) {
            strcat(tmp, strerror(errnum));
        }else{
            strcat(tmp, command);
        }

        char ret[100];
        
        current.string = geterrMsg1(tmp, current.time, ret);

    }
    else{
        strcpy(tmp,"");

        strcat(tmp, ": Error: ");
        strcat(tmp, ":nValue = ");
        char str[15];
        sprintf(str, "%d", number);
        strcat(tmp, str);
        strcat(tmp, " - ");

        if (buggyCodeFlag == 1) {
            strcat(tmp, strerror(errnum));
        }else{
            strcat(tmp, command);
        }

        
        
 
        char ret[100];
        
        current.string = geterrMsg1(tmp, current.time, ret);
    }
    addmsg(current);
}

int main(int argc,char *argv[]){
	
    int cmdOptions;
    int a =0;
    int p = 0;
    int l = 0;
    int helpFlag = 0;
    
    while ((cmdOptions = getopt(argc,argv,"h:n:l:b:")) != -1) {
        
        switch (cmdOptions) {
            case 'h' :
                printf("comming in a");
                helpFlag = 1;
                if(optarg == NULL){
                    help();
                }else{
                    help();
                }

                
                break;
            case 'n' :
                if(optarg != NULL){
                    number = atoi(optarg);
                }
                p = 1;
//                printf("comming in p");
                break;
            case 'l' :
                if(optarg != NULL){

                    strcpy(file, optarg);

                }

                break;
            case 'b':
                if (optarg != NULL) {
                    
                    strcat(buggyCode, optarg);
                    buggyCodeFlag = 1;
                }else{
                    
                }
//            default:
//                printf("In default");
//                print_usage();
//                exit(EXIT_FAILURE);
//                help();
                
        }
        
    }
    if (helpFlag == 1) {
        help();
    }

//    printf("n=%d, l=%s, l=%d \n\n",number,file,l);

    if (strlen(file)<1) {
        strcpy(file, "logfile.txt");
    }
    
    if (strlen(buggyCode) > 2) {
        printf("*************Running buggy code*************** \n");
        logMessage(buggyCode);
        logMessage(buggyCode);
        buggyCodeFlag = 0;
    }
    
    
    logMessageWithErrorNumber(2);
    logMessageWithErrorNumber(2);
    logMessageWithErrorNumber(2);
    logMessage("No dogs detected");
    logMessage("No dogs detected");
    logMessage("ls");
    logMessage("cat abc");
    logMessage("P == NP");
    savelog(file);
    printf("*************Clearing Memory*************** \n ");
    clearlog();
   
    return 0;
}
