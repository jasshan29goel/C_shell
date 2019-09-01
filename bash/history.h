void write_to_file(char str[],char tilda[])
{	
	char path[200]="";
	strcat(path,tilda);
	strcat(path,"/history.txt");
	int fd1=open(path, O_RDONLY , 0644);
	if(fd1<0)
	{
		printf("failed to store the file in  history\n");
		return;
	}
	int total_offset = lseek(fd1, 0, SEEK_END);
	lseek(fd1, 0, SEEK_SET);
	char *BUFFER=(char *)calloc(10000,sizeof(char));
	read(fd1,BUFFER,total_offset);
	close(fd1);
	int fd = open(path, O_WRONLY | O_CREAT |O_TRUNC, 0644);
	char *to_write=(char *)calloc(100,sizeof(char));
	strcpy(to_write,str);

	int sz=strlen(str);
	to_write[sz]='\0';
	int c=0;
	for (int i = 0; i < sz; ++i)
	{
		if(to_write[i]==' '||to_write[i]=='\t'||to_write[i]=='\n')
			c++;
	}
	if(c==sz)
	{
		write(fd, BUFFER, total_offset); 
		close(fd); 
		return ;
	}
	if(to_write[sz-1]!='\n')
	{
		to_write[sz+1]='\0';
		to_write[sz]='\n';
		sz++;
	}
	// printf("%s\n",to_write );
	lseek(fd, 0, SEEK_SET);
	write(fd, to_write, sz); 
	write(fd, BUFFER, total_offset); 
	close(fd); 

}
int number_of_lines(char tilda[])
{
	char path[200]="";
	strcat(path,tilda);
	strcat(path,"/history.txt");

	FILE *fp; 
	int count = 0; 
	char c;

	fp = fopen(path, "r"); 

	if (fp == NULL) 
	{ 
		return 0; 
	} 

	for (c = getc(fp); c != EOF; c = getc(fp)) 
	{
		if (c == '\n')
		{
			count = count + 1; 
		}
	}
	fclose(fp); 
	return (count);  
}
void remove_last_line(char tilda[])
{
	char path[200]="";
	strcat(path,tilda);
	strcat(path,"/history.txt");

	int fd1=open(path, O_RDONLY , 0644);
	int total_offset = lseek(fd1, 0, SEEK_END);
	lseek(fd1, 0, SEEK_SET);
	char *BUFFER=(char *)calloc(10000,sizeof(char));
	read(fd1,BUFFER,total_offset);
	close(fd1);

	int k=number_of_lines(tilda)-1; 

	int fd = open(path, O_WRONLY | O_CREAT |O_TRUNC, 0644);
	char* token = strtok(BUFFER, "\n");
	int c=0;
	while (token != NULL) 
	{
		// printf("c=%d k=%d\n",c,k );
		if(c==k)
		{
			return ;
		}
		//strcpy(netCommand[i++],token); 
		write(fd,token,strlen(token));	
		write(fd,"\n",1);	
		// printf("%s %d\n",token,strlen(token) );
		token = strtok(NULL, "\n"); 
		c++;
		
	}
	close(fd);


}
void print_top_n_lines(int n,char tilda[])
{
	char path[200]="";
	strcat(path,tilda);
	strcat(path,"/history.txt");

	int fd1=open(path, O_RDONLY , 0644);
	int total_offset = lseek(fd1, 0, SEEK_END);
	lseek(fd1, 0, SEEK_SET);
	char *BUFFER=(char *)calloc(10000,sizeof(char));
	read(fd1,BUFFER,total_offset);
	close(fd1);
	
	char* token = strtok(BUFFER, "\n");
	int c=0;
	while (token != NULL) 
	{
		if(c==n)
		{
			return ;
		}
		printf("%s\n",token );
		token = strtok(NULL, "\n"); 
		c++;
		
	}
}