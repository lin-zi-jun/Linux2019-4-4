#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>



void signal_test(int signo)
{
	
	switch(signo)
	{
		case SIGINT:
			printf("signal number = %d\n",signo);
		break;
		
		case SIGQUIT:
			printf("signal number = %d\n",signo);
		break;
		
		case SIGALRM:
			printf("signal number = %d\n",signo);
			int ret = alarm(5);
			printf("ret = %d\n",ret);
		break;
	}
	
}

void signal_test1(int ret)
{
	printf("hello\n");
	sleep(3);
	printf("world\n");
}



void signal_test2(int ret)
{
	sigset_t set;
	printf("hello\n");
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_UNBLOCK,&set,NULL);		//信号屏蔽字不置位
	sleep(3);
	printf("world\n");
}

typedef void (*sighandler_t)(int);

int main(void)
{
//1-忽略信号测试-------------------------------------------------------------------------------------
	// signal(SIGINT,SIG_IGN);
	// while(1);
	
//2-还原位系统信号-------------------------------------------------------------------------------------
	// signal(SIGINT,SIG_DFL);
	// while(1);
	
//3-信号捕获测试-------------------------------------------------------------------------------------
	// signal(SIGINT,signal_test);
	// signal(SIGQUIT,signal_test);
	// while(1);
	
//4-返回值测试-------------------------------------------------------------------------------------
	
	// sighandler_t ret = NULL;
	// ret = signal(SIGINT,SIG_IGN);
	// ret = signal(SIGINT,SIG_DFL);
	// ret = signal(SIGINT,signal_test);
	// ret = signal(SIGINT,SIG_DFL);
	
	// if(ret == SIG_DFL)
	// {
		// printf("default\n");
	// }
	// else if(ret == SIG_IGN)
	// {
		// printf("ignoe\n");
	// }
	// else if(ret == SIG_ERR)
	// {
		// printf("signal fail\n");
	// }
	// else
	// {
		// printf("fun = %p\n",ret);
	// }
	// while(1);
	
//5-SIGKILL信号测试-------------------------------------------------------------------------------------

	// int i=0;
	// for(i=0;i<64;i++)
	// {
		// signal(i,SIG_IGN);
	// }

	// while(1);
	
//6-kill-raise函数测试-------------------------------------------------------------------------------------

	// // kill(getpid(),SIGUSR1);
	// // kill(2426,SIGKILL);
	// // raise(SIGKILL);		//给自己发送信号
	// // while(1);

// //7-alarm函数测试-------------------------------------------------------------------------------------

	// signal(SIGALRM,signal_test);
	// alarm(5);
	// while(1);
//8-休眠函数测试1-------------------------------------------------------------------------------------

	// signal(SIGINT,signal_test);
	// int ret = 0;
// lable:	ret = pause();					//手动休眠
		// if(ret ==-1 &&errno==EINTR)
		// {
			// goto lable;
		// }
	// while(1);
	
//8-休眠函数测试2-------------------------------------------------------------------------------------

	// signal(SIGINT,signal_test);
	// int ret = 10;
// lable:	ret = sleep(ret);					//手动休眠
		// if(ret != 0)
		// {
			// printf("ret = %d\n",ret);
			// goto lable;
		// }
		
		// while(1);
		
//8-休眠函数测试3-------------------------------------------------------------------------------------

	// signal(SIGINT,signal_test);

	// char buf[20] = {0};
	// read(0,buf,sizeof(buf));		//从键盘读数据  -> scanf 读不到会进入休眠 自动休眠
	// printf("%s\n",buf);

	// while(1);
	
	
	
//9-自杀函数测试-------------------------------------------------------------------------------------
	// abort();
	// while(1);
	
//10-未处理信号集测试-------------------------------------------------------------------------------------
	
	// signal(SIGINT,signal_test1);  //信号处理方式 -> 信号屏蔽字 -> 未处理信号集
	// while(1);
	
//11-未处理信号集测试-------------------------------------------------------------------------------------
	
	signal(SIGINT,signal_test2);  //信号处理方式 -> 信号屏蔽字 -> 未处理信号集
	while(1);	
	
	
}
		

		
		
		
		
		
		
		
		
		
		
		

