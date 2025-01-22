#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
// #include<sys/types.h>
#include<sys/wait.h>
int creatP(){
    pid_t newPid = fork();
    return newPid;
}

void executeCommand(char command[]){
    return ;
}

int main(){
    char command[50];
    bool leave = false;
    do {
        strcpy(command,"");
        // scanf("%s",command);
        // int result = system(command);
        //System() function provides the simplest way to execute shell commands in C
        
        printf(">>");
        scanf("%s",command);
        // int Id = creatP();
        if(strcmp(command,"exit")==0) continue;
        pid_t Id = fork();
        if(Id==0){
            printf("child process : %d\n",Id);
            char* newargv[] = {command,"one","two","three"};
            printf("%s commnd\n",command)
            execv(command,newargv);
            // exit(0);
            //execute the code and break
            break;
        }
        else if(Id<0){
            printf("command can't be executed\n");
        }
        else{
            printf("waiting for the child process\n");
            int x = wait(NULL);
            printf("Parent Process :%d\n",Id);
            printf("child process terminated\n");
            //wait for the child process
            // continue;
        }
    }while(strcmp(command,"exit")!=0);


    return 0;
}