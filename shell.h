#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include <sys/wait.h>
#include<signal.h>
#include<fcntl.h>
#include <stdlib.h>

#define MAX_LENGTH 1000
#define DELIMS " \t\r\n"

int arglen;
char path[MAX_LENGTH],HOME[MAX_LENGTH];
char rawcmd[MAX_LENGTH];
int ret,pid,n;
int waitforme;
char *arg[100];
int back_count;
int shellpid;

typedef struct node
{
	char name[MAX_LENGTH];
	int status;
	int pid;
}node;
node back[1000];
void child_handler();
void signal_handler();
void execbin();
void execmain();
void echofn();
void pwdfn();
void cdfn();
void inp(char a[MAX_LENGTH]);
void display();
void parse();
void itoa(int n, char s[]);
void reverse(char s[]);
void pinfo();

