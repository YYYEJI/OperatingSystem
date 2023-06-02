// Peer review HW 2-3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 2

#define MAX_PATH 256			// maximum length of pathnames
#define BUFFER_SIZE 512			// the size of buffer to copy files

int CheckAndCreateDirectory(char *file_path);
int CopyFile(char *src_path, char *dest_path);

int main(int argc, char *argv[])
{
	// display the command line arguments
	printf("%d arguments:\n", argc);
	for(int i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);


	// if argc < 3, display the usage and terminate.
	if(argc < 3){
		printf("Usage: %s <src_path> <dest_path>\n", argv[0]);
		return 0;
	}

	char *src_path = argv[1];
	char *dest_path = argv[2];

	// test if the source file exists and is readible.
	// access(const char *pathname, int mode);       
	// R_OK 는 읽기, W_OK 는 쓰기, X_OK 는 실행 여부를 체크하며 F_OK 는 파일의 존재유무를 체크
	// 권한이 성공적으로 체크되었다면, 0 그렇지 않았다면 -1 이 반환되며, 적당한 errno 값이 세팅된다.
	if(access(src_path, R_OK) != 0){
		printf("Error! File %s does not exist or is not readible!\n", src_path);
		exit(-1);
	}

	// check whether the destination directory exists. otherwise, create the directory
	printf("Preparing directory...\n");
	int success = CheckAndCreateDirectory(dest_path);
	printf("result = %d\n", success);

	// copy file
	printf("Copying file %s to %s\n", src_path, dest_path);
	if(success)
		success = CopyFile(src_path, dest_path);

	// on success, run 'ls -al <dest_path>' by calling the system() function
	// otherwise, display an error message.
	if(success){
		printf("%s was successfully copied to %s\n", src_path, dest_path);

		char cmd[MAX_PATH] = "";
		sprintf(cmd ,"ls -al %s", dest_path);
		system(cmd);
	} else {
		printf("Failed to copy %s to %s!\n", src_path, dest_path);
	}

	return 0;
}

int CheckAndCreateDirectory(char *file_path)
// TO DO: check if the desination directory exists. otherwise, create the destination directory.
// 		if the destination directory exists or successfully created, return TRUE
//		otherwise, return FALSE
{
	
	//  Algorithm)
	// 	repeat for i from 0 to the length of file_path
	//		if file_path[i] is a delimitor ('/'),
	//			make a subdirectory path as a string with the characters from file_path[0] to file_path[i].
	//		 		(don't foreget to add '\0' at the end of the string)
	//			if the subdirectory exists and is writable,
	//				display a message indicating the subdirectory exists.
	//			otherwise,
	//				create the subdirectory.		// use mkdir() with mode 0766
	//				on success,
	//					display a message indicating the subdirectory is created
	//				otherwise,
	//					display an error message and return FALSE
	//
	//  return TRUE

	static char subdir[MAX_PATH] = "";
	int len = strlen(file_path);
    int status;
    
    for(int i=0; i<len; i++) {
        if(file_path[i] == '/') {
            strncpy(subdir, file_path, i+1);
            subdir[i] = '\0';
            status = access(subdir, F_OK);
            if(status == 0) {
                printf("Found directory %s.\n", subdir);
            }
            else if(status == -1) {
                status = mkdir(subdir, 0766);
                if(status == 0) {                 // success
                    printf("Directory %s was created.\n", subdir);
                }
                else {                            // Fail
                    printf("Error! Failed to create %s!\n.", subdir);
                    return FALSE;
                }
            }
        }
    }

	return TRUE;
}

