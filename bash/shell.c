#include "headers.h"

char netCommand[100][100];
char pipeCommand[100][100][100];
int  pipeNum[100];
char tilda[100];

struct typeProc
{
	char name[100];
	int pid;
	int mark;
};

struct typeProc backProc[100];
int numBackProc;

void printCommand(int num) // supply countpipes(i)
{
	for (int i = 0; i <=num; ++i)
	{
		if(i!=0) printf("| ");
		for (int j = 0; j < pipeNum[i]; ++j)
		{
			printf("%s ",pipeCommand[i][j] );
		}
	}
}
void storeCommand(int num,int pid) // supply countpipes(i)
{
	char BUFFER[100];
	for (int i = 0; i <=num; ++i)
	{
		if(i!=0) strcat(BUFFER,"| ");
		for (int j = 0; j < pipeNum[i]; ++j)
		{
			strcat(BUFFER,pipeCommand[i][j]);
			strcat(BUFFER," ");
		}
	}
	strcpy(backProc[numBackProc].name,BUFFER);
	// printf("----------%s---------\n",backProc[numBackProc].name );
	backProc[numBackProc].mark=1;
	backProc[numBackProc].pid=pid;
	numBackProc++;
}
int parsePipes(char *token,int netNum)
{
	char str1[256];
	int i=0,j=0,ctr=0,flag=1,quote=0;

	strcpy(str1,token);
	int len=strlen(str1);
	    // printf("-----------%s----------\n",str1 );

	for(i=0;i<len;i++)
	{
		if((str1[i]==' '||str1[i]=='\n'||str1[i]=='\t')&&flag==1&&quote==0)
		{

		}
		else if((str1[i]==' '||str1[i]=='\n'||str1[i]=='\t')&&flag==0&&quote==0)
		{
			pipeCommand[netNum][ctr++][j]='\0';
			flag=1;
			j=0;
		}
		else if(str1[i]=='\"')
		{
			quote=1-quote;  
		}
		else
		{
			pipeCommand[netNum][ctr][j++]=str1[i];
			flag=0;
		}
	}
	if(flag==0) 
	{
		pipeCommand[netNum][ctr++][j]='\0';
	}
	return ctr;
}
int tokenizeCommand()
{
	char str1[256];
	fgets(str1, sizeof(str1), stdin); 
	write_to_file(str1,tilda);
	if(number_of_lines(tilda)>20)
	{
		remove_last_line(tilda);
	}	

	char* token = strtok(str1, ";"); 
	int i=0;
	while (token != NULL) 
	{
		strcpy(netCommand[i++],token); 
		token = strtok(NULL, ";"); 

	}
	return i;
}
int tokenizePipes(int num)
{
	char str1[256];
	strcpy(str1,netCommand[num]);

	char* token = strtok(str1, "|"); 
	int i=0;
	while (token != NULL) 
	{
		pipeNum[i]=parsePipes(token,i);
		token = strtok(NULL, "|");
		i++; 

	}
	return i;
}

int countPipes(int num)
{
	int k=strlen(netCommand[num]);
	int count=0;
	for (int i = 0; i < k; ++i)
	{
		if(netCommand[num][i]=='|')
		{
			count++;
		}
	}
	return count;
}


int checkIfRedirection(int num)
{
	int j;
	int flag=0;
	for (j = 0; j <num; ++j)
	{
		if(strcmp(pipeCommand[0][j],">")==0||strcmp(pipeCommand[0][j],"<")==0||strcmp(pipeCommand[0][j],">>")==0)
		{
			flag=1;
			break;
		}
	}
	return flag; 
}

