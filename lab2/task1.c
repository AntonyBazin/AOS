#include <stdio.h>
#include <stdlib.h>


char* read_env(char*, char*);

int main(){
	char name[] = "my_name";
	char value[] = "my_value";
	char new_value[] = "new_value";
	char* ptr;
	if(setenv(name, value, 1)){
		perror("Error setting env variable");
	}
	read_env(name, ptr);
	if(setenv(name, new_value, 1)){
		perror("Error changing env variable");
	}
	read_env(name, ptr);
	if(setenv(name, value, 0)){
		perror("Error when not changing env variable");
	}
	read_env(name, ptr);
	exit(0);
}


char* read_env(char* name, char *ptr) {
	if (!(ptr = getenv(name))) {
		perror("Error reading env variable");
		exit(1);
	}
	printf("%s\n", ptr);
	return ptr;
}
