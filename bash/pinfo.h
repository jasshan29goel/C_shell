int pinfo(int pid,char *memory,char * status,char * ex_path)
{
    int l_status=0;
    int l_memory=0;

    char* stat=(char *)calloc(256, sizeof(char));
    char* stat1=(char *)calloc(256, sizeof(char));
    sprintf(stat,"/proc/%d/stat",pid);
    sprintf(stat1,"/proc/%d/exe",pid);
    int fd = open(stat, O_RDONLY);      

    if (fd < 0) 
    {
            // perror("r1");
           printf("Invalid PID\n");
            return 0; 
            // exit(1); 
    }
    char *BUFFER = (char *) calloc(100100, sizeof(char));
    int sz = read(fd, BUFFER, 100000);
    BUFFER[sz] = '\0';
    int c=0;
    for (int i = 0; i < sz; ++i)
    {
        if(BUFFER[i]==' ')
        {
            c++;
        }
        else if(c==2)
        {
            status[l_status++]=BUFFER[i];
        }
        else if(c==22)
        {
            memory[l_memory++]=BUFFER[i];
        }
    }
    sz=readlink(stat1,ex_path,255);
    ex_path[sz]='\0';
    status[l_status]='\0';
    memory[l_memory]='\0';
    return 1;
}