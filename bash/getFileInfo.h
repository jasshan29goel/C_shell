void getFileInfo(char path[],char filename[])
{
    char a[100];
    strcpy(a,path);
    struct stat fileStat;

    strcat(a,"/");
    strcat(a,filename);

    if(stat(a,&fileStat) < 0)
    {
        perror("error:  ");    
        return ;
    }
    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group  *gr = getgrgid(fileStat.st_gid);


    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" %lu",fileStat.st_nlink);
    printf(" %s",pw->pw_name );
    printf(" %s",gr->gr_name );
    printf(" %ld",fileStat.st_size);
    char time[100];
    strcpy(time,ctime(&fileStat.st_mtime));
    time[strlen(time)-1]='\0';
    printf(" %s",time );
    printf(" %s",filename );
    printf("\n");
}