int execute_command(int num)
{
	if(strcmp(pipeCommand[0][0],"pwd")==0)
	{
		printf("%s\n",getPresentWorkingDirectory() );
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"echo")==0)
	{
		for (int i = 1; i < num; ++i)
		{
			printf("%s ",pipeCommand[0][i] );
		}
		printf("\n");
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"cd")==0)
	{
		if(num==1)
		{
			changeDirectory(tildaToPath("~",tilda));
		}
		else
		{
			changeDirectory(tildaToPath(pipeCommand[0][1],tilda));
		}
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"ls")==0)
	{
		int a=0;
		int l=0;
		char path[256]="";
		if(num==1)
		{
			a=0;
			l=0;
			strcpy(path,".");
		}
		else 
		{
			for (int i = 1; i < num; ++i)
			{
				list_arguments(pipeCommand[0][i],path,&a,&l);
			}	
		}
		if(strcmp(path,"")==0)
		{
			strcpy(path,".");
		}
        // printf("%s %d %d\n",path,a,l );
		list(tildaToPath(path,tilda),a,l);
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"pinfo")==0)
	{
		int pid;
		char status[256];
		char memory[256];
		char ex_path[256];
		ex_path[255]='\0';
		if(num==1)
		{
			pid=getpid();
		}
		else
		{
			pid=atoi(pipeCommand[0][1]);
		}
		int a=pinfo(pid,memory,status,ex_path);
		if(a)
		{
			printf("pid--%d \n",pid );
			printf("process status--%s\n",status);
			printf("memory--%s\n",memory );
			printf("executable path--%s\n",ex_path );
		}
		else
		{
			printf("Invalid PID\n");
		}
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"history")==0)
	{
		if(num==1)
		{
			print_top_n_lines(10,tilda);
		}
		else
		{	
			int k=atoi(pipeCommand[0][1]);
			if(k>10)
			{
				print_top_n_lines(10,tilda);
			}
			else
			{
				print_top_n_lines(k,tilda);			
			}
		}
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"jobs")==0)
	{
		char status[256];
		char memory[256];
		char ex_path[256];
		ex_path[255]='\0';

		for (int i = 0; i < numBackProc; ++i)
		{
			int a=pinfo(backProc[i].pid,memory,status,ex_path);
			if(a<=0||strcmp(status,"Z")==0) continue;
			printf("[%d] %s %s %d\n",i,status,backProc[i].name,backProc[i].pid );
		}
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"kjob")==0)
	{
		kill(backProc[atoi(pipeCommand[0][1])].pid,atoi(pipeCommand[0][2]));
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"bg")==0)
	{
		kill(backProc[atoi(pipeCommand[0][1])].pid,SIGCONT);
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"fg")==0)
	{
		waitpid(backProc[atoi(pipeCommand[0][1])].pid-1,NULL,WCONTINUED);
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"overkill")==0)
	{
		char status[256];
		char memory[256];
		char ex_path[256];
		ex_path[255]='\0';

		for (int i = 0; i < numBackProc; ++i)
		{
			int a=pinfo(backProc[i].pid,memory,status,ex_path);
			if(a<=0||strcmp(status,"Z")==0) continue;
			kill(backProc[i].pid,9);
		}
		return 1;
	}
	else if(strcmp(pipeCommand[0][0],"quit")==0)
	{
		exit(0);
	}
	return 0;
}



