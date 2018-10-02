//Tahsin Alam
//Part 0B
//System call creates new file and opens it.
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main(int argc, char*argv[])
{
 int fd;//file handler
 
 fd=open("destination.txt",(O_RDWR|O_CREAT),S_IRWXU);//Read or create file that has write and read permissions.
  if(fd==-1) //error file can't open
	{
	  printf("\n can't open or creat the file \n");
        }
  else  // or the file will be opened if no error.
      {
	  printf("Created and Opened the file \n");
	}
     
     close(fd);
     return 0;
}
