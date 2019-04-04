#include <stdio.h>
#include <string.h>

extern char ** environ;
int main(int argc,char **argv)
{
	int i=0;
	if(argc>1)
	{
		while(argv[i]!=NULL)
		{
			printf("%s\n",argv[i]);
			i++;
			if(strcmp(argv[1],"linzijun")==0)
			{
				while(1);
			}
		}
		
		i=0;
		while(environ[i]!=NULL)
		{
			printf("%s\n",environ[i]);
			i++;
		}
	}
	
	
	return 10;
	
}