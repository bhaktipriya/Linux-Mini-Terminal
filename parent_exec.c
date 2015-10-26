#include "shell.h"
void execmain()
{
	//Main function that segregates commands
	pid_t p;
	signal(SIGCHLD, child_handler);
	if (strcmp(arg[0], "cd") == 0) {
		cdfn();
	}
	else if (strcmp(arg[0], "echo") == 0) {
		echofn();
	}
	else if (strcmp(arg[0], "pwd") == 0) {
		pwdfn();
	}
	else if (strcmp(arg[0], "pinfo") == 0) {
		pinfo();
	}
	else if (strcmp(arg[0], "exit") == 0) {
		exit(0);
	}
	else{

		p=fork();
		if(p==0)
		{
			execbin();
		}

		else if(p>0)
		{
			if(waitforme==0)
			{
				wait(NULL);

			}
			else
			{
				char cmd[MAX_LENGTH];
				int j=0;
				strcpy(cmd,"");
				while(j<arglen)
				{
					strcat(cmd,arg[j]);
					strcat(cmd," ");
					j++;
				}
				strcat(cmd,"&");strcpy(back[back_count].name,cmd);
				back[back_count].pid=p;back[back_count].status=1;
				back_count++;
				waitforme=0;
				printf("%s with [pid] %d created\n",cmd,p);
			}
		}




	}//else for external commands



}

void execbin()
{
	//For all external commands
	if (execvp(arg[0], arg)<0)
	{
		perror("Error");
		_exit(0);
	}

}

void pwdfn()
{
	//pwd function
	char my_cwd[1024];
	getcwd(my_cwd, 1024);
	printf("%s\n", my_cwd);
}
void echofn()
{	int i=1,j;
	int st=0;
	char *cmd;
	char line[MAX_LENGTH];
	strcpy(line,rawcmd);
	cmd=strtok(line,DELIMS);
			
	cmd=strtok(0,"\n");
	if(!cmd)
		{fprintf(stderr,"Invalid Input\n");
			return;
		}
	strcpy(line,cmd);
	
	j=0;
	st=-1;
	char op;
	//checking for pairs
	while(j<strlen(line))
		{
			if(st==-1&&(line[j]=='\"'||line[j]=='\''))
				st=j;
			
			else if(st!=-1&&(line[j]==line[st]))
				st=-1;
			
				j++;


		}
	//if invalid pairs return
		if(st!=-1)
		{
			fprintf(stderr,"Invalid Input\n");
			return;
		}

		st=0;
		j=0;
		int in=0;
	//parsing ""
	while(st<strlen(line))
		{
			if (!in&&(line[st]==' '||line[st]=='\t'||line[st]=='\n'))
			{
				st++;
				continue;
			}
			else if(arg[i][st]=='\"'||arg[i][st]=='\'')
			{
				j=st;
				st++;
				while(st<strlen(line)&&line[j]!=line[st])
				{
					printf("%c",line[st]);
					st++;
				}

				printf(" ");
				st++;

			}
			else
			{
					printf("%c",line[st]);
					st++;
				
			}
		}

	printf("\n");

}
void cdfn()
{
	if(!arg[1]||!strcmp(arg[1],"~"))
	{chdir(HOME);return;}
	if(chdir(arg[1])<0)
		fprintf(stderr,"Invalid Directory\n");
		
}

void pinfo()
{


	FILE *fp1,*fp2;

	char filename[MAX_LENGTH],buffer[21];
	char statusnm[MAX_LENGTH];
	char mapnm[MAX_LENGTH];
	char l[MAX_LENGTH];

	strcpy(filename,"/proc/");
	if(arg[1])
		strcat(filename,arg[1]);
	else{
		itoa(shellpid,buffer);
		strcat(filename,buffer);
	}
	strcpy(statusnm,filename);
	strcpy(mapnm,filename);
	strcat(statusnm,"/status");
	strcat(mapnm,"/smaps");

	fp1 = fopen (statusnm, "r");
	fp2 = fopen (mapnm, "r");

	if(!fp1)
	{
			fprintf(stderr,"Invalid Process\n");
			return;
	}

	while ( fgets ( l, sizeof l, fp1 ) != NULL ) 
	{
		char* field=strtok(l,":");
		if(strcmp(field,"Name")==0)
		{
			field=strtok(NULL,":");
			printf("Name:%s",field);

		}
		if(strcmp(field,"State")==0)
		{
			field=strtok(NULL,":");
			printf("State:%s",field);

		}
		if(strcmp(field,"Pid")==0)
		{
			field=strtok(NULL,":");
			printf("Pid:%s",field);

		}
		if(strcmp(field,"VmSize")==0)
		{
			field=strtok(NULL,":");
			printf("Virtual Memory:%s",field);

		}

	}
	if(!fp2)
	{
			//fprintf(stderr,"Invalid Process\n");
			return;
	}


	while ( fgets ( l, sizeof l, fp2 ) != NULL ) 
	{
		char* field=strtok(l,"/");
		char *d=strtok(NULL,"\n");
		printf("Executable Path:/%s",d);
		break;

	}
	printf("\n");


	fclose(fp1);
	fclose(fp2);



}


