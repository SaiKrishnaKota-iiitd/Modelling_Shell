#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void splitInput(char* str,char** arglist,int p){
    int x=0;
    int begin = -1;
    int n=0;
    char newstr[100];
    int i;
    
    while(1){
        if(str[x]==' ' || str[x]=='\0'){
            if(begin!=-1){
                strcpy(newstr,"");
                if(p) printf("before allocation\n");
                arglist[n] = (char*)malloc(sizeof(char)*100);
                if(p) printf("after allocation\n");
                
                i=0;
                for(i;i<x-begin;i++){
                    newstr[i] = str[i+begin];
                }
                newstr[i]='\0';
                strcpy(arglist[n],newstr);
                
                if(p) printf("%s\n",newstr);
                if(p) printf("%d\n",x);

                n++;
                begin = -1;
                if(str[x]=='\0'){
                    if(p) printf("exiting : %d\n",x);
                    break;
                }
                // printf("found split\n");
                
            }
            if(str[x]=='\0') break;
        }
        else{
            if(begin==-1){
                begin = x;
            }
        }
        x++;
    }
    arglist[n]=(char*)NULL;

}


int checkRedirection(char* arglist[],int maxarg){
    int i=0;
    int fileID = -1;
    int mode = 0;

    while(arglist[i]!=NULL){
        // printf("%d %s\n",i,arglist[i]);
        if(strcmp("<",arglist[i])==0){
            printf(" case 1: %s", arglist[i]);
            mode =  1;
        }
        else if(strcmp("<<", arglist[i])==0){
            // printf(" case 2: %s", arglist[i]);
            mode =  2;
        }
        else if(strcmp(">", arglist[i])==0){
            // printf(" case 3: %s", arglist[i]);
            mode =  3;
        }
        else if(strcmp(">>", arglist[i])==0){
            // printf(" case 4: %s", arglist[i]);
            mode =  4;
        }

        if(mode != 0){
            // printf("%s %d-%d %s",arglist[i],mode,i,arglist[i+1]);
            if(i>(maxarg -2) || arglist[i+1]==NULL){
                printf("enter the required file's path\n");
            };
            // printf("file is : %s\n",arglist[i+1]);
            if(mode == 1) fileID = open(arglist[i+1],O_RDWR | O_CREAT ,0640);
            else if(mode == 2) fileID = open(arglist[i+1],O_RDWR | O_CREAT ,0640);
            else if(mode == 3) fileID = open(arglist[i+1],O_RDWR | O_CREAT | O_TRUNC ,0640);
            else if(mode == 4) fileID = open(arglist[i+1],O_RDWR | O_CREAT | O_APPEND,0640);
            
            if(fileID<0){
                printf("can't access required file %s\n",arglist[i+1]);
                return -1;
            }

            if(mode == 1 || mode ==2 )dup2(fileID,STDIN_FILENO);
            else if(mode == 3 || mode == 4 )dup2(fileID,STDOUT_FILENO);
            arglist[i] = NULL;
            close(fileID);

            if(execvp(arglist[0],arglist)==-1) printf("failed to execute the given command\n");
            exit(0);
            
            // break;
        }
        i++;
    }
    return mode;
}

int handleBuiltin(char* arglist[]){
    int executed = 0;
    char b_path[500];
    char a_path[500];
    if(strcmp("cd",arglist[0])==0){
        if(arglist[1]!=NULL){
            getcwd(b_path,500);
            chdir(arglist[1]);
            getcwd(a_path,500);
            if(strcmp(b_path,a_path)==0) printf("%s : Not a directory\n",arglist[i]);
        }
        executed = 1;
    }

    if(strcmp("help",arglist[0])==0){
            printf("******************* CUSTOM SHELL ***********************\n");
            printf("Most of the shell commands are executables like :\n");
            printf("> ls [options]\n");
            printf("Few commands are defined internally:\n");
            printf("> cd <path>\n> help\n\n");
            printf("Use '>','>>','<','<<' for input output redirection\n");
        executed = 1;
    }
    return executed;
}

int main(int argc, char* argv[]){
    int argcount=55;
    char filepath[500];
    int inputlimit = 100;

    char command[inputlimit];
    int z = 0;

    char* args[argcount];
    for(int i=0;i<argcount;i++) args[i]=NULL;

    printf("************************ WELCOME **********************************\n");
    while(z<50){
        printf("%s",getcwd(filepath,500));
        //user input
        printf(" >> ");
        scanf("%[^\n]s", command);
        getchar();
        if(strcmp(command,"exit")==0) break;

        //parsing the user input
        splitInput(command,args,0);
        
        if(strcmp("cd",args[0])==0 || strcmp("help",args[0])==0 ){
            handleBuiltin(args);
            continue;
        }


        //creating child process to handle command
        pid_t Id = fork();
        if(Id==0){
            //checking if redirection is needed
            int redirection = checkRedirection(args,argcount);
            if(execvp(args[0],args)==-1) {

                printf("failed to execute the given command\n");
            }
            break;
            //ends the child process
        }
        else if(Id<0){
            printf("command can't be executed\n");
        }
        else{

            waitpid(Id,NULL,0);
            
            // wait for the child process to execute the command
        }

        


        for(int i=0;i<argcount;i++){
            if(args[i]!=NULL) {
                free(args[i]);
                args[i]=NULL;
                //free the dynamic memory
            }
        }
        strcpy(command,"");
        z++;
        printf("\n");
    }
    if(z>=50) printf(" limit reached \n Exiting......");

    return 0;

}
