#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include "log.h" 

char logfile[100];

typedef struct list_struct
{
     data_t data;
     struct list_struct *next;

} log_t; 

log_t *headptr = NULL;
log_t *tailptr = NULL;

int createnode(log_t** newnode,data_t data)
{
	*newnode = (log_t*)malloc(sizeof(log_t));
	
	if ((*newnode) == NULL)  /*memory allocation failed*/
	{
	  perror("\nMemory allocation failed\n");
      return -1;
	}

   (*newnode)->data.time = data.time;
   (*newnode)->data.string = (char*)malloc(strlen(data.string) + 1);
   strcpy((*newnode)->data.string, data.string);
   (*newnode)->next = NULL;    

   return 0;
}

int addmessage(data_t data) 
{
	log_t* newnode = NULL;

	if(createnode(&newnode,data) == -1)
	{
		return -1;
	}
	if(headptr == NULL)
	{
		headptr = newnode;
	}
	else
	{
		tailptr->next = newnode;
	}
	tailptr = newnode;
	return 0;
}

void freenode(log_t* temp_headptr)
{
    if(temp_headptr == NULL)
        return;
    if(temp_headptr->data.string)
    {
       free(temp_headptr->data.string);
       temp_headptr->data.string = NULL;
    }
    free(temp_headptr);
    temp_headptr = NULL;
}
void clearlog(void) 
{
	FILE* log_fileptr = NULL;
	log_t* temp_headptr = NULL;
	log_t* temp_headptr1 = NULL;
	if(headptr == NULL)
	{
		return ;
	}
	if(headptr == tailptr)
	{
        freenode(headptr);
		tailptr = NULL;
	}
	temp_headptr = headptr;
	while(temp_headptr != NULL)
	{
		temp_headptr1 =	temp_headptr->next;
        freenode(temp_headptr);
		temp_headptr = temp_headptr1;
	}
	headptr = tailptr = NULL;

    log_fileptr = fopen(logfile,"w");
	if(log_fileptr)
	{
		fclose(log_fileptr);
		log_fileptr = NULL;
	}

} 
char *getlog(void) 
{
	long filesize = 0; 
	int length = 0;
	char buff[50];
	char* log_message = NULL;
    int i=0;
    FILE* logfile_ptr =NULL;

	if(strcmp(logfile,"") == 0)
    {
		return NULL;
    }

    logfile_ptr = fopen(logfile,"r");

	if(logfile_ptr == NULL) //
	{
		perror("\n ***********FAILED READING LOGS*********** \n");
		
		return NULL;
	}
	fseek(logfile_ptr, 0, SEEK_END);
	filesize=ftell(logfile_ptr);
	fseek(logfile_ptr, 0, SEEK_SET);
	log_message = (char*) malloc(filesize+1);
    memset(log_message,0,filesize+1);
	while((log_message[i++] = fgetc(logfile_ptr)) != EOF);
	fclose(logfile_ptr);
	logfile_ptr =NULL;

   return log_message;
}

int savelog(char *filename)
{
    FILE* fileOpen  =NULL;
	log_t* temp_nodeptr = NULL;
	strcpy(logfile,filename);

	fileOpen = fopen(logfile,"a");
	if(fileOpen == NULL)
	{
		perror("\n ***********FAILED SAVING LOGS*********** \n");
		return -1;
	}

	temp_nodeptr = headptr;
	do
	{
		fputs(temp_nodeptr->data.string,fileOpen);
		temp_nodeptr = temp_nodeptr->next;
    }while(temp_nodeptr != NULL);
    printf("\n ***********SAVED LOGS*********** \n");

	fclose(fileOpen);

	return 1;
} 
