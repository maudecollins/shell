#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//determines whether the command is built in or not
int is_built_in(char *cmd)
{
	if(strcmp("exit", cmd) == 0 || strcmp(cmd, "cd") == 0){
		return 1;
	} else{
		return 0;
	}
}
//executes the built in command
void do_built_in(char *cmd, const char *path)
{
	if(strcmp(cmd, "exit") == 0) {
		exit(0);
	}
	if(strcmp(cmd, "cd") == 0) {
		chdir(path);
	}
	
}
//reads the command
char *read_command(){
	int bufsize = 50; //will need to realloc if input is bigger than 10
	char *buffer = malloc(sizeof(char) * bufsize);
	int pos = 0;
	while(1){
		char c = getchar();
		if(c != '\n'){
			buffer[pos++] = c;
			//realloc if bufsize is too small
			if(pos >= bufsize) {
				bufsize += bufsize;
				buffer = realloc(buffer, bufsize);
			}
		} else {
			buffer[pos] = '\0'; //null byte
			return buffer;
		}
	}
}
int main(int argc, char *argv[]){
	
	while(1){
		printf("maudecollins@machine$ ");
		
		//READING
		char *buffer = read_command();
		//END READING
						
		//PARSING
		int paramsize = 50;
		int pos = 0;
		char **params = malloc(paramsize * sizeof(char*));
		//parse command
		//cmd = parsed command
		char *tmp = strtok(buffer, " ");
		char *cmd = tmp; 
		//parse parameters
		//params = parsed parameters
		while(tmp != NULL) {
			params[pos] = tmp;
			pos ++;
			if(pos >= paramsize) {
				paramsize += paramsize;
				params = realloc(params, paramsize);
			}
			tmp = strtok(NULL, " ");
		}
		//END PARSING
		//check if cmd is built-in --> exit or cd
		int status;
		if(is_built_in(cmd) == 1){

			do_built_in(cmd, params[0]);
		}

		//EXECUTION
		else{
			if(fork() != 0){
				pid_t child = waitpid(-1, &status, 0);
			} else{
				execvp(cmd, params);
				printf("Unknown command \n");
			}
		}
		//END EXECUTION
			
	}
}


