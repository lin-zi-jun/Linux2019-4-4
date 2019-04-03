#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// struct stat {
				// dev_t     st_dev;         /* ID of device containing file */
				// ino_t     st_ino;         /* inode number */
				// mode_t    st_mode;        /* protection */
				// nlink_t   st_nlink;       /* number of hard links */
				// uid_t     st_uid;         /* user ID of owner */
				// gid_t     st_gid;         /* group ID of owner */
				// dev_t     st_rdev;        /* device ID (if special file) */
				// off_t     st_size;        /* total size, in bytes */
				// blksize_t st_blksize;     /* blocksize for filesystem I/O */
				// blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

				// struct timespec st_atim;  /* time of last access */
				// struct timespec st_mtim;  /* time of last modification */
				// struct timespec st_ctim;  /* time of last status change */

				// #define st_atime st_atim.tv_sec      /* Backward compatibility */
				// #define st_mtime st_mtim.tv_sec
				// #define st_ctime st_ctim.tv_sec
				// };
				
//	st_mode		st_nlin		st_uid		st_gid		st_size		st_atime		file.txt	
// 	-rw-r--r-- 	1 			root 		root   		21 			Apr  1 19:54 	file.txt
// 	33188 		1 			0 			0 			21 			1554119684 		file.txt
/*				
S_ISREG(m)  is it a regular file?
S_ISDIR(m)  directory?
S_ISCHR(m)  character device?
S_ISBLK(m)  block device?
S_ISFIFO(m) FIFO (named pipe)?
S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
*/

	 // struct dirent {
				   // ino_t          d_ino;       /* inode number inode 节点编号*/
				   // off_t          d_off;       /* not an offset; see NOTES */
				   // unsigned short d_reclen;    /* length of this record */
				   // unsigned char  d_type;      /* type of file; not supported
												  // by all filesystem types */
				   // char           d_name[256]; /* filename	文件名 */
			   // };


//chmod u=rwx,g=rw-,o=r-- file.txt
//chown 新的所属用户:新的组 文件
				
#define print_error(str) \
do{\
	fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
	perror("error Reason");\
	exit(-1);\
}while(0);


struct stat sta={0};
char file_type = '0';
int fd=-1;


int fun_R(char *p)
{
	int ret = lstat(p, &sta);
	if(-1 == ret) print_error("main");
	
//显示文件类型
		 if(S_ISREG(sta.st_mode)) 	file_type = '-'; 
	else if(S_ISDIR(sta.st_mode)) 	file_type = 'd'; 
	else if(S_ISCHR(sta.st_mode)) 	file_type = 'c'; 
	else if(S_ISBLK(sta.st_mode)) 	file_type = 'b'; 
	else if(S_ISFIFO(sta.st_mode)) 	file_type = 'p'; 
	else if(S_ISLNK(sta.st_mode)) 	file_type = 'l'; 
	else if(S_ISSOCK(sta.st_mode)) 	file_type = 's'; 
	printf("%c",file_type);
//显示文件权限
	char c_buf[]="rwxrwxrwx-";
	char temp_buf[10] = {0};
	int i=0;
	for(i=0;i<9;i++)
	{
		if(sta.st_mode&(1<<(8-i)))  temp_buf[i]=c_buf[i];
		else temp_buf[i]=c_buf[9];
	}

	printf("%s ",temp_buf);

	struct passwd * pw=NULL;
    pw = getpwuid(sta.st_uid);
	  if(pw==NULL) print_error("getpwuid");
	  
	struct group * gp = NULL;
	gp = getgrnam("root");
	if(gp==NULL) print_error("getgrnam");
	
	

	struct tm * pt = NULL;
	pt = localtime(&sta.st_atime);
	char buf[100]={0};
	strftime(buf,sizeof(buf),"%Y/%m/%d %H:%M:%S",pt);

	printf("%lu %s %s %10ld %s ",
			sta.st_nlink,pw->pw_name,gp->gr_name,sta.st_size,buf);
		
		if(file_type=='l')
		{
			char buf[30]={0};
			readlink(p, buf,sizeof(buf));			//符号跟随
			printf("%s->%s\n",p,buf);
		}else
		{
			printf("%s\n",p);
		}
	
	return 0;
}

int fun_DIR(char *p)
{
	DIR *dirp=NULL;
	
	char buf_old[30]={0};
	char buf_new[30]={0};
	getcwd(buf_old,sizeof(buf_old));
	chdir(p);
	getcwd(buf_new,sizeof(buf_new));
	dirp = opendir(buf_new);
	struct dirent * DIRP=NULL;
	
	while(1)
	{
		DIRP = readdir(dirp);
		if(DIRP==NULL&&errno!=0)
		{
			perror("readdir fail");
			exit(-1);
		}
		
		if(DIRP==NULL&&errno==0) break;
		fun_R(DIRP->d_name);
	}
	chdir(buf_old);
	return 0;
}

