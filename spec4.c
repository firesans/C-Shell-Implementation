


struct passwd  *pwd1;
struct group   *grp;
struct tm      *tm;
char  datestring[256];

char gs[1000];
const char s3[2] = ".";
const char s4[2] = "..";

int ls_calling(char *cmd_input)
{

    const char s[2] = " ";
    char *ftoken = strtok(cmd_input,s);

		if(strcmp(ftoken,"ls") == 0)
		{
			char *stoken = strtok(0,s);
			DIR *dir ;
			struct dirent *files;
			struct stat info;

			char buf[1024];


			if(stoken == NULL)
			{
				getcwd(gs,999);
				dir = opendir(gs);
				while((files = readdir(dir)) != NULL)
				{
					if( !(strcmp(files->d_name,".") == 0 || strcmp(files->d_name,"..") == 0) )
						printf("%s\t",files->d_name);
				}
				closedir(dir);
        printf("\n");
		  }
			else if(strcmp(stoken,"-l") == 0)
			{
				getcwd(gs,999);
				dir = opendir(gs);
				while((files = readdir(dir)) != NULL)
				{

          if( !( strcmp(files->d_name,".") == 0 || strcmp(files->d_name,"..") == 0 ) )
          {
				        if (stat(files->d_name, &info) == -1)
                                            continue;
					//printf("%10.10s", sperm (info.st_mode));
					if(S_ISDIR(info.st_mode))
                                                printf("d");
                                        else printf("-");
					if(S_IRUSR & info.st_mode)
                                                printf("r");
                                        else  printf("-");
					if(info.st_mode & S_IWUSR)
                                                printf("w");
                                        else  printf("-");
					if(info.st_mode & S_IXUSR)  printf("x"); else  printf("-");
					if(info.st_mode & S_IRGRP)  printf("r"); else  printf("-");
					if(info.st_mode & S_IWGRP)  printf("w"); else  printf("-");
					if(info.st_mode & S_IXGRP)  printf("x"); else  printf("-");
					if(info.st_mode & S_IROTH)  printf("r"); else  printf("-");
					if(info.st_mode & S_IWOTH)  printf("w"); else  printf("-");
					if(info.st_mode & S_IXOTH)  printf("x"); else  printf("-");
				        //	printf("%4d",info.st_nlink);
					if ((pwd1 = getpwuid(info.st_uid)) != NULL)
					  printf(" %-8.8s", pwd1->pw_name);
                                        else
                                          printf(" %-8d", info.st_uid);
                                        if ((grp = getgrgid(info.st_gid)) != NULL)
                                          printf(" %-8.8s", grp->gr_name);
                                        else
                                          printf(" %-8d", info.st_gid);
					printf(" %9jd ", (intmax_t)info.st_size);
					tm = localtime(&info.st_mtime);
                                        /* Get localized date string. */
          strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
					printf("%s ",datestring);
					printf(" %d ",files->d_type);
					printf("%s \n",files->d_name);
				     }
                              }
			      //	printf("\n");
				closedir(dir);
      }

			else if(strcmp(stoken,"-a") == 0)
			{
                                getcwd(gs,999);
				dir = opendir(gs);
				while((files = readdir(dir)) != NULL)
				{
					if(strcmp(files->d_name,".")||strcmp(files->d_name,".."))
						printf("%s\t",files->d_name);
				}
				closedir(dir);
        printf("\n");
      }
			else if(strcmp(stoken,"-al") == 0 || strcmp(stoken,"-la") == 0 || strcmp(stoken,"-l-a") == 0 || strcmp(stoken,"-a-l") == 0)
			{
                                getcwd(gs,999);
				dir = opendir(gs);
				while((files = readdir(dir)) != NULL)
				{
				        if (stat(files->d_name, &info) == -1)
                                            continue;
					//printf("%10.10s", sperm (info.st_mode));
					if(S_ISDIR(info.st_mode)) printf("d"); else printf("-");
					if(S_IRUSR & info.st_mode)  printf("r"); else  printf("-");
					if(info.st_mode & S_IWUSR)  printf("w"); else  printf("-");
					if(info.st_mode & S_IXUSR)  printf("x"); else  printf("-");
					if(info.st_mode & S_IRGRP)  printf("r"); else  printf("-");
					if(info.st_mode & S_IWGRP)  printf("w"); else  printf("-");
					if(info.st_mode & S_IXGRP)  printf("x"); else  printf("-");
					if(info.st_mode & S_IROTH)  printf("r"); else  printf("-");
					if(info.st_mode & S_IWOTH)  printf("w"); else  printf("-");
					if(info.st_mode & S_IXOTH)  printf("x"); else  printf("-");
				        //	printf("%4d",info.st_nlink);
					if ((pwd1 = getpwuid(info.st_uid)) != NULL)
					  printf(" %-8.8s", pwd1->pw_name);
                                        else
                                          printf(" %-8d", info.st_uid);
                                        if ((grp = getgrgid(info.st_gid)) != NULL)
                                          printf(" %-8.8s", grp->gr_name);
                                        else
                                          printf(" %-8d", info.st_gid);
					printf(" %9jd ", (intmax_t)info.st_size);
					tm = localtime(&info.st_mtime);
                                        /* Get localized date string. */
                                        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
					printf("%s ",datestring);
					printf(" %d ",files->d_type);
					printf("%s \n",files->d_name);
				}
			        //	printf("\n");
				closedir(dir);
			}

			else if(strcmp(stoken,"&") == 0)
		        {
				getcwd(gs,999);
				dir = opendir(gs);
				while((files = readdir(dir)) != NULL)
				{
					if(!(strcmp(files->d_name,".") == 0 || strcmp(files->d_name,"..") == 0) )
						printf("%s\n",files->d_name);
				}
				closedir(dir);
			}

		        else
			{
			  dir = opendir(stoken);
			  while((files = readdir(dir)) != NULL)
			  {
			    	if( !(strcmp(files->d_name,".") == 0 || strcmp(files->d_name,"..") == 0 ) )
						printf("%s\n",files->d_name);
			  }
			  closedir(dir);
		  }
      return 1;
    }
    else
    {
       return 0;
    }

}
