#include "shell.h"
void inp(char line[MAX_LENGTH])
{
	//Parsing Function
	arglen=0;
	char *cmd;
	cmd=strtok(line,DELIMS);
	while( cmd != NULL ) 
	{
		arg[arglen++] = cmd;
		cmd = strtok(NULL, DELIMS);
	}

	int i=0;
	arg[arglen] = 0;
	if(strcmp(arg[arglen-1],"&")==0)
	{
		setpgid(0, 0);
		waitforme=1;
		arg[arglen-1]=0;
		arglen--;
	}

}

void parse(char line[MAX_LENGTH],char semicolsep[100][MAX_LENGTH],int *n)
{
	//Parsing function
	strcpy(rawcmd,line);
	char *cmd;
	cmd=strtok(line,";\n");
	int i=0;
	while(cmd != NULL) 
	{
		strcpy(semicolsep[i],cmd);
		i++;
		cmd = strtok(NULL, ";\n");
	}
	*n=i;
}

void display()
{
	//Display prompt
	char hostname[1024],*username,relpath[MAX_LENGTH];
	hostname[1023] = '\0';
	username=getlogin();
	gethostname(hostname, 1023);
	char cpath[1024];
	getcwd(cpath, 1024);
	int i,j;
	int ct=0;
	for (i=0;i<strlen(HOME);++i)
			if(cpath[i]!=HOME[i])
			{
				ct=0;
				break;
			}
			else
				ct++;
	
	
	if(ct==strlen(HOME))
	{
		relpath[0]='~';
		j=1;

		for(i=strlen(HOME);i<strlen(cpath);++i)
		relpath[j++]=cpath[i];

		relpath[j]='\0';
	}

	else
		strcpy(relpath,cpath);

	printf("<%s@%s>:%s ",username,hostname,relpath);

}

