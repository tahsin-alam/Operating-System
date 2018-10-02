//Tahsin Alam
//Check for read and write permission
//Part 0 A
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main (int argc, char* argv[])
{
char* filepath = argv[1];
int returnval;

//Check file existence
returnval= access (filepath, F_OK);
if(returnval == 0)
	printf ("\n %s exist\n", filepath);
else
{

if (errno==ENOENT)
 printf("%s does not exist\n", filepath);
else if (errno == EACCES)
printf ("%s is not accessible\n", filepath);
return 0;
}


//Check read access
returnval= access (filepath,R_OK);

if(returnval==-1)
printf("%s No Read Access\n", filepath); 
else
{
printf("%s Able to Read Access\n", filepath);
}


//check write access
returnval= access(filepath, W_OK);

if(returnval==-1)
printf("%s No Write Access\n", filepath);
else
{
printf("%s Able to Write Access\n", filepath);
}


return 0;

}

