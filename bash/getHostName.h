char* getHostName()
{
	struct utsname a;
	if(uname(&a)==-1)
	{
		perror("error");
	}

    char *hostbuffer=malloc(256*sizeof(char)); 
    hostbuffer[255]='\0';

    strcpy(hostbuffer,a.nodename);

    return hostbuffer; 

}
