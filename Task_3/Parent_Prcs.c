//Tahsin Alam.
// Task3 Parent Process  Step 3 & Step 4
// Create two child processes that execute Prcs_P1.c and Prcs_P2.c
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>


int main(void)
{

int Child_one, Child_two;

 Child_one=fork(); // forking child_one

if (Child_one==0)
{
printf("The Child One is succefully created and its pid is: %d\n", getpid());
char *const argv[]={"Prcs_P1",NULL}; //Executes Prcs_P1
execv(argv[0],argv); 
	

	
}




else
{
 wait(NULL);

	sleep(2); ////sleep to introduce delays. sleep two second and start forking.
         Child_two=fork();

	if (Child_two==0)
	{
	printf("The Child Two is succefully created and its pid is: %d\n ", getpid());
	char *const argv[]={"Prcs_P2",NULL}; //executes Prcs_P2
	execv(argv[0],argv);
	}




}





return 0;
}

