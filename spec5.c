
const char s[2] = " ";

int pinfo_calling(char *cmd_input)
{
             char *ftoken = strtok(cmd_input,s);
             if(strcmp(ftoken,"pinfo") == 0)
             {
                     //printf("entered");
                     FILE *fd1,*fd2;
		     int flag_notexist = 0;
		     char *stoken = strtok(0,s);
                     //printf("stoken : %s",stoken);

                     char exec_stat[256],buffer1[256],buffer2[256],buffer3[256];
                     char state;
                     int pid;
                     long unsigned int vmsize;

                     if(stoken == NULL)
		     {
			     sprintf(buffer1,"/proc/%d/stat",getpid());
			     sprintf(buffer2,"/proc/%d/statm",getpid());
			     sprintf(buffer3,"/proc/%d/exe",getpid());
	             }
		     else
		     {
			     sprintf(buffer1,"/proc/%s/stat",stoken);
			     sprintf(buffer2,"/proc/%s/statm",stoken);
			     sprintf(buffer3,"/proc/%s/exe",stoken);
		     }

		     fd1 = fopen(buffer1,"r");
		     if(fd1 != NULL)
		     {
			     flag_notexist = 1;
		      	     fscanf(fd1,"%d %*s %c",&pid,&state);
		             fclose(fd1);
		             fd2 = fopen(buffer2,"r");
		             fscanf(fd2,"%lu",&vmsize);
		             fclose(fd2);
	             }

                     if(flag_notexist)
                     {
			     printf("Process Id: %d\n",pid);
		             printf("State : %c\n",state);
		             printf("VirtualMemorySize:  %lukB\n",vmsize);

                             readlink(buffer3,exec_stat,256);
		             printf("Executable Path: %s\n",exec_stat);
		     }
		     else
		     {
			     fprintf(stderr,"No such process with given pid\n");
		     }
                     //free(fd1);
                     //free(fd2);
                  return 1;

             }
             else
             {
                  return 0;
             }
}
