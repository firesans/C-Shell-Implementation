Assignment : IMPLEMENTING SHELL IN C
------------------------------------

AIM :  The goal of the project is to create a user defined interactive shell program that can
       create and manage new processes.

Implemented commands:
---------------------
- pwd
- echo
- All variations of cd
- All variations of ls [-al]
- pinfo
- All other commands like emacs, vi and so on. The shell can
  execute them either in the background or in the foreground.
- Implementation of piping and redirection
- setenv 
- quit
- Ctrl+Z and various other background functioning 

Compilation : make 
-----------

Running : ./main
-------

PWD : 
----
Since the directory from which we run the file is considered as home directory, we have to find the path with respect to the new "home" directory. 
The pwd command gives the present working directory with respect to the new "home" directory.

CD:    (All variations)
--
In cd command, the first token is 'cd' itself and second argument can be : '.' , '~' , '..' , '-' , or path can be mentioned. The directory is changed according to the second argument.

ECHO: 
-----
Using "echo" command, it displays the arguments.

LS:   (All variations)
--
'opendir()' is used to opens a directory stream corresponding to the directory name, and returns a pointer to  the  directory  stream.   The
stream is positioned at the first entry in the directory. 'readdir()' is used to get the names of the files. The readdir() function returns a pointer to a dirent  structure  repre‐senting  the next directory entry in the directory stream pointed to by dirp.
To check the permissions, st_mod field of stat is used and then the corresponding permissions are printed.

FOREGROUND AND BACKGROUND PROCESSES: 
------------------------------------
Any command invoked with "&" is treated as background command. This implies that your shell will spawn that process and doesn't wait for the process to exit. It will keep taking user commands. For example, emacs a.txt &. 'execvp' command provide  an  array  of pointers  to  null-terminated  strings that represent the argument list available to the new  program.   The  first  argument point  to the filename associated with the file being executed.

PINFO:
------
When the command "pinfo" is entered, the result output displays the process id and the required process information is displayed along with the execution path.

PIPING AND REDIRECTION :
----------------------
Piping '|' and input-output redirection has been implemented. You can simply give the arguments containing pipe and redirection and can view the output. I have specifically added fucntionality for the "grep" command.

VARIOUS OTHER SPECS:
-------------------
Various other specifications have been added and can be checked from the various spec files .


