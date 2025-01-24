#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
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

int main(int argc, char* argv[]){
    int n=11;

    // for(int i=0;i<11;i++) args[i]=NULL;
    // printest(args);
    // for(int i=0;i<11;i++){
    //     if(args[i]){
    //         printf("%s\n",args[i]);
    //         free(args[i]);
    //     }
    // }
    char command[50];
    int z = 0;
    while(z<50){

        char* args[n];
        for(int i=0;i<n;i++) args[i]=NULL;
        
        // fgets(command,50,stdin);
        printf(">> ");
        scanf("%[^\n]s", command);
        getchar();
        // printf("%s",command);
        if(strcmp(command,"exit")==0) break;
        splitInput(command,args,0);


        // printf("************************************************\n");
        pid_t Id = fork();
        if(Id==0){
            // printf("child process : %d\n",Id);
            // char* newargv[] = {command,"one","two","three"};
            // printf("%s commnd\n",command)
            if(execvp(args[0],args)==-1) printf("failed to execute the given command\n");
            // exit(0);
            //execute the code and break
            break;
        }
        else if(Id<0){
            printf("command can't be executed\n");
        }
        else{
            // printf("waiting for the child process\n");
            int x = wait(NULL);
            // printf("Parent Process :%d\n",Id);
            // printf("child process terminated\n");
            //wait for the child process
            // continue;
        }

        
        printf("**********************************************\n");


        for(int i=0;i<n;i++){
            if(args[i]!=NULL) {
                // printf("in main : %s\n",args[i]);
                free(args[i]);
            }
        }
        strcpy(command,"");
        z++;
    }


    // printf("*********test program**********\n");
    // printf("printing the args passed\n");
    // for(int i=0;i<argc;i++){
    //     printf("%s\n",argv[i]);
    // }
    // printf("********ending test program*********\n");

    // char s[] = "    dlfdf sdf sldfjsdf lsdkfjlsdf lsdjflsdj";
    // char arglist[10][20];

    return 0;

}
