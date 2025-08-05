#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include <limits.h>

int main(int argc, char* argv[]){
    char input[1024];
    scanf("%[^\n]%*c",input);
    char *token = strtok(input, " \t ");
    char **echo;
    echo = malloc(1000 * sizeof(char*));
    int itr = 0;
    while(token != NULL){ 
        echo[itr] = malloc((1000)*sizeof(char));
        echo[itr] = token;
        itr++;
        token = strtok(NULL," \t ");
    }

    for(int i=0;i<itr;i++){
        if(i != itr-1)
            printf("%s ",echo[i]);
        else
            printf("%s\n",echo[i]);
    }

    return 0;
}

