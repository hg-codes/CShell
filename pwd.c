#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    char cwd[FILENAME_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) 
    {
        perror("getcwd() error");
        return 1;
    }
    printf("%s\n",cwd);
    return 0;
}