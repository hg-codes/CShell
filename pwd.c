#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include <limits.h>

int main(){
    char cwd[FILENAME_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n",cwd);
    return 0;
}


