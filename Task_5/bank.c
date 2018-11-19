//Tahsin Alam
// Use of semaphore to correctly synchronize processes.

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
#include"sem.h"
#include<sys/ipc.h>
#include<sys/shm.h>






#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1
#define PERMS 0666 //0666 - To grant read and write permissions
#define BUFSIZE 1  
int *buffer;


FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */
FILE *fp5, *fp6, *fp7;				// Use to acesses three counters, one for each process (Dad, son1,son2)

int sem;        //semaphore variable

void main()
{

 ///////////////////////////////////////////////////////////////////// semaphore creation and initalization to 1
 if((sem=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
 {
   printf("\n can't create sem semaphore");
   exit(1);
 }

sem_create(sem,1);


////////////////////////////////////////////////////////////////////////////////////////////

	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables

	int waitTimeDad, waitTimeSon1, waitTimeSon2;   //Counters for each processes


	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;// orginally 20
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);
	
//////////////////////////////////////////////////////////////////////////////////////////Intialize the counter files to be zero
	//Intialize the number of wait to enter CS to be zero for the dad's counter 
	fp5=fopen("Num_Wait_Dad","w");
	waitTimeDad=0;
	fprintf(fp5, "%d\n",waitTimeDad );
	fclose(fp5);

	//Intialize the number of wait to enter CS to be zero for the Son One's counter 
	fp6=fopen("Num_Wait_Son1","w");
	waitTimeSon1=0;
	fprintf(fp6, "%d\n",waitTimeSon1 );
	fclose(fp6);

	//Intialize the number of wait to enter CS to be zero for the Son Two's counter 
	fp7=fopen("Num_Wait_Son2","w");
	waitTimeSon2=0;
	fprintf(fp7, "%d\n",waitTimeSon2);
	fclose(fp7);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	//Create child processes that will do the updates
		if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
	
		N=5;
		for(i=1;i<=N; i++)
		{
//////////////////////////////////////////////////////////////////////////			
		       P(sem);   //Dad enters CS
/////////////////////////////////////////////////////////////////////////
			
			/////////////////////////////////////////////////////////////////////
			//Increase the counter of wait for both sons since dad's in CS
			fp6=fopen("Num_Wait_Son1", "r+");
			fscanf(fp6, "%d", &waitTimeSon1);
			fseek(fp6,0L,0);
			waitTimeSon1++;
			fprintf(fp6, "%d \n",waitTimeSon1);
			fclose(fp6);
			fp7=fopen("Num_Wait_Son2", "r+");
			fscanf(fp7, "%d", &waitTimeSon2);
			fseek(fp7,0L,0);
			waitTimeSon2++;
			fprintf(fp7, "%d \n",waitTimeSon2);
			fclose(fp7);	
			////////////////////////////////////////////////////////////////////



			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
						
			fscanf(fp1, "%d", &bal2);
			
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */


///////////////////////////////////////////////////////////////////////////////////////////////////////////
			V(sem);  //Dad exits CS
///////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{	
//////////////////////////////////////////////////////////////////////////////////////////////
				P(sem);		//Son1 enters CS
//////////////////////////////////////////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////////////////////////
			// Son1 is in CS, Increase wait counter for Dad and son2
                        fp5=fopen("Num_Wait_Dad", "r+");
			fscanf(fp5, "%d", &waitTimeDad);
			fseek(fp5,0L,0);
			waitTimeDad++;
			fprintf(fp5, "%d \n",waitTimeDad);
			fclose(fp5);
			fp7=fopen("Num_Wait_Son2", "r+");
			fscanf(fp7, "%d", &waitTimeSon2);
			fseek(fp7,0L,0);
			waitTimeSon2++;
			fprintf(fp7, "%d \n",waitTimeSon2);
			fclose(fp7);
			/////////////////////////////////////////////////////////////////////////






				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{       
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					
					fscanf(fp2,"%d", &bal2);
									
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
					
				}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				V(sem);	    //Son1 exits CS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			}
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					P(sem);                          //Son2 enter CS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////////////////////////
			// Son2 is in CS, Increase wait counter for Dad and son1
                        fp5=fopen("Num_Wait_Dad", "r+");
			fscanf(fp5, "%d", &waitTimeDad);
			fseek(fp5,0L,0);
			waitTimeDad++;
			fprintf(fp5, "%d \n",waitTimeDad);
			fclose(fp5);
			fp6=fopen("Num_Wait_Son1", "r+");
			fscanf(fp6, "%d", &waitTimeSon1);
			fseek(fp6,0L,0);
			waitTimeSon1++;
			fprintf(fp6, "%d \n",waitTimeSon1);
			fclose(fp6);
			//////////////////////////////////////////////////////////////////////////////////////////////

					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{     
						printf("Poor SON_2 wants to withdraw money.\n");
					
						fp2 = fopen("balance", "r+");
						
						fscanf(fp2,"%d", &bal2);
						
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					
					}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
					V(sem);        //Son2 exits CS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				} 
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
				////////////////////////////////////////////////////////# of times Dad has waited				
				fp5=fopen("Num_Wait_Dad", "r+");
				fscanf(fp5, "%d", &waitTimeDad);
				printf("Dad # of wait time while either sons in CS is: %d\n", waitTimeDad);
				fclose(fp5);
				//////////////////////////////////////////////////////////////////////////////////
							
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
				///////////////////////////////////////////////////////# of time Son1 has waited				
				fp6=fopen("Num_Wait_Son1", "r+");
			        fscanf(fp6, "%d", &waitTimeSon1);
			    	printf("Son1 # of wait time while either Dad or son2 is in CS is: %d\n", waitTimeSon1);
			        fclose(fp6);
				//////////////////////////////////////////////////////////////////////////////////

				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
				///////////////////////////////////////////////////////# of time Son2 has waited
				fp7=fopen("Num_Wait_Son2", "r+");
			        fscanf(fp7, "%d", &waitTimeSon2);
			    	printf("Son2 # of wait time while either Dad or son1 is in CS is: %d \n", waitTimeSon2);
			        fclose(fp7);
				///////////////////////////////////////////////////////////////////////////////////
				
			}
		
			exit(0);

		}
		

		exit(0);
	}
		
	exit(0);
}




