
char path_shell[1024],savedir[1000];
char tilda[2] = {'~', '\0'};
int a;


int cd_calling(char * path_shell,char *cmd_input)
{

    //printf("inp :%s\n",cmd_input);
    const char s[2] = " ";

    ftoken = strtok(cmd_input,s);
    //printf("%s\n",ftoken);
		if(strcmp(ftoken,"cd") == 0 )
		{
			char *stoken = strtok(0, s);
			//printf("%s",stoken);

			if(stoken == NULL)
			{
				chdir(path_shell);

			}
			else if(stoken[0]==tilda[0])
			{
				chdir(path_shell);
			}
			else if(strcmp(stoken,"-")==0)
			{
				chdir(savedir);
			}
			//else if(strcmp(cmd_input,"cd") == 0)
			//  {
			//    chdir(path_shell);
			//  }
			else if(strcmp(stoken,".")==0)
			{
				a =1;
			}
			else if(strcmp(stoken,"..")==0)
			{
				//you can't write stoken==".." here :(

				chdir("..");
			}
			else if(!stoken)
			{
			        chdir(path_shell);
			}
			else
			{
                             //printf("entered");
			     getcwd(savedir,999);
			     chdir(stoken);
			}
		return 1;
		}
	return 0;
}
