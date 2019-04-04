#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
//1-查看进程-其父进程--------------------------------------------------------------------------------	
	// pid_t pid=0;
	// pid = getpid();
	
	// pid_t ppid=0;
	// ppid = getppid();
	
	// uid_t uid=0;
	// uid = getuid();
	
	// gid_t gid=0;
	// gid = getgid();
	
	// printf("pid = %d , ppid = %d , uid = %d , gid = %d\n",pid,ppid,uid,gid);
	
	// while(1);pid_t pid=0;
	
//2-从父进程复制子进程--------------------------------------------------------------------------------

	// pid_t pid = 0;
	// // pid = getpid();  ??
	
	// printf("start-----\n");
	// printf("end--------");		//解释库缓存
	
	// pid_t ret = 0;
	// ret = fork();		//子进程开始执行的地方
	// if(ret>0)
	// {
		// printf("parent pid = %d\n",getpid());
		// printf("parent ret = %d\n",ret);
	// }else if(ret == 0)
	// {
		// printf("child pid = %d\n",getpid());
		// printf("child ret = %d\n",ret);
	// }
	
	// printf("hello world\n");
	
	// while(1);
	
//3-从父子进程共享文件覆盖测试--------------------------------------------------------------------------------

	// pid_t pid = 0;

	// pid_t ret = 0;
	// ret = fork();		//子进程开始执行的地方
	// if(ret>0)
	// {
		// int fd =0;
		
		// fd = open("file.txt",O_RDWR|O_CREAT);		//当前进程 -> fd -> 文件表  -> 文件位移量 ->V节点  ->文件Inode 
		// if(fd==-1) exit(-1);
		// write(fd,"hello",strlen("hello"));
	// }else if(ret == 0)
	// {
		// int fd = 0;
		// fd = open("file.txt",O_RDWR|O_CREAT);		//当前进程 -> fd -> 文件表  -> 文件位移量 ->V节点  ->文件Inode 
		// if(fd==-1) exit(-1);
		// write(fd,"world",strlen("world"));
	// }


//4-从父子进程共享文件测试--------------------------------------------------------------------------------

	// pid_t pid = 0;

	// pid_t ret = 0;
	// ret = fork();		//子进程开始执行的地方
	// if(ret>0)
	// {
		// int fd =0;
		
		// fd = open("file.txt",O_RDWR|O_CREAT|O_APPEND);		//当前进程 -> fd -> 文件表  ->V节点  ->文件Inode ->文件长度 
		// if(fd==-1) exit(-1);
		// write(fd,"hello",strlen("hello"));
	// }else if(ret == 0)
	// {
		// int fd = 0;
		// fd = open("file.txt",O_RDWR|O_CREAT|O_APPEND);		//当前进程 -> fd -> 文件表   ->V节点   ->文件Inode ->文件长度 
		// if(fd==-1) exit(-1);
		// write(fd,"world",strlen("world"));
	// }
	
//5-从父进程打开文件子进程共享测试--------------------------------------------------------------------------------	

	// pid_t ret = 0;
	
	// int fd =0;
	// fd = open("file.txt",O_RDWR|O_CREAT);		//当前进程 -> fd -> 文件表  ->V节点  ->文件Inode ->文件长度 
	// if(fd==-1) exit(-1);
	
	// ret = fork();		//子进程开始执行的地方
	// if(ret>0)
	// {
		// write(fd,"hello\n",strlen("hello\n"));
	// }else if(ret == 0)
	// {
		// write(fd,"world\n",strlen("world\n"));
	// }
	
//6-加载器测试--------------------------------------------------------------------------------

	// pid_t ret = 0;
	// ret = fork();		//子进程开始执行的地方
	// if(ret>0)
	// {
		// // sleep(5);
	// }else if(ret == 0)
	// {
		// extern char ** environ;
		// execve("exev.out",argv,environ);
	// }
	
//7-库函数加载进程--------------------------------------------------------------------------------	
	
	// system("/home/C/open/exev.out 111 222 333 444 555 666");
	
//8-僵尸进程演示--------------------------------------------------------------------------------	
	// pid_t ret = 0;
	// ret = fork();		//子进程开始执行的地方
	// if(ret>0)
	// {
		// while(1);
	// }else if(ret == 0)
	// {
	// }
	// return 0;
	
//9-孤儿进程演示--------------------------------------------------------------------------------
	// pid_t ret = 0;
	// ret = fork();		//子进程开始执行的地方
	// if(ret>0)
	// {
		
	// }else if(ret == 0)
	// {
		// while(1);
	// }
	// return 0;
	
//10-父进程等待子进程结束，并获取子进程终止状态--------------------------------------------------------------------------------

	pid_t ret = 0;
	ret = fork();		//子进程开始执行的地方
	if(ret>0)
	{
		int status=0;
		wait(&status);
		
		if(WIFEXITED(status))
		{
			printf("status = %d\n",WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status))
		{
			printf("status = %d\n", WTERMSIG(status));
		}
		
	}else if(ret == 0)
	{
		extern char ** environ;
		execve("exev.out",argv,environ);
	}
	
	return 0;
	
}


      



























