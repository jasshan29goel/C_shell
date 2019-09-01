#include "headers.h"

char command[100][100];
char netCommand[100][100];
char tilda[100];

int parseCommand(int netNum)
{
	char str1[256];
	int i=0,j=0,ctr=0,flag=1,quote=0;

	strcpy(str1,netCommand[netNum]);
	int len=strlen(str1);
	    // printf("-----------%s----------\n",str1 );

	for(i=0;i<len;i++)
	{
		if((str1[i]==' '||str1[i]=='\n'||str1[i]=='\t')&&flag==1&&quote==0)
		{

		}
		else if((str1[i]==' '||str1[i]=='\n'||str1[i]=='\t')&&flag==0&&quote==0)
		{
			command[ctr++][j]='\0';
			flag=1;
			j=0;
		}
		else if(str1[i]=='\"')
		{
			quote=1-quote;  
		}
		else
		{
			command[ctr][j++]=str1[i];
			flag=0;
		}
	}
	if(flag==0) 
	{
		command[ctr++][j]='\0';
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
int execute_command(int num)
{
	if(strcmp(command[0],"pwd")==0)
	{
		printf("%s\n",getPresentWorkingDirectory() );
		return 1;
	}
	else if(strcmp(command[0],"echo")==0)
	{
		for (int i = 1; i < num; ++i)
		{
			printf("%s ",command[i] );
		}
		printf("\n");
		return 1;
	}
	else if(strcmp(command[0],"cd")==0)
	{
		if(num==1)
		{
			changeDirectory(tildaToPath("~",tilda));
		}
		else
		{
			changeDirectory(tildaToPath(command[1],tilda));
		}
		return 1;
	}
	else if(strcmp(command[0],"ls")==0)
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
				list_arguments(command[i],path,&a,&l);
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
	else if(strcmp(command[0],"pinfo")==0)
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
			pid=atoi(command[1]);
		}
		int a=pinfo(pid,memory,status,ex_path);
		if(a)
		{
			printf("pid--%d \n",pid );
			printf("process status--%s\n",status);
			printf("memory--%s\n",memory );
			printf("executable path--%s\n",ex_path );
		}
		return 1;
	}
	else if(strcmp(command[0],"history")==0)
	{
		if(num==1)
		{
			print_top_n_lines(10,tilda);
		}
		else
		{	
			int k=atoi(command[1]);
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
	else if(strcmp(command[0],"quit")==0)
	{
		exit(0);
	}
	return 0;
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
		char *args[20];
		for (int i = 0; i < num; ++i)
		{
			args[i]=command[i];
		} 
		args[num]=NULL;
		if(execvp(args[0],args)==-1)
		{
			exit(127);
		}
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
	int pid=fork();
	int pid1;
	
	if (pid<0) 
	{
		// error
	}
	else if(pid>0)
	{
		for (int i = 0; i < num; ++i)
		{
			printf("%s ",command[i] );
		} 
		printf("Initiated\n");

	}
	else
	{
		pid1=fork();
		if(pid1<0)
		{
		// error
		}
		else if(pid1==0)
		{
			char *args[20];
			for (int i = 0; i < num; ++i)
			{
				args[i]=command[i];	
			} 
			args[num]=NULL;
			if(execvp(args[0],args)==-1)
			{
				exit(127);
			}
		}
		else
		{
			//printf("%d \n",pid1 );
			int status; 

			wait(&status); 

			if ( WIFEXITED(status) ) 
			{ 
				int exit_status = WEXITSTATUS(status);         
				for (int i = 0; i < num; ++i)
				{
					printf("%s ",command[i] );
				} 
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
				for (int i = 0; i < num; ++i)
				{
					printf("%s ",command[i] );
				} 
				printf("Exited %d abnormally\n",pid1); 

			} 
		}
		exit(0);
	}

}



int main() 
{ 
	strcpy(tilda,getPresentWorkingDirectory());

	while(1)
	{
		printf("%s@%s:%s>",getUserName(),getHostName(), pathToTilda(getPresentWorkingDirectory(),tilda));

		int netNum=tokenizeCommand();
		for (int i = 0; i < netNum; ++i)
		{
			int num=parseCommand(i);
			if(num==0||execute_command(num)) continue;

			if(strcmp(command[num-1],"&")==0)
			{
				background_process_execute(num-1);	
			}
			else
			{
				foreground_process_execute(num);
			}
		}

	}
	return 0; 
} 

