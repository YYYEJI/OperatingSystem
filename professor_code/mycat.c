#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>


//#define _DEBUG

void CatFile(const char *filename);

int main()
{
	CatFile("mycat.c");

	return 0;
}


#define BUFFER_SIZE 512
char buffer[BUFFER_SIZE];

void CatFile(const char *filename)
{
#ifdef	_DEBUG
	printf("pass (line = %d)\n", __LINE__);
#endif	//	_DEBUG

	// open file
	int fd = open(filename, O_RDONLY, 0);
	if(fd <= 0){
		printf("Failed to open file %s\n", filename);
		return;
	}

#ifdef	_DEBUG
	printf("pass (line = %d)\n", __LINE__);
#endif	//	_DEBUG

	size_t size = 0;
	// repeat
	//		read a block from the file
	//		print each characters in the block
//	while(1){
	do {
		size = read(fd, buffer, BUFFER_SIZE);
		if(size <= 0)
			break;

		for(int i = 0; i < size; i++)
			putchar(buffer[i]);
	} while(size > 0);
		
#ifdef	_DEBUG
	printf("pass (line = %d)\n", __LINE__);
#endif	//	_DEBUG

	// close file
	close(fd);

#ifdef	_DEBUG
	printf("pass (line = %d)\n", __LINE__);
#endif	//	_DEBUG
}