void pipeRedirection(int i)
{
	char *args[20];
	int j;
	int flag=0;
	for (j = 0; j < pipeNum[i]; ++j)
	{
		if(strcmp(pipeCommand[i][j],">")==0||strcmp(pipeCommand[i][j],"<")==0||strcmp(pipeCommand[i][j],">>")==0)
		{
			flag=1;
			break;
		}
		args[j]=pipeCommand[i][j];
	} 
	args[j]=NULL;
	if(flag!=0)
	{
		for (int k = 0; k < pipeNum[i]; ++k)
		{
			if(strcmp(pipeCommand[i][k],">")==0)
			{
				int out = open(pipeCommand[i][k+1],O_WRONLY|O_CREAT,0666);
				if(out < 0)
				{
					perror("file opening/creation not ok");
					exit(0);
				}
				if(dup2(out,STDOUT_FILENO)==-1)
				{
					perror("dup2 failed");
					exit(0);		
				}
				close(out);	
			}
			if(strcmp(pipeCommand[i][k],"<")==0)
			{
				int in = open(pipeCommand[i][k+1],O_RDONLY);
				if(in < 0)
				{
					perror("file does not exist");
					exit(0);
				}
				if(dup2(in,STDIN_FILENO)==-1)
				{
					perror("dup2 failed");
					exit(0);
				}
				close(in);
			}
		}
	}
	if(execvp(args[0],args)==-1)
	{
		perror("command could not be run");
		exit(127);
	}

}
void executePipe(int num_pipes)
{
	if(num_pipes==0)
	{
		pipeRedirection(0);
	}
	int fildes[100];


	for (int i = 0; i < num_pipes; ++i)
	{
		if(pipe(fildes+2*i) != 0)
		{
			perror("pipe failed");
			exit(0);
		}

	}
	for (int i = 0; i < num_pipes+1; ++i)
	{

		int pid;
		pid=fork();
		// printf("ans=%d\n",pid );
		if(pid<0)
		{
		// error
		}
		else if(pid==0)
		{
			if(i!=0)
			{
				if(dup2(fildes[2*i-2],0)==-1)
				{
					perror("dup2 failed");
					exit(0);
				}
			}
			if(i!=num_pipes)
			{
				if(dup2(fildes[2*i+1],1)==-1)
				{
					perror("dup2 failed");
					exit(0);
				}
			}

			for (int j = 0; j < 2*num_pipes; ++j)
			{
				close(fildes[j]);
			}
			pipeRedirection(i);
		}
	}
	for (int i = 0; i < 2*num_pipes; ++i)
	{
		close(fildes[i]);
	}
	
	int status;
	for(int i = 0; i < num_pipes+1; i++)
	{ 
		wait(&status);
	}
	exit(0);
}

void foreground_process_execute(int num)
{
	int pid;
	pid=fork();
	if(pid<0)
	{
		// error
	}
	else if(pid==0)
	{
		executePipe(num);	
	}
	else
	{
		//printf("%d\n",pid );
		int status; 

		// wait(&status); 
		waitpid(pid,&status,0);
		
		//	printf("yes\n");
		

		if ( WIFEXITED(status) ) 
		{ 
			int exit_status = WEXITSTATUS(status);         
			if(exit_status==0)
			{
			}
			else
			{
				printf("command not found\n"); 
			}
		}
		else
		{
			printf("Exited abnormally\n"); 

		} 		
	}

}

void background_process_execute(int num)
{
	pipeNum[num]--;
	int pid=fork();
	int pid1;
	if (pid<0) 
	{
		// error
	}
	else if(pid>0)
	{
		printCommand(num);
		printf("Initiated\n");

	}
	else
	{
		pid1=fork();
		// printf("%d\n",pid1 );
		if(pid1<0)
		{
		// error
		}
		else if(pid1==0)
		{
			executePipe(num);	
		}
		else
		{
			printf("%d \n",pid1 );
			int status; 

			wait(&status); 

			if ( WIFEXITED(status) ) 
			{ 
				int exit_status = WEXITSTATUS(status);         
				printCommand(num);
				if(exit_status==0)
				{
					printf("Exited %d Normally(0)\n",pid1); 
				}
				else
				{
					printf("command not found\n"); 

				}
			}
			else
			{
				printCommand(num);
				printf("Exited %d abnormally\n",pid1); 

			} 
		}
		exit(0);
	}
	storeCommand(num,++pid);
}

int main() 	
{ 
	numBackProc=0;
	strcpy(tilda,getPresentWorkingDirectory());

	while(1)
	{
		printf("%s@%s:%s>",getUserName(),getHostName(), pathToTilda(getPresentWorkingDirectory(),tilda));

		int netNum=tokenizeCommand();
		for (int i = 0; i < netNum; ++i)
		{
			tokenizePipes(i);
			int k=countPipes(i);
			if(k==0)
			{
				int flag=checkIfRedirection(pipeNum[0]);
				if(flag==0&&(pipeNum[0]==0||execute_command(pipeNum[0]))) continue;
			}
			if(strcmp(pipeCommand[k][pipeNum[k]-1],"&")==0)
			{
				background_process_execute(k);	
			}
			else
			{
				foreground_process_execute(k);
			}
		}

	}
	return 0; 
} 

