#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void splitInput(char* str,char** arglist){
    int x=0;
    int begin = -1;
    int n=0;
    while(1){
        if(str[x]==' ' || str[x]=='\0'){
            if(begin!=-1){
                char newstr[100];
                int i=0;
                for(i;i<x-begin;i++){
                    newstr[i] = str[i+begin];
                }
                arglist[n] = (char*)malloc(sizeof(char)*100);
                newstr[i]='\0';
                strcpy(arglist[n],newstr);
                printf("%s\n",newstr);
                begin = -1;
                if(str[x]=='\0') break;
            }
        }
        else{
            if(begin==-1){
                begin = x;
            }
        }
        x++;
    }

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
    char* args[11];
    for(int i=0;i<11;i++) args[i]=NULL;
    printest(args);
    for(int i=0;i<11;i++){
        if(args[i]){
            printf("%s\n",args[i]);
            free(args[i]);
        }
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
