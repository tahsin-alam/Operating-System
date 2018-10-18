//Tahsin Alam.
// Part1
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(int argc, char *argv[])
{

int child_One=fork();


if(child_One==0)
{
printf("The Child is succefully created and its pid is: %d\n ", getpid());
execl("/bin/date", argv[0],NULL);
}
else
{
wait(NULL);// wait after one prcoess to finish then execute other.
printf("I am the parent and my PID is : %d\n", getpid());

}




return 0;
}

