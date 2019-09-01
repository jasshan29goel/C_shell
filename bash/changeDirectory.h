void changeDirectory(char path[])
{
    if(chdir(path)==-1)
    {
       perror("chdir() to path failed"); 

    }
    return ;
}