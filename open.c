#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
/*
linux系统函数：open write read lseek close
*/

/*
O_RDONLY、O_WRONLY、O_RDWR  从头开始写 不存在会报错
O_TRUNC：打开清空
O_APPEND：追加，共享时以文件位长度而不是文件位移量的形式增长
O_CREAT：不存在就创建 需指定创建文件的权限
O_EXCL：文件存在就报错 与O_CREAT 配合使用
*/

/*每个进程都有独立的文件描述符池->文件表->文件位移量->V节点(文件大小)
1. 0、1、2默认被使用
   0-> stdin 
   read -> scanf
   1->stdout  
   write -> printf 4096缓冲 行缓冲
   2->stderr
   write -> perror 字节缓冲
2. 重复利用
*/

/*
ernno:系统全局错误编号
perror函数：打印errno编号对应信息(对比错误对照表)
*/

#define print_error(str) \
do{\
				fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
				perror("error Reason");\
				exit(-1);\
}while(0);


int error_printf(int fd)
{
	if(-1 == fd)
	{
		print_error("open");
	}else
	{
		printf("open ok \n");
		printf("fd = %d\n",fd);					
	}
}


int main(void)
{
		int fd1 = 0,fd2 = 0;
		char buf1[]="hello world\n";
		char buf2[30]={0};  //应用缓存
//1-写入测试-------------------------------------------------------------------------------------------------		
		// fd = open("/home/C/open/file.txt",O_RDWR|O_TRUNC);	//申请内核缓存
		// error_printf(fd);	
		// write(fd,buf1,strlen(buf1)+1);		//写入内核缓存 - >写入驱动缓存 -> 块设备文件
		// lseek(fd,0,SEEK_SET);				//将文件指针指向头			
		// read(fd,buf2,sizeof(buf2));			//块设备->驱动缓存 -> 内核缓存 -> 应用缓存
		// printf("buf2 = %s",buf2);
		// close(fd);
		
		
//2-覆盖测试-------------------------------------------------------------------------------------------------		
		// fd1 = open("/home/C/open/file.txt",O_RDWR|O_TRUNC);		//第一次打开
		// error_printf(fd1);
		// fd2 = open("/home/C/open/file.txt",O_RDWR|O_TRUNC);		//第二次打开
		// error_printf(fd2);
					
		// strcpy(buf1,"1111111111\n");		//先写入
		// write(fd1,buf1,strlen(buf1));			

		// strcpy(buf1,"222222222\n");			//后写入
		// write(fd2,buf1,strlen(buf1));			

		// close(fd1);
		// close(fd2);		
		
//3-时时更新文件长度防共享覆盖--------------------------------------------------------------------------------------------------
		// fd1 = open("/home/C/open/file.txt",O_RDWR|O_TRUNC|O_APPEND);		//第一次打开
		// error_printf(fd1);
		// fd2 = open("/home/C/open/file.txt",O_RDWR|O_TRUNC|O_APPEND);		//第二次打开
		// error_printf(fd2);
					
		// strcpy(buf1,"111111111\n");		//先写入
		// write(fd1,buf1,strlen(buf1));			

		// strcpy(buf1,"222222222\n");			//后写入
		// write(fd2,buf1,strlen(buf1));			

		// close(fd1);
		// close(fd2);	

//4-dup--dup2-实现共享-----------------------------------------------------------------------------------------------
		// fd1 = open("/home/C/open/file.txt",O_RDWR|O_TRUNC);		//第一次打开
		// error_printf(fd1);
		// fd2 = dup(fd1);
		// error_printf(fd2);
		// //fd2 = dup2(fd1,4);
		
		// strcpy(buf1,"111111111\n");		//先写入
		// write(fd1,buf1,strlen(buf1));			

		// strcpy(buf1,"222222222\n");			//后写入
		// write(fd2,buf1,strlen(buf1));			

		// close(fd1);
		// close(fd2);	
		
//5-dup--dup2-实现文件重定向-----------------------------------------------------------------------------------------------
		// fd1 = open("/home/C/open/file.txt",O_RDWR|O_TRUNC);		//第一次打开
		// error_printf(fd1);
		// close(1);
		// //fd2 = dup(fd1);
		// error_printf(fd2);
		// fd2 = dup2(fd1,1);  //将1指向fd1指向的文件
		
		// printf("LINZIJUN\n");
		
		// close(fd1);
		// close(fd2);	

//6-fcntl模拟dup-------------------------------------------------------------------------------------------------
		// fd1 = open("/home/C/open/file.txt",O_RDWR|O_TRUNC);		//第一次打开
		// error_printf(fd1);
		// close(1);
		    
       // fd2 = fcntl(fd1,F_DUPFD,0);

		// printf("fd1 = %d  fd2 = %d\n",fd1,fd2);
		
		// close(fd1);
		// close(fd2);	

//7-fcntl补设文件标志位-------------------------------------------------------------------------------------------------


		// fd1 = open("/home/C/open/file.txt",O_TRUNC|O_RDWR);		//第一次打开
		// error_printf(fd1);
		
		// fd2 = open("/home/C/open/file.txt",O_TRUNC|O_RDWR);		//第二次打开
		// error_printf(fd2);
		    
        // int flag = fcntl(fd1, F_GETFL ,0);
		// flag |= O_APPEND;
		
		// fcntl(fd1, F_SETFL ,flag);
		// fcntl(fd2, F_SETFL ,flag);

		// strcpy(buf1,"1111111111\n");		//先写入
		// write(fd1,buf1,strlen(buf1));			

		// strcpy(buf1,"222222222\n");			//后写入
		// write(fd2,buf1,strlen(buf1));			

		// close(fd1);
		// close(fd2);			
		
		return 0;	
}
