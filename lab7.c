#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//excute -> ./a.out PATH    

#define PATH_MAX 1024
int main(int argc, char *argv[]){
	char *var = argv[1];
	char *value, *getc;
	char name[PATH_MAX];
	if(argc == 1 || argc > 3){
		fprintf(stderr,"usage: environ var [value]\n");
		exit(1);
	}
	//current path
	value = getenv(var);
	if(value){
		printf("%s's value is %s\n",argv[1], value);
	}
	else{
		printf("%s is not existed\n",argv[1]);
	}
	//eliminate var
	unsetenv(var);
	value = getenv(argv[1]);
	printf("current delete value : %s\n",value); // null
	
	getc = getcwd(name,PATH_MAX); //get the current directory path
	if(getc == NULL)
		perror("get error");
	else
		printf("lab7.c directory: %s\n", name);
	//set path
	if(setenv(var, name, 1) == -1)
		perror("error setenv");
	value = getenv(var);
	printf("now path: %s\n",value);

	return 0;
}
