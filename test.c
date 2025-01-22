#include<stdio.h>
int main(int argc, char* argv[]){
    printf("*********test program**********\n");
    printf("printing the args passed\n");
    for(int i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    printf("********ending test program*********\n");
    return 0;
}