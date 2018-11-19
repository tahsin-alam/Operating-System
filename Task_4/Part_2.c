//Tahsin Alam
//Lab 4
// Part 2: Average Grade calculator with Director, manager and worker process.
// the input file contains quiz grades for 10 students for x =2 and y =2. The program will calculate the average by each column.

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <string.h>

int main(int argc, char* argv[])
{


char* filename="quiz_grades.txt";
int row=10;
int columns=4;
int status;

double grades[columns][row];
double average[columns];
double acc_grade;
double averages[4];


///Open file

//Check if file exist
int retval= access(filename, F_OK);

if (retval != 0)
{
	if(errno == ENOENT)
	{
	printf("%s doesn't exist \n",filename);
	}
	else if (errno == EACCES)
	{
	printf("%s is not accessible \n", filename);
	return 1;
	}
}

//Check read permission
retval= access(filename, R_OK);

if (retval != 0)
{
printf("%s is not readable (access denied)\n", filename);
return 1;	
}


//Open file
FILE *fd=fopen(filename,"r");


///loading data into two dimensional array

int count_row=0;
int count_columns=0;


while(count_row <= row-1)
{
	while(count_columns <= (columns-1))
	{
	fscanf(fd,"%lf", &grades[count_columns][count_row]);
	count_columns++;
	}

count_columns=0;
count_row++;
}


/// Two Managers with two workers each
// ManagerOne manages workerone and workertwo.

int ManagerOne=fork(); 
if(ManagerOne==0)
{

int workerOne=fork();

	if(workerOne==0)
	{
		for(int R=0;R<row;R++)
		{
		acc_grade+=grades[0][R];
	
		}
	
	printf("Avg Grade for Column 1 is: %lf\n", (acc_grade/(10.0)));
	wait(&status);
        exit(0); 
	}
	else if(workerOne == -1) {
	printf("A worker One WAS NOT created successfully");  
	}   
        else 
        {
            wait(&status);  
        }


int workerTwo=fork();

	if(workerTwo==0)
	{
	 acc_grade=0;
		for(int R=0;R<row;R++)
		{
		acc_grade+=grades[1][R];
	
		}
	
	printf("Avg Grade for Column 2 is: %lf\n", (acc_grade/(10.0)));
	wait(&status);
        exit(0);
	}	
	else if(workerTwo == -1) {
	printf("A worker Two WAS NOT created successfully");     
	}
        else 
        {
            wait(&status);  
        }


}
else if (ManagerOne == -1) 
printf("First manager WAS NOT created successfully");    
else 
wait(&status);



//ManagerTwo manages workerthree and workerFour. 

int ManagerTwo=fork();

if(ManagerTwo==0)
{

int workerThree=fork();
	
	if(workerThree==0)
	{
		acc_grade=0;
		for(int R=0;R<row;R++)
		{
		acc_grade+=grades[2][R];
	
		}
	
	printf("Avg Grade for Column 3 is: %lf\n", (acc_grade/(10.0)));
	wait(&status);
        exit(0);
	}	
	else if(workerThree == -1) {
	printf("A worker Three WAS NOT created successfully");   
	}  
        else 
        {
            wait(&status);  
        }



int workerFour=fork();

	if(workerFour==0)
	{
		acc_grade=0;
		for(int R=0;R<row;R++)
		{
		acc_grade+=grades[3][R];
	
		}
	
	printf("Avg Grade for Column 4 is: %lf\n", (acc_grade/(10.0)));
	wait(&status);
        exit(0);
	}
	else if(workerFour == -1) {
	printf("A worker Four WAS NOT created successfully");     	
	}	
        else 
        {
            wait(&status);  
        }
}
else if (ManagerTwo == -1) 
printf("First manager WAS NOT created successfully");    
else 
wait(&status);

/// Close File
fclose(fd);
return 0;
}
