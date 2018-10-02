//Tahsin Alam
// Two Child process management system creation
//Part 1
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>

int main()
{
printf("I am the parent. My pid: %d\n", getpid());
int status1, status2,pid_childOne,pid_childTwo;

    int child_One=fork();
	if(child_One==0)
	{
	printf("I am child one, my pid is: %d\n",getpid());
	printf("My parent is: %d\n",getppid());
	}
	else
	{
	printf("In parent mode. My pid is: %d\n", getpid());
	
	
	
        int child_Two=fork();
		if(child_Two==0)
		{
		printf("I am child Two, my pid is: %d\n",getpid());
		printf("My parent is: %d\n",getppid());
		}
		else{
		pid_childOne=waitpid(child_One,&status1,0);
		pid_childTwo=waitpid(child_Two,&status2,0);}
	}



return 0;
}
