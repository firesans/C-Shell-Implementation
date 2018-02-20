void setenv_calling(char *setv[])
{
	setenv(setv[1],setv[2],1);
	return;
}

void unsetenv_calling(char *setv[])
{
	unsetenv(setv[1]);
	return;
}
			
	

			
	
	
