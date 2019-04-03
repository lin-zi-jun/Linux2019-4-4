#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
// struct passwd {
	// char   *pw_name;       /* username */
	// char   *pw_passwd;     /* user password */
	// uid_t   pw_uid;        /* user ID */
	// gid_t   pw_gid;        /* group ID */
	// char   *pw_gecos;      /* user information */
	// char   *pw_dir;        /* home directory */
	// char   *pw_shell;      /* shell program */
// };

//root x 0 0 root /root /bin/bash

   // struct group {
	   // char   *gr_name;        /* group name */
	   // char   *gr_passwd;      /* group password */
	   // gid_t   gr_gid;         /* group ID */
	   // char  **gr_mem;         /* NULL-terminated array of pointers
								  // to names of group members */
   // };
   
  // struct tm {
   // int tm_sec;    /* Seconds (0-60) */
   // int tm_min;    /* Minutes (0-59) */
   // int tm_hour;   /* Hours (0-23) */
   // int tm_mday;   /* Day of the month (1-31) */
   // int tm_mon;    /* Month (0-11) */
   // int tm_year;   /* Year - 1900 */
   // int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
   // int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
   // int tm_isdst;  /* Daylight saving time */
// };




#define print_error(str) \
do{\
				fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
				perror("error Reason");\
				exit(-1);\
}while(0);

int main(void)
{
	
//1-测试获取用户信息-----------------------------------------------------------------------------------------------------	
	// struct passwd * pw=NULL;
	// // pw = getpwnam("root");
	// pw = getpwuid(0);
	// if(pw==NULL) print_error("getpwuid");

	// printf("%s %s %d %d %s %s %s\n",
	// pw->pw_name,pw->pw_passwd,pw->pw_uid,pw->pw_gid,pw->pw_gecos,pw->pw_dir,pw->pw_shell);
	
//2-测试获取组信息-----------------------------------------------------------------------------------------------------	
	// struct group * gp = NULL;
	// gp = getgrnam("root");
	// if(gp==NULL) print_error("getgrnam");
	// // gp = getgrgid(0);
	
	// printf("%s %s %d ",gp->gr_name,gp->gr_passwd,gp->gr_gid);
	
	// while(1)
	// {
		// static int i=0;
		// if(gp->gr_mem[i]!=NULL)
		// {
			// printf("%s",gp->gr_mem[i]);
			// i++;
		// }else
		// {
			// break;
		// }
	// }
	// printf("\n");

//3-时间测试-----------------------------------------------------------------------------------------------------	

	long int tim = 0;
    time(&tim);
	char * p = NULL;
	char * ascp = NULL;
	p = ctime(&tim);
	
	 struct tm * pt = NULL;
	 pt = localtime(&tim);
	 ascp = asctime(pt);
	printf("%ld\n%s\n",tim,p);
	printf("%d/%d/%d %d:%d:%d\n",pt->tm_year,pt->tm_mon,pt->tm_mday,pt->tm_hour,pt->tm_min,pt->tm_sec);
	printf("%s\n",ascp);
	
	char buf[100]={0};
	strftime(buf,sizeof(buf),"%Y/%m/%d/ %H:%M:%S\n",pt);
	printf("%s",buf);

	return 0;
}





