//Tahsin Alam
//command displaycontent takes a text file(sample.txt) as an arguement an display its content. 
#include <stdio.h>

int main(int argc, char *argv[])
{
 FILE *fp;
 char *filename;
 char ch;

  // Check if a filename has been specified in the command
  if (argc < 2)
   {
        printf("Missing Filename\n");
        return(1);
   }
   else
  {
        filename = argv[1];
        printf("File Name : %s\n", filename);
   }

   // Open file in read-only mode
   fp = fopen(filename,"r");

   // If file opened successfully, then print the contents
   if ( fp )
      {
        printf("File contents:\n");
        while ( (ch = fgetc(fp)) != EOF )
           {
                printf("%c",ch);
           }

       }
   else
      {
         printf("Failed to open the file\n");
        }
 

return(0);
}
