// Tahsin Alam
// Part2
//child created to execute command that shows all types of files.
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char* argv[])
{
int child_One=fork();  

  
if(child_One==0)
{
printf("The Child is succefully created and its pid is: %d\n ", getpid());
execvp("ls", &argv[0]); // show all files 
}
else
{
wait(NULL); // this make the system after one forking process and then do another.
printf("I am the parent and my PID is :%d\n", getpid());

}

return 0;
}

