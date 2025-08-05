#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    char input[1024];
    scanf("%[^\n]%*c", input);

    char *save1;
    char *token = strtok_r(input, " \t",&save1);
    char *echo[1000];
    int itr = 0;

    while (token != NULL) 
    {
        echo[itr++] = token;
        token = strtok_r(NULL, " \t", &save1);
    }
    for (int i = 0; i < itr; i++) printf("%s%s", echo[i], (i == itr - 1) ? "\n" : " ");

    return 0;
}
