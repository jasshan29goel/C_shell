void list(char path[],int a_flag,int l_flag)
{
    struct dirent *de;  
    DIR *dr = opendir(path);
    if (dr == NULL)  
    {
        perror("error:");   
        return ;     
    }
    if(l_flag==0)
    {
        if(a_flag==0)
        { 
            while ((de = readdir(dr)) != NULL)
            {
                char *arr=de->d_name;
                if(arr[0]!='.')
                    printf("%s\n",arr );

            }
        }
        else
        {
            while ((de = readdir(dr)) != NULL)
            {
                char *arr=de->d_name;
                printf("%s\n",arr );

            }

        }
    }
    else
    {
        if(a_flag==0)
        { 
            while ((de = readdir(dr)) != NULL)
            {
                char *arr=de->d_name;
                if(arr[0]!='.')
                    getFileInfo(path,arr);
            }
        }
        else
        {
            while ((de = readdir(dr)) != NULL)
            {
                char *arr=de->d_name;
                getFileInfo(path,arr);

            }

        }
    } 
    closedir(dr);     
}
void list_arguments(char argument[],char * path,int *a,int *l)
{
    if(argument[0]=='-')
    {
        for (int i = 1; i < strlen(argument); ++i)
        {
            if(argument[i]=='a')
            {
                *a=1;
            }
            if(argument[i]=='l')
            {
                *l=1;
            }
        }
    }
    else
    {
        strcpy(path,argument);
    }
    return;
}