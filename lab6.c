#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include <dirent.h>

typedef struct dirent Dirent;

// match function
int match(char *s1, char *s2){
	int diff = strlen(s1) - strlen(s2);
	if(strlen(s1) > strlen(s2)) return (strcmp(&s1[diff],s2) == 0);
	else return (0);
}


int main(int argc, char *argv[]){
	Dirent *dp;
	DIR *dir_fd;
	while(--argc > 0){
		if(!(dir_fd = opendir(argv[1]))){ //doesn't exist
			//open dir
			if(mkdir(argv[1],S_IRWXU|S_IRWXG|S_IRWXO) == -1) 
				perror("opendir");
			continue;
		}
		for(int i = 0; i < 2; i++){
			int cnt = 0;
			for(; dp = readdir(dir_fd);){
				if(i) { 
					//if match result -> print name, ino
					if(match(dp->d_name, argv[2]) == 1){
						printf("filename is %s\n",
						 dp->d_name);
						printf("file i-node is
						 %ld\n",
						dp->d_ino);
						return 0;
						
					}
				}
				if(strcmp(dp->d_name, ".") && 
				strcmp(dp->d_name,"..")){ cnt++;}
			}
			if(!cnt){
					rmdir(argv[1]); break;
				}
				rewinddir(dir_fd);		
		}
		closedir(dir_fd);
		
	}
	return 0;
}
