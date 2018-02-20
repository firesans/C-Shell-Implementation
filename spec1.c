#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <setjmp.h>
//colors:
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

#include "spec2.c"
#include "spec3.c"
#include "spec4.c"
#include "spec5.c"
#include "spec6.c"
sigjmp_buf ctrlz_buf;
void sig_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		sleep(0);
	}
	else if (signo == SIGKILL)
	{
		sleep(0);
	}
	else if (signo == SIGSTOP)
	{
		sleep(0);
	}
	else if (signo == SIGINT)
	{
		sleep(0);
		printf("\n");
	}
	else if(signo==SIGTSTP)
	{
		printf("\n");
		sleep(0);

	}
	else if (signo==SIGCHLD)
	{
		sleep(0);
	}

	if(signo != SIGCHLD)				//If it's sigchild, ignore prompt prompt gets printed and SIGCHILD message
		siglongjmp(ctrlz_buf, 1);		//To go back to prompt
}

void welcomeScreen(){
        printf("\n\t=================================================\n");
        printf("\t              C Shell - Sanjana \n");
        printf("\t=================================================\n");
        printf("\n\n");
}

const char* get_process_name_by_pid(const int pid)
{
	char* name = (char*)calloc(1024,sizeof(char));
	if(name){
		sprintf(name, "/proc/%d/cmdline",pid);
		FILE* f = fopen(name,"r");
		if(f){
			size_t size;
			size = fread(name, sizeof(char), 1024, f);
			if(size>0){
				if('\n'==name[size-1])
					name[size-1]='\0';
			}
			fclose(f);
		}
	}
	return name;
}

int bgf,n,fgg;
int ctrZ_flag;
int jobpid[1000];
char joblist[1000][1000],jobflag[1000];
volatile sig_atomic_t keep_going = 1;
void handler_z(int sig)
{
	int pid = getpid();
	const char* name;
	keep_going = 0;
	signal (sig, handler_z);
	//	name = get_process_name_by_pid(pid);
	//	printf("NAME: %s\n",name);
	//	strcpy(joblist[n],name);
	//	joblist[n][strlen(name)]='\0';
	//	jobpid[n] = pid;
	//	jobflag[n]=1;
	//	n++;
	kill(pid,SIGTSTP);
	return;
}
void handler_c()
{
	int pid=getpid();
	kill(pid,SIGINT);
	return;
}
void exit_process()
{
	int info,pid;
	while(1)
	{
		pid = waitpid(-1,&info,WNOHANG);
		if(pid==0 || pid==-1) return;     //pid 0 means no child process changed its state, pid -1 means waitpid failure
		else if(fgg==0) return;
		else
		{
			printf("Process exited with exit status %d\n",info);
			//jobflag[n]=0;
			n--;
		}
	}
}
void trim(char * str)
{
	int index, i;

	/*
	 * Trim leading white spaces
	 */
	index = 0;
	while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
	{
		index++;
	}

	/* Shift all trailing characters to its left */
	i = 0;
	while(str[i + index] != '\0')
	{
		str[i] = str[i + index];
		i++;
	}
	str[i] = '\0'; // Terminate string with NULL
	/*
	 * Trim trailing white spaces
	 */
	i = 0;
	index = -1;
	while(str[i] != '\0')
	{
		if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			index = i;
		}

		i++;
	}
	/* Mark the next character to last non white space character as NULL */
	str[index + 1] = '\0';
}


char untinput[1024],tmp1[100],cmd_input0[1024],cmd_input1[1024],cmd_input2[1024],cmd_input3[1024],cmd_input4[1024],cmd_input5[1024],cmd_input6[1024];
char cmd_input7[1024],cmd_input8[1024],cmd_input9[1024],cmd_input10[1024],cmd_input11[1024],cmd_input12[1024],cmd_input13[1024];
char cmd_input14[1024],inputf[100],r_inputf[100],r_outputf[100],wrt[1024],tmp[100],outputf[100],actcom[1000];
char tmp2[100],*process_name[100];

