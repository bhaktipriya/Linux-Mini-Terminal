#include "shell.h"
int main()
{
	char line[MAX_LENGTH];
	signal(SIGCHLD,child_handler);
	shellpid=getpid();
	strcpy(HOME,getenv("PWD"));
	strcpy(path,"/bin/");
	char commands[100][MAX_LENGTH];
	int i,n;
	while(1)
	{	
		display();
		if(!fgets(line,MAX_LENGTH,stdin)){;}
		else
		{
			parse(line,commands,&n);
			for(i=0;i<n;++i)
			{
				inp(commands[i]);
				/*int j=0;
				while(j<arglen)
					printf("%s",arg[j++]);
				printf("\n");
				//global variables arg, now hold the various arguments*/
				execmain();

			}
		}

	}
	return 0;
}



