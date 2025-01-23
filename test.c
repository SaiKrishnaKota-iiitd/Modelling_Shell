#include<stdio.h>
#include<string.h>
int main(int argc, char* argv[]){
    printf("*********test program**********\n");
    printf("printing the args passed\n");
    for(int i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    printf("********ending test program*********\n");

    char s[] = "sdlfdf sdf sldfjsdf lsdkfjlsdf lsdjflsdj    ";
    int x=0;
    while(s[x]!='\0'){
        if(s[x]==' '){ 
            x++;
            continue;
        }
        int y=x;
        while(s[y]!=' ' || s[y]!='\0'){
            y++;
        }
        char newstr[20];
        strncpy(newstr,s+x,y-x);
        newstr[y-x]='\0';
        x=y;
        printf("%s",newstr);
        // printf("%c %d\n",s[x],s[x]);
        // x++;
    }
    return 0;

}