int CopyFile(char *src_path, char *dest_path)
// TO DO: copy src_path to dest_path
//		assume the destination directory exists
{
	int src = open(src_path, O_RDONLY, 0);
	printf("src = %d\n", src);	
	
    /*
	// TO DO: on failure, display an error message and return FALSE
    if (src < 0) {           // Fail, if success, it returns src>0
        printf("Failed to open source file!\n");
        return FALSE;
    }

	int dest = open(dest_path, O_WRONLY | O_CREAT, 0644);
	printf("dest = %d\n", dest);

	// TO DO: on failure, display an error message and return FALSE
    if (dest < 0) {          // Fail
        printf("Failed to create destination file!\n");
        close(src);
        return FALSE;
    }

	static char buffer[BUFFER_SIZE];
	ssize_t read_size = 0, written_size = 0;

	// TO DO:
	// repeat until there is no more byte to read
	//		read maximum BUFFER_SIZE bytes from the source file into the buffer, storing the number of bytes actually read in a variable.
	//		write the buffer into the destination file

	while ((read_size = read(src, buffer, BUFFER_SIZE)) > 0) {      
        written_size = write(dest, buffer, read_size);
        if (written_size != read_size) {
            printf("Failed to write to destination file!\n");
            // close는 마지막에 한 번만 해주세요.
            close(src);
            close(dest);
            return FALSE;
        }
        printf("read_size = %ld, written_size = %ld\n", read_size, written_size);
    }
    printf("read_size = %ld, written_size = %ld\n", read_size, written_size);

    // read()함수의 return 값은 음수값이 될 수 없기 때문에 if문의 조건을 변경해야 될 것 같습니다.
    if (read_size < 0) {
        printf("Failed to read source file!\n");
        // close는 마지막에 한 번만 해주세요.
        close(src);
        close(dest);
        return FALSE;
    }

	// TO DO: close the source and destination files
	close(src);
    close(dest);

    */

   // TO DO: on failure, display an error message and return FALSE
    if (src < 0) {           // Fail, if success, it returns src>0
        printf("Failed to open source file!\n");
        return FALSE;
    }

	int dest = open(dest_path, O_WRONLY | O_CREAT, 0644);
	printf("dest = %d\n", dest);

	// TO DO: on failure, display an error message and return FALSE
    if (dest < 0) {          // Fail
        printf("Failed to create destination file!\n");
        close(src);
        return FALSE;
    }

	static char buffer[BUFFER_SIZE];
	ssize_t read_size = 0, written_size = 0;

	while ((read_size = read(src, buffer, BUFFER_SIZE)) > 0) {      
        written_size = write(dest, buffer, read_size);
        if (written_size != read_size) {
            printf("Failed to write to destination file!\n");
            return FALSE;
        }
        printf("read_size = %ld, written_size = %ld\n", read_size, written_size);
    }
    printf("read_size = %ld, written_size = %ld\n", read_size, written_size);

    if (read_size == 0) {
        printf("Failed to read source file!\n");
        return FALSE;
    }

	close(src);
    close(dest);
	
	return TRUE;
}


// Peer review HW 2-2 (time() 함수가 현재까지 흐른 시간을 적용해 준다는 것을 발견해서 메모용으로 작성했습니다.)
// #include <stdio.h>

// #include <dirent.h>
// #include <sys/stat.h>
// #include <stdlib.h>
// #include <time.h>

// int main()
// {
// 	DIR *dir_child = NULL;
// 	struct dirent *ent = NULL;
// 	struct stat sbuf;
	
//     // Previous code
// 	/* 
// 	dir_child = opendir(".");
// 	if (NULL != dir_child) {
//         while(ent = readdir(dir_child)) { 
//          // modified time이 이상합니다.
// 			time_t timer;
// 			struct tm* t;
// 			timer = time(&sbuf.st_mtime);               
// 			t = localtime(&sbuf.st_mtime);              
			
// 			lstat(ent->d_name, &sbuf);
//             printf("%s, ", ent->d_name);
// 			printf("uid = %d, ", sbuf.st_uid);
// 			printf("gid = %d, ", sbuf.st_gid);
// 			printf("size = %ld,", sbuf.st_size);
// 			printf("modified data = %d/%d/%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); 

// 			printf("\n");
// 		}
//     }

//     // system() 함수 추가해주세요.

// 	// TO DO: close directory
// 	closedir(dir_child);
//     */

//    // Update code
//    dir_child = opendir(".");
// 	if (NULL != dir_child) {
//         while(ent = readdir(dir_child)) { 
// 			struct tm* t;
// 			t = localtime(&sbuf.st_mtime);              // 포맷팅을 위해 구조체에 넣기
			
// 			lstat(ent->d_name, &sbuf);
//             printf("%s, ", ent->d_name);
// 			printf("uid = %d, ", sbuf.st_uid);
// 			printf("gid = %d, ", sbuf.st_gid);
// 			printf("size = %ld,", sbuf.st_size);
// 			printf("modified data = %d/%d/%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); 

// 			printf("\n");
// 		}
//     }
// 	system("ls -al");

// 	// TO DO: close directory
// 	closedir(dir_child);

// 	return 0;
// }
