
int k = 1;
char untinput[1024],cmd_input1[1024],wrt[1024],ans[1000];
char path_shell[1024],wrt1[1024];
char pd[1024];
char *ftoken;

//pwd

int pwd_calling(char *path_shell,char *cmd_input,char *outputf)
{
	//printf("OUTPUTFILE: %s",outputf);
	int i,fout;

	if(strcmp(cmd_input, "pwd")==0 && getcwd(pd,1000) ==NULL && outputf[0]=='\0')
	{
		printf ("Can not get current working directory\n");
	}

	else if(strcmp(cmd_input, "pwd")==0 && getcwd(pd,999) != NULL && outputf[0]=='\0')
	{
		//pd = removeSubstring(pd, path_shell);
		k=1;
		wrt[0] = '~';
		for(i=strlen(path_shell);i<strlen(pd);i++)
		{
			wrt[k]=pd[i];
			k++;
		}
		wrt[k]='\0';
		//strcat(tilda1,wrt);
		printf("%s\n",wrt);
	}
	//	if(outputf[0]=='\0') printf("%s\n",wrt);
//	else if(outputf[0]!='\0')
	else
	{	
/*		if(strcmp(cmd_input, "pwd")==0 && getcwd(pd,999) != NULL)
		{
			//pd = removeSubstring(pd, path_shell);
			k=1;
			wrt[0] = '~';
			for(i=strlen(path_shell);i<strlen(pd);i++)
			{
				wrt[k]=pd[i];
				k++;
			}
			wrt[k]='\0'; }*/
		printf("ENTER~~~~~\n");
		
				if(access(outputf,F_OK)==0 && access(outputf,W_OK)!=0)		//Permission to open in Write mode
				{
					printf("You dont have permission to access %s\n",outputf);
					//continue;
				}
				else
				{
					if(access(outputf,F_OK))				//write permissions only for user
						creat(outputf,0600);
					fout=open(outputf,O_WRONLY,0600);
					if(fout<0)
						printf("1 File error\n");
					if(dup2(fout,1)<0)
						printf("2 File error\n");
					close(fout);
				}
			}

		//	getcwd(pwd,100);
		//	printf("%s\n", pwd);
		getcwd(ans,999);
	printf("%s\n", ans);


	//getcwd(ans,999);
//	printf("%s\n", ans);
	//printf("%s\n",wrt);
	return 1;
}

//echo 

int echo_calling(char *cmd_input)
{

	int i;
	//printf("%s",cmd_input);
	const char s[2] = " ";
	ftoken = strtok(cmd_input,s);
	//printf("%s",ftoken);
	const char s1[2] = "\n";
	if(strcmp(ftoken,"echo") == 0)
	{
		char *stoken = strtok(0,s1);
		//int len = strlen(stoken);
		//printf("%s",stoken);

		if(!stoken)
		{
			fprintf(stderr," ");
		}
		else if((int)stoken[0] == 34)
		{
			int len = strlen(stoken);
			for(i=1;i<len-1;i++)
			{
				printf("%c",stoken[i]);
			}
		}
		else
		{
			printf("%s",stoken);

		}
		printf("\n");
		return 1;
		//continue;
	}
	else
	{
		return 0;
	}
}
