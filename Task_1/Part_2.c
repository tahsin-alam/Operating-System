//Tahsin Alam
//Part 2
//The cp command copies the source file specified by the SourceFile parameter to the destination file parameter
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char*argv[])
{

int fd, fd2, t,size,x;

if(3 != argc)
{
printf("\n Missing Three Parameters \n");
return 1;
}


fd2 = open(argv[2], O_WRONLY|O_CREAT,S_IRWXU); // open or create the destination file
fd = open(argv[1],O_RDONLY,S_IRWXU); // open the source file that you want to copy from

if(fd == -1) //error opening file
{
printf("sorry, I couldn't open source file\n");
perror("open"); 
}
else
{
printf("Source File is able to Open \n");
}

if(fd2 == -1) //error opening file
{
printf("sorry, I couldn't open destination file\n");
perror("open"); 
}
else
{
printf("Destination File is able to Open or Create \n");
}


// Read the source file

FILE *fp =fopen(argv[1], "r");
fseek(fp ,0,SEEK_END);
size = ftell(fp);
//printf("size: %d", size);
rewind(fp);
fclose(fp);
char* buffer = malloc(size);

x=read(fd,buffer,size);

if (x==-1)
perror("read");

// Write to the destination file

t=write(fd2,buffer,size);

if(t==-1)
perror("write");

//Close The file
close(fd);
close(fd2);

return 0;
}

