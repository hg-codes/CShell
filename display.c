#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include <limits.h>

int main(){
    char systemname[1024];
    int value = gethostname(systemname, sizeof(systemname));

    char *username;
    username=(char *)malloc(50*sizeof(char));
    username=getlogin();
    
    char cwd[FILENAME_MAX];
    getcwd(cwd, sizeof(cwd));
    
    printf("<%s@%s:~>",username,systemname);

    return 0;
}


