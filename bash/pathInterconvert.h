
char * tildaToPath(char *path,char *tilda)
{
	char *finalPath=(char *)malloc(256*sizeof(char));
	if(path[0]!='~')
		return path;
	int j=0;
	int k=strlen(tilda);
	for (int i=0; i < k; ++i)
	{
		finalPath[j++]=tilda[i];
	}
	int l =strlen(path);
	for (int i = 1; i < l; ++i)
	{
		finalPath[j++]=path[i];
	}
	finalPath[j]='\0';
	return finalPath;

}
char * pathToTilda(char *path,char *tilda)
{
	char *finalPath=(char *)malloc(256*sizeof(char));
	int k=strlen(tilda);
	int l=strlen(path);
	int flag=0;
	int i;
	int j=0;
	if(k<=l)
	{
		for (i = 0; i < k; ++i)
		{
			if(tilda[i]!=path[i])
			{
				flag=1;
			}
		}
	}
	if(flag==0&&k<=l)
	{
		finalPath[j++]='~';
		for (; i <l; ++i)
		{
			finalPath[j++]=path[i];
		}
		finalPath[j]='\0';
		return finalPath;
	}
	else
	{
		return path;
	}
}