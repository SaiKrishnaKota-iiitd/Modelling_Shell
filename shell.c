#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int main(){
    char command[50];
    bool leave = false;
    do {
        strcpy(command,"");
        // scanf("%s",command);
        // int result = system(command);
        //the above code is the simplest way to execute shell commands using the system() function in C
        
        printf(">>");
        gets(command);
    }while(strcmp(command,"exit")!=0);


    return 0;
}