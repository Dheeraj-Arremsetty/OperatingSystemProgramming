#include <stdlib.h>
#include <string.h>
#include "log.h"
#include <err.h>
#include <errno.h>
#include <stdio.h>

typedef struct list_struct {
    data_t item;
    struct list_struct *next;
} log_t;
static log_t *headptr = NULL;
static log_t *tailptr = NULL;

char* geterrMsg(char* msg, int time, char* ret) {
    sprintf(ret, "./debugger: %d: %s ", time,msg);

    return ret;
}

int addmsg(data_t data) {
    log_t *newnode;
    int nodesize;
    nodesize = sizeof(log_t) + strlen(data.string) + 1;
    if ((newnode = (log_t *)(malloc(nodesize))) == NULL) {
        return -1;
    }
    newnode->item.time = data.time;
    newnode->item.string = (char *)newnode + sizeof(log_t);
    strcpy(newnode->item.string, data.string);
    newnode->next = NULL;
    if (headptr == NULL) {
        headptr = newnode;
    }else{
        tailptr->next = newnode;
    }
    tailptr = newnode;
    
    
    return 0;
}

void clearlog(void) {
    log_t *next = headptr;
    while (next != NULL) {
        next = headptr->next;
        free(headptr);
        headptr = next;
    }
}
char *getlog(void) {
    size_t len = 0;
    size_t msglen;
    size_t offset;
    log_t *node = headptr;
    char *log;
    while (node != NULL) {
        len += strlen(node->item.string);
        len++;
        node = node->next;
    }
    
    log = (char*)malloc(len);
    if (log == NULL) {
        warn("malloc failed while allocating memory for getlog");
        return NULL;
    }
    
    node = headptr;
    offset = 0;
    while(node) {
        msglen = strlen(node->item.string);
        memcpy(log + offset, node->item.string, msglen);
        offset += msglen;
        memcpy(log + offset, "\n", 1);
        offset++;
        node = node->next;
    }
    memcpy(log + offset - 1, "\0", 1);
    return log;

}
int savelog(char *filename) {
    FILE *f;
    int error;
    log_t *node;
    if (filename == NULL) {
        errno = EINVAL;
        return -1;
    }
    
    f = fopen(filename, "a");
    if (f == NULL) {
        error = errno;
        warn("Failed to open %s", filename);
        errno = error;
        return -1;
    }
    
    node = headptr;
    while (node) {
        char* msg = node->item.string;
        char ret[100];
        int time = node->item.time;
//        fprintf(f, "%s\n", geterrMsg(msg, time, ret));
        fprintf(f, "%s\n", msg);
        node = node->next;
    }
    if (fclose(f)) {
        error = errno;
        warn("fclose failed in savelog");
        errno = error;
        return -1;
    }
    return 0;
}