int main()
{
	char path_shell[1024],system_name[1024],a[10],gs[1000],c[10],buffer[1024],wrt1[1024],cwp[1000],test[1000];
	const char s1[2] = "\n";
	const char s3[2] = ".";
	const char s4[2] = "..";
	n=0;
	bgf=1;
	//char* pd;
  welcomeScreen();
	char tpath[1024],savedir[1000];
	char* ftoken;
	char* fir;
	char* fir1;
	char* fvar;
	char* fvar1;
	pid_t pid_req;
	pid_t pid;
	char* ftoken1;
	const char s[2] = " ";
	const char s2[2] = "/";
	//char tilda[2] = {'~', '\0'};
	//char tilda1[2] = {'~', '\0'};

	struct passwd  *pwd1;
	struct group   *grp;
	struct tm      *tm;
	char  datestring[256];

	int flag=1,i,k,flag3 = 0;

	for(i=0;i<200;i++)
	{
		jobflag[i]=0;
	}


	if(getcwd(path_shell, 1023) == NULL)
	{
		printf(ANSI_COLOR_RED "Cannot get your present working directory!" ANSI_COLOR_RESET "\n");
	}

	//path_shell[1023]='\0';
	//pd[1023]='\0';
	//int count = 0;
	//if (signal(SIGTSTP, sig_handlerZ))			//To check if any command like "firefox" had a ctr+Z so that it terminates
	//{;}

	//	while ( sigsetjmp( ctrlz_buf, 1 ) != 0 );		//To catch prompt after child is killed
	while(1)
	{

		if (signal(SIGUSR1, sig_handler) == SIG_ERR)
			sleep(0);
		if (signal(SIGKILL, sig_handler) == SIG_ERR)
			sleep(0);
		if (signal(SIGSTOP, sig_handler) == SIG_ERR)
			sleep(0);
		if (signal(SIGINT, sig_handler) == SIG_ERR){
			//printf("SIGINT not detected");
				sleep(0);
  }
		if (signal(SIGCHLD, sig_handler) == SIG_ERR)
		{
			printf("\n");
			sleep(0);
		}

		signal(SIGTSTP,sig_handler);

		while ( sigsetjmp( ctrlz_buf, 1 ) != 0 );		//To catch prompt after child is killed
		char aa[2] = {'S', '\0'};
		char tilda[2] = {'~', '\0'};
		char j[5] = {'j', 'o', 'b', 's', '\0'};
		char kj[5] = {'k','j', 'o', 'b','\0'};
		char ok[9] = {'o','v', 'e', 'r', 'k', 'i', 'l', 'l','\0'};
		char sf[3] = {'f', 'g', '\0'};
		char pd[1024];
		char tilda1[2] = {'~', '\0'};
		char bg[3] = {'b','g','\0'};
		char *uname = malloc( 10*sizeof(char) );
		char cmd_input[1024];
		char *tilda_char = "~";
		inputf[0]='\0';
		outputf[0]='\0';
		r_inputf[0] = '\0';
		r_outputf[0] = '\0';
		int flag = 0,flag1 = 0,flag2 = 0;
		//Specification:1
		uname = getlogin();
		char *user_name = getenv("LOGNAME");
		if( user_name  == NULL){
			return EXIT_FAILURE;
		}

		gethostname(system_name, 20);
		getcwd(cwp, 1023);

		int a = 0 ;
		k=0;

		for(i=strlen(path_shell);i<strlen(cwp);i++)
		{
			wrt1[k]=cwp[i];
			k++;
		}

		wrt1[k]='\0';
		strcat(tilda,wrt1);

		printf(ANSI_COLOR_YELLOW "%s@"ANSI_COLOR_RESET ,user_name);
		printf(ANSI_COLOR_GREEN "%s:"ANSI_COLOR_RESET,system_name);
		printf(ANSI_COLOR_CYAN "%s$" ANSI_COLOR_RESET, tilda);

		scanf(" %[^\n]s",cmd_input);   //takes the input till new line comes :P
		//trim_whitespaces(cmd_input);

		//printf("1: %s",cmd_input);
		strcpy(cmd_input1,cmd_input);
		if(strcmp(cmd_input,"quit")==0 || strcmp(cmd_input,"exit") == 0)
		{
			break;
		}
		if (fgets(buffer, 10, stdin) == NULL)
		{
			printf("\n");
			continue;
		}

                pid_t pID = waitpid(pid_req,NULL,WNOHANG);

		while(pID > 0)
		{
			 printf("Background-Process : %d has been exited\n",pID);
			 pID = 0;
		}

    strcpy(cmd_input0,cmd_input);
    strcpy(cmd_input1,cmd_input);
		strcpy(cmd_input2,cmd_input);
		strcpy(cmd_input3,cmd_input);
		strcpy(cmd_input4,cmd_input);
		strcpy(cmd_input5,cmd_input);
		strcpy(cmd_input6,cmd_input);
		strcpy(cmd_input7,cmd_input);

		strcpy(cmd_input8,cmd_input);
		strcpy(cmd_input9,cmd_input);
		strcpy(cmd_input10,cmd_input);
		strcpy(cmd_input11,cmd_input);
		strcpy(cmd_input12,cmd_input);
		strcpy(cmd_input13,cmd_input);
    strcpy(cmd_input14,cmd_input);

		fir = strtok(cmd_input10,s);

		//printf("%s\n",fir);
		char* to[100];
		char* to1[100];
		char* setv[100];
		char* setv1[100];
		int status;
		//strcpy(to[0],fir);
		to[0] = fir;

		to1[0] = fir1;
		//printf("first:%s\n",to1[0]);
		int nom = 0,jn,jnarr;
		int nom1=0,one,two;
		int nom2=0,nom3=0;

		while(to[nom] != NULL)
		{
			nom++;
			to[nom] = strtok(NULL,s);
		}

		fvar = strtok(cmd_input13,s);
    setv[nom2] = fvar;
      //  printf("setvar : %s\n",fvar);
		while(setv[nom2] != NULL)
		{
			nom2++;
			setv[nom2] = strtok(NULL,s);
      //  printf("args : %s\n",setv[nom2]);
		}
		fvar1 = strtok(cmd_input14,s);

		setv1[nom3] = fvar1;
		while(setv1[nom3] != NULL)
		{
			nom3++;
			setv1[nom3] = strtok(NULL,s);
		}

		if(strcmp(fvar,"setenv")==0)
			setenv_calling(setv);
		if(strcmp(fvar1,"unsetenv")==0)
			unsetenv_calling(setv1);


		//printf("NO1:%s\n",to[1]);
		//printf("NO2:%s\n",to[2]);
		//printf("NOTOKENS:%d\n",nom);
		//printf("FG SHOULD BE PRINTED: %s\n",to[0]);
		//printf("2nd..: %s\n",to[1]);
		//printf("NUMBER:%d\n",nom);

		if(nom>1)
		{
			jn=atoi(to[1]);
			jnarr=jn-1;
			//	printf("JOBNUM: %d\n",jnarr);
		}

		if(strcmp(to[0],sf)==0 && nom<=1) printf("Wrong number of arguments for fg command :(\n");

		if(strcmp(to[0],sf)==0 && nom>1)
		{
			if(jnarr<=n-1){
				printf("SIGNAL SENT\n");
				kill(jobpid[jnarr],SIGCONT);
				jobflag[jnarr]=0;

				pid_t pid=waitpid(jobpid[jnarr],&status,WUNTRACED);}
			//above -- wuntraced requests status info about both stopped as well as terminated processes
		}

		//	printf("KILLNO: %d\n",nom);
		//	int t1;
		//	t1 = atoi(to[1]);

		if(strcmp(to[0],bg)==0 && nom>1)
		{
			if(jnarr<=n-1){
				kill(jobpid[jnarr],SIGCONT);}
		}

		int nkflag = 1;

		if(strcmp(to[0],kj)==0 && nom!=3){
			printf("Wrong number of arguments for kjob command :(\n");
			nkflag=0;
		}
		//	printf("JN:%d\n",jn);
		//	printf("nminus1:%d\n",n-1);
		if(strcmp(to[0],kj)==0 && nom==3 && jn>n){
			printf("This job number doesn't exist :(\n");
			nkflag = 0;
		}

		if(strcmp(to[0],kj)==0 && nom==3 && nkflag==1)
		{
			//printf("KILLLOOP\n");
			//	one=atoi(to[1]);
			two=atoi(to[2]);
			int r = kill(jobpid[jnarr],two);
			jobflag[jnarr]=0;
			//fgg=0;
			if(r!=0)
			printf("Signal not valid... (could not be sent)\n");
			continue;

		}
		int t,g;

		if(strcmp(cmd_input12,ok)==0)
		{
			//		printf("NUM OF JOBS: %d\n",n);
			if(n>0)
			{
				for(i=0; i<n; i++)
				{
					printf("[%d] %s [%d] killed \n", i+1, joblist[i], jobpid[i]);
					kill(jobpid[i], 9);
					//for(g=i;g<n-1;g++)
					//{
					//	strcpy(joblist[g],joblist[g+1]);
					//	jobpid[g]=jobpid[g+1];
					//}
					//n=0;
				}
				n=0;
				for(i=0;i<n;i++)
					jobflag[i]=0;
			}
			else printf("There are no jobs to be killed! :)\n");
		}
		if (strcmp(cmd_input9, j)==0)
		{
			char buffer2[300];
		  char st;
		  FILE* fd8;
			//printf("NO OF JOBS:%d\n",n);
			if(n==0){
				printf("No jobs are currently running :(\n");}
			else
			{
				//printf("FIRSTJOB:%s\n",joblist[0]);
				//printf("SECONDJOB:%s\n",joblist[1]);
				//printf("N:%d\n",n);
				for(i=0; i<=n-1; i++)
				{
				//	printf("LIST!!!\n");
					if(jobflag[i]==1)
					{
						//printf("LIST!!!\n");
						printf("[%d]  %s  %d \n",i+1,joblist[i],jobpid[i]);
			     	/*printf("[%d]\t",i+1);
						sprintf(buffer2, "/proc/%d/stat",jobpid[i]);
						fd8=fopen(buffer2, "r");
						fscanf(fd8, "%*d %*s %c",&st);
						if(st == 'S') printf("Running\t");
						else printf("Stopped\t");
						printf("%d\n",jobpid[i]);*/
				  }
			  }
		 }
		 continue;
		}

		for(i=0; i<strlen(cmd_input);i++)
		{
			if(cmd_input[i]=='<')
			{
				while(cmd_input[i+1] == ' ') i++;
				t = i+1;
				sscanf(cmd_input+t, "%[^> \n]", inputf);
				break;
			}
		}
		for(i=0; i<strlen(cmd_input);i++)
		{
			if(cmd_input[i]=='>')
			{
				while(cmd_input[i+1] == ' ') i++;
				t = i+1;
				sscanf(cmd_input+t, "%[^< \n]", outputf);
				break;
			}
		}
		//printf("INPUT: %s",inputf);
		//printf("OUTPUT: %s",outputf);

		sscanf(cmd_input,"\n%[^<>]", actcom);

		trim(actcom);
		//printf("ACTCOMMAND:%saaa\n",actcom);
		//printf("FLAG2:%d\n", flag2);

    int lsflag = 0;

		char arg[1024],lasttok_arg[1024],redirect_arg[1024];
		const char pipe_del[2] = "|";
		//int fpipes[2] = {0};
		int m = 0;

		int inp_len = strlen(cmd_input0);

		char *toks[100];
		char *ftok = strtok(cmd_input0,pipe_del);
		toks[0] = ftok;

		//printf("process :0 - %s\n",toks[0]);

		trim(toks[0]);

		while(toks[m] != NULL)
		{
			m++;
			toks[m] = strtok(NULL,pipe_del);
		}

		//trimming the whitespaces the commands

		int  pt = m-1;
		int num_toks  = pt;

		//printf("number of pipes :%d\n",num_toks);

		while(pt>0)
		{
			trim(toks[m-pt]);
			pt--;
		}

		int p2 = 0;

		char *lastok[100];
		strcpy(lasttok_arg,toks[num_toks]);

		char *lasttok = strtok(lasttok_arg,s);
		lastok[0] = lasttok;

		while(lastok[p2] != NULL)
		{
			p2++;
			lastok[p2] = strtok(NULL,s);
		}

		if(strcmp(actcom,"pwd") == 0)
		{
			//printf("ACTUAL COMMAND CHECK\n");
			pwd_calling(path_shell,actcom,outputf);
			flag1 = 1;
			continue;
		}

		else if( echo_calling(cmd_input2) == 1)
		{
			flag1 = 1;
			continue;
		}
		//	printf("FLAG2:%d\n", flag2);
		else
		{    //printf("inp0 : %s\n",cmd_input3);
			//printf("entered\n");
			flag2 = cd_calling(path_shell,cmd_input3);
			//printf("flag2 :%d",flag2);
			//flag2=1;
		}

		if(num_toks == 0 && ls_calling(cmd_input4) == 1)
		{
			flag1 = 1;
      lsflag = 1;
			continue;
		}

		pinfo_calling(cmd_input6);
		//printf("FLAG2:%d\n", flag2);

		if(strcmp(cmd_input, "\n")==0 && flag2 != 1)
		{
			flag1 = 1;
			continue;
		}
		//printf("FLAG2:%d\n", flag2);

		if(strcmp(cmd_input, "exit") == 0 || strcmp(cmd_input, "quit") == 0)
		{
			break;
		}

		else if (flag2 != 1 && lsflag == 0)
		{
			char *tokens[100];
			int pt =0, procid, procid1;
			//printf("hello");
			//printf("%s",cmd_input7);
			//ftoken1 = strtok(cmd_input7,s);
			//printf("ACTCOMMAND : %s\n",actcom);
			ftoken1 = strtok(actcom,s);
			//printf("hi5");
			tokens[0] = ftoken1;
			//printf("initial command: %s\n",tokens[0]);
			//tokens[0] = strtok(cmd_input,s);
			//char *stoken = strtok(NULL,s);
			//printf("hello1");
			while(tokens[pt] != NULL)
			{
				pt++;
				tokens[pt] = strtok(NULL,s);

			}
			int cr = pt;
			int fin,fout;
			// printf("%d\n",cr);

			//background process

			if(cr == 1) cr = 1;
			//printf("token1: %s\n",tokens[cr-1]);
			//printf("token2: %s\n",tokens[cr]);
			//		printf("TOCKE should be a : %s\n",tokens[cr-1]);
			if(strcmp(tokens[cr-1],"&") == 0 || tokens[cr-1][strlen(tokens[cr-1])-1]=='&')
			{
				//	printf("ampercent stated!!!\n");
				//	signal(SIGCHLD, exit_process);
				//printf("%s@%s:%s$ ",user_name, system_name , tilda);
				procid = fork();
				//printf("TOKENS: \n");
				//for(i=0;i<cr;i++) printf("%s\n",tokens[i]);
				signal(SIGCHLD, exit_process);
				if(procid != 0)
				{
					strcpy(joblist[n],actcom);
					joblist[n][strlen(actcom)]='\0';
				//	printf("%s should be printed...\n",joblist[n]);
					jobpid[n]=procid;
					jobflag[n] = 1;
					n = n+1;
					//printf("FIRSTJOB:%s\n",joblist[0]);
					//printf("SECONDJOB:%s\n",joblist[1]);
				}
				if(procid == 0)   //child process
				{
					char c;
					pid_req = getpid();
					//printf("process id:%d\n",pid_req)
					//strcpy(process_name,tmp2);

					execvp(tokens[0],tokens);
					_exit(1);
					//	printf("command has been terminated,error\n");
				}
			}

			//foreground process
			else
			{
				int status1;
				int procid1 = fork();
				pid_t cpid;
        int fpipes[2*num_toks+1];
				if(procid1 == 0)
				{
					//printf("BGFLAGCHANGED!!!\n");
					//bgf=0;
					signal(SIGTSTP,handler_z);
					/*while (keep_going)
					  {
					  if(keep_going==0)
					  {
					  jobpid[n] = procid1;
					  strcpy(joblist[n],actcom);
					  joblist[n][strlen(actcom)]='\0';
					  jobpid[n]=procid;
					  jobflag[n]=1;
					  n = n+1;
					  }
					  }*/
   				//printf("Foreground process %d started\n",getpid());
					if(num_toks > 0)
					{
             int in = 0;
					   int out = 1;
					   int status = 0;
					   //printf("number of tokens :%d\n",num_toks);

					   for(i=0;i<num_toks;i++)
	           {
					     if(pipe(fpipes+i*2) != 0)
					     {
					       perror("error occured while piping\n");
					       exit(EXIT_FAILURE);
					     }
					   }

					   int cp = 0;
					   for(i=0 ; i < num_toks+1 ; i++)
					   {
	      					 int d,pla;
									 int p1=0,fl = 0;
				      		 //printf("pipes:  %d\n",num_toks);
				           strcpy(arg,toks[i]);
						       strcpy(redirect_arg,toks[i]);
						       //pinputf[0] = '\0';
						       //poutputf[0] = '\0';
				           char *tokargs[100];
						       char *rtokens[100];
						       char *ft1;
				           char *ftok1 = strtok(arg,s);
						       int fin1, fout1;
				           tokargs[0] = ftok1;
									 char r_actcom[1000];
						       //if(strcmp(ftok1,"grep") == 0)
						       //{
						       //  tokargs[1] = "grep";
						       //  p1 = 1;
						       //}
						       //printf("command: %s\t",tokargs[0]);

						       while(tokargs[p1] != NULL)
                   {
				                  p1++;
				                  tokargs[p1] = strtok(NULL,s);
						              //printf("num: %d args: %s\t",p1,tokargs[p1]);
				           }
                   pid_t pid1;
      						 pid1 = fork();
                   //printf("before the child process : %s\n",tokargs[0]);
			       			 //printf("value of cp: %d\n",cp);

 						       if(pid1 == -1)
						       {
						         perror("error while forking\n");
						         exit(EXIT_FAILURE);
						       }

						       else if(pid1 == 0)
						       {
						        //printf("entered child process\n");
						        if(cp != 2*num_toks)
						        {
						           //printf("\n cp :%d\n",cp);
						           if(dup2(fpipes[cp+1],1) < 0)
						           {
						               perror("error while dup2 - 0\n");
						               exit(EXIT_FAILURE);
						           }
						        }

						        if(cp != 0)
						        {
						            //printf("entered2\n");
						            if(dup2(fpipes[cp-2],0) < 0)
						            {
						                perror("error while dup2 - 1\n");
						                exit(EXIT_FAILURE);
						            }
						        }

						        for(d = 0; d < 2*num_toks; d++)
						        {
						           close(fpipes[d]);
						        }

						        //printf("\ncom :%s\n",tokargs[0]);

						        if(strcmp(tokargs[0],"grep") == 0)
						        {
						           //printf("grep command entered\n");
						           if(execvp("grep",tokargs)< 0)
						           {
						                perror("error while execvp\n");
						                return -1;
						           }
						        }

							      else if(strcmp(tokargs[0],"ls") == 0)
						        {
						           if(execv("/bin/ls",tokargs)< 0)
						           {
						               perror("error while execvp");
						               return -1;
						           }
						        }

							      else
						        {
						           if( execvp(tokargs[0],tokargs) < 0)
						           {
						               perror("error while exec command\n");
						               exit(EXIT_FAILURE);
						           }
    						    }
									 }
						 			 cp=cp+2;
						 //}
						 //printf("value of cp:%d\n",cp);

					   }

					   for(i=0;i< 2*num_toks;i++)
					   {
					     close(fpipes[i]);
					   }

					   for(i=0;i<num_toks + 1;i++)
					   {
					     wait(&status1);
					   }
          }

		     else
         {

					if(inputf[0]!='\0')
					{
						if(access(inputf,F_OK)!=0)
						{
							printf("File that you want to access (%s) doesn't exist.......!!!\n",inputf);
							continue;
						}
						else if(access(inputf,R_OK)!=0)
						{
							printf("You dont have permission to access this file (%s).....!!! \n",inputf);
							continue;
						}
						else
						{
							fin=open(inputf,O_RDONLY,0600);			//opening file in RDONLY with permissions
							if(fin<0)
								printf("1 File error\n");
							else if(dup2(fin,0) < 0)
								printf("2 File error\n");
							close(fin);
						}

					}
					if(outputf[0]!='\0')
					{

						if(access(outputf,F_OK)==0 && access(outputf,W_OK)!=0)		//Permission to open in Write mode
						{
							printf("You dont have permission to access this file......(%s)\n",outputf);
							continue;
						}
						else
						{
							if(access(outputf,F_OK))	creat(outputf,0600);		//write permissions only for user
							fout=open(outputf,O_WRONLY,0600);
							if(fout<0)
								printf("1 File error\n");
							if(dup2(fout,1)<0)
								printf("2 File error\n");
							close(fout);
						}
					}

          signal(SIGINT,handler_c);
					//printf("Foreground process %d started\n",getpid());
					execvp(ftoken1,tokens);
        }

				exit(1);
				//printf("Foreground process exited\n");
				}

				else
				{
					//cpid = wait(NULL);
					int s;
					signal(SIGTSTP, SIG_IGN);
					signal(SIGINT,SIG_IGN);
					waitpid(procid1,&s,WUNTRACED);
					/*	if(WSTOPSIG(s)==2) //child stopped by sigint (Ctrl-C)
						{
						printf("CRECOGNIZED!\n");
						for(i=0;i<n;i++) {
						jobflag[i]=0;
						n=0;}}*/

					if(WIFSTOPPED(s))
					{
						if(WSTOPSIG(s) == 18 || WSTOPSIG(s) == 20 || WSTOPSIG(s) == 24)  //stopped by SIGTSTP
						{
							printf("ZRECOGNIZED!\n");
							jobpid[n] = procid1;
							strcpy(joblist[n],actcom);
							joblist[n][strlen(actcom)]='\0';
							jobpid[n]=procid;
							jobflag[n]=1;
							n = n+1;
						}
						//	printf("Child process stopped by a signal\n");
						//	jobpid[n] = procid1;
						//	strcpy(joblist[n],actcom);
						//	joblist[n][strlen(actcom)]='\0';
						//	printf("%s should be printed...\n",joblist[n]);

						//	jobpid[n]=procid;
						//	jobflag[n]=1;
						//	n = n+1;

					}

					//printf("Process- %d has been exited\n",cpid);
				}
			}
			cr = 0;

		}


		//if(flag1 == 0)
		//{
		//     printf("Command entered is not supported!!\n");
		//     continue;
		//}
		//printf("BGF END: %d\n",bgf);
	}
	return 0;
}
