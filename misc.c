#include "shell.h"
void itoa(int n, char s[])
{
	int i, sign,k;
	i = 0;
	
	do 
	{       
		s[i++] = n % 10 + '0';   
	} 
	//print("%d",k);
	while ((n /= 10) > 0);    
	k++;
	s[i] = '\0';

	reverse(s);
}


void reverse(char s[])
{
	int i, j;
	char c;
	j = strlen(s)-1;
	i=0;
	for (; i<j; i++, j--)
	{
		c = s[i];s[i] = s[j];s[j] = c;
	}
}
