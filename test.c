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

void printest(char** arglist){
    for(int i=0;i<10;i++){
        arglist[i] = (char*)malloc(sizeof(char)*10);
        strcpy(arglist[i],"HI");
    }
    // arglist[10]=NULL;
    return;
}

int checkRedirection(char* arglist[],int *pos,int maxarg){
    int i=0;
    int fileID = -1;
    int mode = 0;

    while(arglist[i]!=NULL){
        // printf("%d %s\n",i,arglist[i]);
        if(strcmp("<",arglist[i])==0){
            printf(" case 1: %s", arglist[i]);
            *pos = i;
            mode =  1;
        }
        else if(strcmp("<<", arglist[i])==0){
            // printf(" case 2: %s", arglist[i]);
            *pos = i;
            mode =  2;
        }
        else if(strcmp(">", arglist[i])==0){
            // printf(" case 3: %s", arglist[i]);
            *pos = i;
            mode =  3;
        }
        else if(strcmp(">>", arglist[i])==0){
            // printf(" case 4: %s", arglist[i]);
            *pos = i;
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

int main(int argc, char* argv[]){
    int argcount=55;
    char filepath[100];
    int inputlimit = 100;

    char command[inputlimit];
    int z = 0;

    char* args[argcount];
    for(int i=0;i<argcount;i++) args[i]=NULL;

    while(z<50){
        
        // fgets(command,50,stdin);
        printf(">> ");
        scanf("%[^\n]s", command);
        getchar();
        // printf("%s",command);
        if(strcmp(command,"exit")==0) break;
        splitInput(command,args,0);


        //creating child process to handle command
        pid_t Id = fork();
        if(Id==0){
            int pos = -1;
            int redirection = checkRedirection(args,&pos,argcount);
            // printf("child process : %d\n",Id);
            // char* newargv[] = {command,"one","two","three"};
            // printf("%s commnd\n",command)
            if(execvp(args[0],args)==-1) printf("failed to execute the given command\n");
            break;
            //ends the child process
        }
        else if(Id<0){
            printf("command can't be executed\n");
        }
        else{
            wait(Id);
            // wait for the child process to execute the command
        }

        
        printf("**********************************************\n");


        for(int i=0;i<argcount;i++){
            if(args[i]!=NULL) {
                free(args[i]);
                args[i]=NULL;
                //free the dynamic memory
            }
        }
        strcpy(command,"");
        z++;
    }
    if(z>=50) printf(" limit reached \n Exiting......");

    // printf("*********test program**********\n");
    // printf("printing the args passed\n");
    // for(int i=0;i<argc;i++){
    //     printf("%s\n",argv[i]);
    // }
    // printf("********ending test program*********\n");

    return 0;

}
