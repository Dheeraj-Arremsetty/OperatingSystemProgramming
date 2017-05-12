#ifndef LOG_CODE_LOG_H
#define LOG_CODE_LOG_H
#include <time.h> 

typedef struct data_struct 
{
	time_t time;

     char *string;

} data_t;

int addmessage(data_t data);

void clearlog(void);

char *getlog(void);

int savelog(char *filename);

#endif //LOG_CODE_LOG_H