char *getPresentWorkingDirectory()
{
    char *pwdBuffer=malloc(256*sizeof(char));
    pwdBuffer[255]='\0';

    pwdBuffer=getcwd(pwdBuffer,256);

    if(pwdBuffer==NULL)
    {
        perror("error occoured");
    }
    else
    {
        return pwdBuffer;
    }
}