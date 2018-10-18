//Tahsin Alam
// Part 3  --Prcs_P2
//In this step we are copying the content of source.txt to destination1.txt and destination2.txt with some other procedures.
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>



int main(int argc, char* argv[])
{


/// File Descripters for Source, Destination1, and Destination2 files

int size; // store size of source file
int fd; // file descripter to source file
int fd1; // file descripter to destination1 file
int fd2;// file descripter to destination2 file

fd=open("source.txt",O_RDONLY, S_IRWXU);
fd1=open("destination1.txt",O_WRONLY,S_IRWXU);
fd2=open("destination2.txt",O_WRONLY,S_IRWXU);



/// Check if you are able to open these files

	if(fd == -1) //error opening file
		{
		printf("\n source.txt open() failed to open [%s] \n\n", strerror(errno));
	return 1;
		}
	else
		{
		printf("Source File is able to Open \n");
		}

	if(fd1 == -1) //error opening file
	     {
	     printf("\n destination1.txt open() failed to open [%s] \n\n",strerror(errno));
	return 1; 
	     }
	else
		{
		printf("destination1.txt File is able to Open\n");
		}

	if(fd2 == -1) //error opening file
	    {
	printf("\n destination2.txt open() failed to open [%s] \n\n",strerror(errno));
	return 1;
	    }
	else
		{
		printf("destination2.txt File is able to Open \n");
		}



/// Get size of source.txt file.
FILE *fp =fopen("source.txt", "r"); // open the source file
fseek(fp ,0,SEEK_END); //finds the end of the source file
size = ftell(fp); // gives the file size of the source file
rewind(fp); // Reposition the file handler fp to the beginng of the file
fclose(fp); // closes the handler fp



/// Create two buffers to read the source content
char buffer[100];



int num_of_loops = size/100;


/// Hold read and write system call values
int rt, rt2, ws, ws2;


for (int i=0 ; i < num_of_loops ; i++) // read 100 Chars each iteration 
	{
		rt = read(fd, buffer, 100);
		for (int j=0 ; j < 100 ; j++)
		{
			if (buffer[j] == '1') buffer[j]='A';
		}
		ws =  write (fd1,buffer,100);
	   
	}



int remainder = size%100;
//Reading less than 100 characters at the end of the file
char BUF[remainder]; 
read(fd, BUF, remainder);	

for (int u=0 ; u < remainder ; u++) 
	{
		if (BUF[u] == '1') BUF[u]='A';  //Convert 1 to A
		if (u == remainder-1)           // If reached the end start to write to the destination file.
		{
			write (fd1,BUF,remainder); // The less than 100 chars that were manipluated
			
		}

	}


lseek(fd,0,SEEK_SET);  /// Re set the file descripter fd to the begininng of the source file





char bufferTwo[50];
int num_of_loops2= size/50;
int remainder2 = size%50;

for (int i=0 ; i < num_of_loops2 ; i++) // read 50 Chars each iteration 
	{
		rt2 = read(fd, bufferTwo, 50);
		for (int j=0 ; j < 50 ; j++)
		{
			if (bufferTwo[j] == '2') bufferTwo[j]='B';
		}
		ws2 =  write (fd2,bufferTwo,50);
	   
	}



//Reading less than 50 characters at the end of the file
char BUFF[remainder2]; 
read(fd, BUFF, remainder2);	

for (int u=0 ; u < remainder2 ; u++) 
	{
		if (BUFF[u] == '2') BUFF[u]='B';  //Convert 2 to B
		if (u == remainder2-1)           // If reached the end start to write to the destination file.
		{
			write (fd2,BUFF,remainder2); // The less than 50 chars that were manipluated
			
		}

	}

/// close files
close(fd);
close(fd1);
close(fd2);




return 0;
}

