#include "shell.h"

void child_handler()
{
	int p= waitpid(WAIT_ANY,NULL,WNOHANG);
	int i=0,j=0,ct=0;
	char temp[100];
	while(i<back_count)
	{
		if(back[i].pid==p)
		{
			for (j =0;back[i].name[j]!='&'; ++j)
				temp[ct++]=back[i].name[j];

			temp[ct]='\0';
			fflush(stdout);
			printf("\n%s with pid [%d] Exited Normally\n",temp,back[i].pid);
			display();
			fflush(stdout);
			back[i].status=0;
		}




		i++;
	}

	signal(SIGCHLD, child_handler);
	return;

}

void signal_handler(int signum)
{
	int d=0;
	if(signum==20 || signum==3 || signum ==2)
	{
		fflush(stdout);printf("\n");
		display();fflush(stdout);
		signal(SIGINT, signal_handler);
		d++;
		if(d)
			signal(SIGQUIT, signal_handler);
		d++;
		if (d)
			signal(SIGTSTP,signal_handler);
	}
	return;
}
