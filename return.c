#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void process_deal(void)
{
	printf("process_deal\n");
}

extern char **environ;


int main(int agvc, char **agve)
{
	
//echo $?查看返回值	
//1-正常终止测试---------------------------------------------------------------------------------
//	exit(-1);			//exit -> _exit
//	return 0;			//return -> exit -> _exit

//2-自杀测试-------------------------------------------------------------------------------------	
	// abort();

//3-扫尾函数测试(进程终止处理函数)-------------------------------------------------------------------------------------	
	// atexit(process_deal);		//压栈的方式注册
	// exit(0);
	
//4-行缓冲测试-------------------------------------------------------------------------------------	

	// printf("hello world");
	// // fflush(stdout);		//主动刷新库缓冲
	// // fclose(stdout);		//关闭文件描述符(文件标准io) -> fflush
	// // exit(-1);			//exit -> fclose ->fflush ->_exit 
	 // _exit(-1);			//标准函数不会刷新
	// while(1);
	
//5-打印所有全局变量-------------------------------------------------------------------------------------
	int i=0;
	
	putenv("AA=linzijun");
	putenv("AA=HelloWorld");
	
	setenv("BB","AAAAAAAAAAAAAAAAAA",!0);
	setenv("BB","CCCCCCCCCCCCCCCCCC",0);
	
	unsetenv("BB");
	
	char *p=NULL;
	
	p = getenv("AA");
	if(p!=NULL) printf("AA=%s\n\n",p);
	
	while(environ[i]!=NULL)
	{
		printf("%s\n",environ[i]);
		i++;
	}
	
	return 0;
}














