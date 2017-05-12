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
    /*
     
     ./debugger: 1485211525309381617: Error: nValue = 37 - No dogs detected
     */
    
    printf("top of function\n");
    
//    struct tm *gm;
//    char time[15]="";
    
//    gm = localtime(&data->time);
//    sprintf(time," %d:%d:%d : ",gm->tm_hour,gm->tm_min,gm->tm_sec);
//    data->string = (char*)malloc(len+9+strlen(time)+strlen(errormsg));
//    strcpy(data->string,buggy_code);
//    strcat(data->string,":Error :");
//    strcat(data->string,time);
//    strcat(data->string,errormsg);
    
    
    
    data->string = (char*)malloc(100+strlen(errormsg));
    strcat(data->string, buggy_code);
    char ret[15];
    sprintf(ret, "%d ",time(NULL));
    int t = time(NULL);
    strcat(data -> string,": ");
    printf("***************************ret =%d",time(NULL));
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
//    sprintf(str,"%ld",time(NULL));
//    strcat(node.string,str);
//    node->time = time();
    addmessage(node);
}

int main(int argc,char* argv[])
{
  data_t a,a1;
  char* logmsg = NULL;
  int opt = 0;
//    int n = 37;
    char fileName[100] = "logFile.txt";
  while((opt = getopt(argc,argv,"h:n:l:i:o:"))!=-1)
  {
	  switch(opt)
	  {
      case 'h':
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
//    if (strlen(fileName) <1) {
//        strcpy(fileName,"logFile.txt");
//    }
    printf("argv[0] = %s \n", argv[0]);
    printf("filename = %s",fileName);
    printf("n = %d",n);
    
//    logMessage("Yoo THis is test msg!!!!!!");
//    savelog("log.txt");

  len = strlen(argv[0]);
  memset(buggy_code,0,30);
  strcpy(buggy_code,argv[0]);
 

    
  a1.time = time(NULL);
    printf("calling log messsssssgggggggggg \n");
  formateerrormessage(&a1,"Number is not an even number\n");
    addmessage(a1);
formateerrormessage(&a1,"Number is not an even number\n");
    addmessage(a1);
    formateerrormessage(&a1,"Division by zero\n");
    addmessage(a1);
    formateerrormessage(&a1,"Division by zero\n");
    addmessage(a1);
//    formateerrormessage(&a1,"Number is not an even number\n");
//    formateerrormessage(&a1,"Number is not an even number\n");
    
  savelog(fileName);

 logmsg =  getlog();
 printf("%s",logmsg);

 
// clearlog();
// getch();
 
 return 0;        
}              

