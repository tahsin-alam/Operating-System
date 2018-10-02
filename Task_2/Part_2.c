/Tahsin Alam
//Part 2
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>

int main()
{

//Parent P
int a=10, b=25, fq=0, fr=0;


printf("My process as parent is: %d\n",getpid());

fq=fork();// fork a child -call it Process Q

if(fq==0)
{
a=a+b;

printf("The value of a at Q child %d\n",a);
printf("The value of b at Q child %d\n",b);
printf("The value of process id at Q child is:  %d\n",getpid());
printf("My parent is: %d\n",getppid());

	fr=fork(); // fork a child -call it process R

	if(fr!=0)
	{
	b=b+20;////Q parent of R

	printf("The value of a parent of R at  %d\n",a);
	printf("The value of b parent of R at  %d\n",b);
	printf("The value of process id parent of R at Q is:  %d\n",getpid());
	printf("My parent of R process Q is : %d\n",getppid());
	}
	else 
	{
	a=(a*b)+30;  ///R
	printf("The value of a in process R %d\n",a);
	printf("The value of b in process R %d\n",b);
	printf("The value of pid in process R :  %d\n",getpid());
	printf("My parent of R is : %d\n",getppid());
	}


}
else
{
b=a+b-5;
	printf("The value of a parent of Q %d\n",a);
	printf("The value of b parent of Q %d\n",b);
	printf("The value of process id of parent Q  is:  %d\n",getpid());

}





return 0;
}