int main(int argc,char **argv)
{
	int mode_t=0;
	
// //1-获取文件属性测试-------------------------------------------------------------------------------------------------		
	if(argc<2) print_error("argv");	
	//int ret = stat(argv[1], &sta);
	//fd = open("/home/C/open/file.txt",O_RDWR|O_TRUNC);	//申请内核缓存
	//int ret = fstat(fd, &sta);
	int ret = lstat(argv[1], &sta);
	if(-1 == ret) print_error("main");
	
//显示文件类型
		 if(S_ISREG(sta.st_mode)) 	file_type = '-'; 
	else if(S_ISDIR(sta.st_mode)) 	file_type = 'd'; 
	else if(S_ISCHR(sta.st_mode)) 	file_type = 'c'; 
	else if(S_ISBLK(sta.st_mode)) 	file_type = 'b'; 
	else if(S_ISFIFO(sta.st_mode)) 	file_type = 'p'; 
	else if(S_ISLNK(sta.st_mode)) 	file_type = 'l'; 
	else if(S_ISSOCK(sta.st_mode)) 	file_type = 's'; 
	
	if(file_type!='d')
	{
		 fun_R(argv[1]);
	}else
	{
		fun_DIR(argv[1]);
	}


			
//2-设置当前文件进程掩码-------------------------------------------------------------------------------------------------
	// mode_t=umask(0);
	// printf("mode_t:%d\n",mode_t);
	// fd = open("/home/C/open/file.txt",O_RDWR|O_CREAT,0777);		
	// if(-1 == fd) print_error("main");	

//3-截断测试-------------------------------------------------------------------------------------------------

	// char buf[]="1234567890";
	// fd = open("/home/C/open/file.txt",O_RDWR|O_CREAT,0777);		
    // if(-1 == fd) print_error("main");
    // write(fd,buf,strlen(buf));
	// // truncate("/home/C/open/file.txt",5);
    // ftruncate(fd,20);  //多出的会成为空洞，使用du + 文件 可查看实际块设备上的占用空间
	// close(fd);
	   
//4-lseek空洞测试-------------------------------------------------------------------------------------------------	   
	   
    // char buf[]="1234567890";
	// fd = open("/home/C/open/file.txt",O_RDWR|O_CREAT,0777);		
    // if(-1 == fd) print_error("main");
	// lseek(fd,50,SEEK_SET);
    // write(fd,buf,strlen(buf));
	// close(fd);

//5-硬链接测试-------------------------------------------------------------------------------------------------	

	//link("./file.txt","./file.txt1");
    //unlink("./file.txt1");
	
//6-临时文件测试-------------------------------------------------------------------------------------------------	

	// char buf[10]={0};
	// fd = open("/home/C/open/file.txt",O_RDWR|O_CREAT,0777);
	// if(-1 == fd) print_error("main");
	// unlink("./file.txt");
	// write(fd,"linzijun",strlen("linzijun"));
	// lseek(fd,0,SEEK_SET);
	// read(fd,buf,10);
	// printf("%s\n",buf);
	
//6-文件删除测试-------------------------------------------------------------------------------------------------

		//remove("./file.txt");		//删除文件
		// remove("./file");			//删除目录
	
//rm -> remove->(封装unlink与rmdir)
	
//7-修改文件路径名测试-------------------------------------------------------------------------------------------------

    // rename("./file.txt","../file.txt");		//移动文件
	//rename("./file.txt","./file11.txt");	//修改文件名
		
//mv -> rename

// //8-软(符号)连接测试-------------------------------------------------------------------------------------------------
	// symlink("./file.txt","./file11.txt");
	
// //生成拥有自己inode几点的独立文件


//9-获取当前工作目录与切换目录-------------------------------------------------------------------------------------------------	
	// char buf[30]={0};
	// getcwd(buf,sizeof(buf));
	// printf("%s\n",buf);
	// chdir("../");
	// getcwd(buf,sizeof(buf));
	// printf("%s\n",buf);
	// mkdir("./111",0777);
	// chdir("./111");
	// getcwd(buf,sizeof(buf));
	// printf("%s\n",buf);
	// chdir("../");
	// rmdir("./111");
	
//10-打开目录项读取文件名与iNode节点-------------------------------------------------------------------------------------------------

	// DIR *dirp=NULL;
    // dirp = opendir("/home/C/open");
	// struct dirent * DIRP=NULL;
	// while(1)
	// {
		// DIRP = readdir(dirp);
		// if(DIRP==NULL&&errno!=0)
		// {
			// perror("readdir fail");
			// exit(-1);
		// }
		
		// if(DIRP==NULL&&errno==0) break;
		// printf("inode:%ld--%s\n",DIRP->d_ino,DIRP->d_name);
	// }
	


	return 0;
}












