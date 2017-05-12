#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"log.c"

int len;
char buggy_code[30];
int n = 37;
void formateerrormessage(data_t* data,char* errormsg)
{
    
    
    //printf("top of function\n");    
    
    data->string = (char*)malloc(100+strlen(errormsg));
    strcat(data->string, buggy_code);
    char ret[15];
    sprintf(ret, "%d ",time(NULL));
    int t = time(NULL);
    strcat(data -> string,": ");
    strcat(data->string,ret);
    strcat(data->string,": Error: nValue = ");
    char ret2[10];
    sprintf(ret2, "%d ",n);
    strcat(data->string,ret2);
    strcat(data->string," - ");
    strcat(data->string, errormsg);
    
    
}

void logMessage1(char* msg){
    data_t node;
    strcat(node.string, msg);
    char str[30];
    sprintf(str,"%ld",time(NULL));
    strcat(node.string,str);
    node.time = time(NULL);
    addmessage(node);
}

int main(int argc,char* argv[])
{
  data_t a,a1;
  char* logmsg = NULL;
  int opt = 0;
    int helpFlag = 0;
    char fileName[100] = "logFile.txt";
  while((opt = getopt(argc,argv,"h:n:l:i:o:"))!=-1)
  {
	  switch(opt)
	  {
      case 'h':
              helpFlag = 1;
	
              break;
      case 'n':
              if (optarg != NULL) {
                  n = atoi(optarg);
              }
              break;
      case 'l':
              if (optarg != NULL) {
                  strcpy(fileName, optarg);
              }
              break;
	  }
  }
    
    if (helpFlag == 1) {
        printf("***HELP***\nType -h for HELP?\n \Type -n to Enter a numeric value\nType -l to Change the log filename");
    }
    printf("argv[0] = %s \n", argv[0]);
    printf("filename = %s",fileName);
    printf("n = %d",n);
    
    len = strlen(argv[0]);
    memset(buggy_code,0,30);
    strcpy(buggy_code,argv[0]);
 

    
    a1.time = time(NULL);
    //printf("calling log messsssssgggggggggg \n");
    formateerrormessage(&a1,"Number is not an even number\n");
    addmessage(a1);
    formateerrormessage(&a1,"Number is not an even number\n");
    addmessage(a1);
    formateerrormessage(&a1,"Division by zero\n");
    addmessage(a1);
    formateerrormessage(&a1,"Division by zero\n");
    addmessage(a1);
    
    formateerrormessage(&a1,"P == NP\n");
    addmessage(a1);
    formateerrormessage(&a1,"P == NP\n");
    addmessage(a1);
    
    formateerrormessage(&a1,"No dogs detected\n");
    addmessage(a1);
    formateerrormessage(&a1,"No dogs detected\n");
    addmessage(a1);
    
  savelog(fileName);

 logmsg =  getlog();
 printf("%s",logmsg);

 return 0;        
}              

