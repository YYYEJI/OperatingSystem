/*
	Write a program that displays the files and subdirectories of the current directory.
	Display name, user ID (uid), group ID (gid), size, and modified date as the following example.
	Make the output as close to the example as possible.

	Example)
		$ ./hw2_2
		hw2_2, uid = 1001, gid = 1001, size = 17032, modified date = 2023/03/11
		NewDir, uid = 1001, gid = 1001, size = 4096, modified date = 2023/03/11
		.., uid = 1001, gid = 1001, size = 4096, modified date = 2023/03/08				// parent directory
		test.txt, uid = 1001, gid = 1001, size = 22, modified date = 2023/03/11
		hw2_3.c, uid = 1001, gid = 1001, size = 7121, modified date = 2023/03/11
		hw2_2.c, uid = 1001, gid = 1001, size = 493, modified date = 2023/03/11
		., uid = 1001, gid = 1001, size = 4096, modified date = 2023/03/1001			// current directory
		hw2_3, uid = 1001, gid = 1001, size = 17320, modified date = 2023/03/11
 
	To solve this problem, search the Internet for the following functions and structures, and learn how to use them.

	Functions:
	    * DIR *opendir(const char *name);
		* int closedir( DIR *dir);
		* struct dirent *readdir(DIR *dir);
		* int stat(const char *path, struct stat *buf);
		* struct tm *localtime(const time_t *timeval);

	Structures:
		* struct DIR
		* struct dirent
		* struct stat
		* struct tm

*/


#include <stdio.h>

#include <dirent.h>        // opendir() 관련 함수
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	DIR *dir_child = NULL;       // DIR은 구조체
	struct dirent *ent = NULL;
	struct stat sbuf;
	// TO DO: open current directory using opendir()


	// TO DO:
	// 	repeat until there is more more directory entry
	//		read a directory entry using readdir()
	// 		get the file state using stat()
	//		convert the modified time into struct tm
	//		display the name, uid, gid, size, and modified date (year, month, day)
	
	dir_child = opendir(".");         // 인수로 받은 디렉토리 오픈, 정상적이면 DIR * 포인터가 리턴되지만 실패하면 NULL을 리턴하고 errno에 에러코드가 들어 갑니다.
	if (NULL != dir_child) {          
        while(ent = readdir(dir_child)) {               // opendir()로 얻어진 디렉토리 포인터를 통해서 디렉토리 정보를 하나씩 차례대로 읽습니다.
			struct tm* t;
			t = localtime(&sbuf.st_mtime);              // 포맷팅을 위해 구조체에 넣기
			
			lstat(ent->d_name, &sbuf);                  // 파일 정보를 읽어오는 함수, arg1: 절대경로, arg2: tat의 구조체 
            printf("%s, ", ent->d_name);			    // .,
			printf("uid = %d, ", sbuf.st_uid);          // uid = 0,
			printf("gid = %d, ", sbuf.st_gid);          // gid = 999,
			printf("size = %ld, ", sbuf.st_size);        // size = ???, modified data = 2023/4/26
			printf("modified date = %d/%d/%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); 

			printf("\n");
		}
    }
	system("ls -al");

	// TO DO: close directory
	closedir(dir_child);

	return 0;
}
