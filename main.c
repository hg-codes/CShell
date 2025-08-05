#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include <limits.h>

char* getCurrentDirectory(char* input,char* home_directory, char* current_directory, char* prev_directory);

void remove_initial_substring(char *str, const char *substr) 
{
    char *match = strstr(str, substr); 
    if (match != NULL) 
    {
        memmove(str, "~", 1); // Add tilde (~) to the beginning
        memmove(str + 1, match + strlen(substr), strlen(match + strlen(substr)) + 1); // Remove the substring and shift the remaining characters
    }
}


int main(){

    char hostname[FILENAME_MAX];
    char username[FILENAME_MAX];
    gethostname(hostname, FILENAME_MAX);
    getlogin_r(username, FILENAME_MAX);

    char home_directory[FILENAME_MAX];
    getcwd(home_directory, sizeof(home_directory));

    char *current_directory,*prev_directory ;
    current_directory = (char *)malloc(strlen(home_directory) * 100);
    prev_directory = (char *)malloc(strlen(home_directory) * 100);
    char * current_directory_visible = (char *) malloc(strlen(home_directory) * 100);
    if (current_directory == NULL || prev_directory == NULL) 
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    current_directory_visible[0] = '~';
    current_directory_visible[1] = '\0';
    strcpy(current_directory,home_directory);
    strcpy(prev_directory,home_directory);
    printf("<%s@%s:%s> ",username,hostname,current_directory_visible);

    while(1)
    {
        char input[1024];
        char c;
        int i = 0;
        while((c = getchar()) != '\n')
        {
            input[i++] = c;
        }
        input[i]='\0';
        
        char *token = strtok(input, " \t ");
        char **user_input;
        user_input = malloc(1000 * sizeof(char*));
        int itr = 0;
        while(token != NULL)
        { 
            user_input[itr] = malloc((1000)*sizeof(char));
            user_input[itr] = token;
            token = strtok(NULL," \t ");
            itr++;
        }

        if(i==0 && c=='\n')
        {
            printf("<%s@%s:%s> ",username,hostname,current_directory_visible);
        }
        else if(strcmp(user_input[0],"echo") == 0)
        {
            for(int i=1;i<itr;i++)
            {
                if(i != itr-1) printf("%s ",user_input[i]);
                else printf("%s\n",user_input[i]);
            }
            if(itr == 1) printf("\n");
            strcpy(current_directory_visible,current_directory);
            remove_initial_substring(current_directory_visible,home_directory);
            printf("<%s@%s:%s> ",username,hostname,current_directory_visible);
        }
        else if(strcmp(user_input[0],"pwd") == 0)
        {
            if(itr == 1)
            {
                char cwd[FILENAME_MAX];
                getcwd(cwd, sizeof(cwd));
                printf("%s\n",current_directory);
                strcpy(current_directory_visible,current_directory);
                remove_initial_substring(current_directory_visible,home_directory);
                printf("<%s@%s:%s> ",username,hostname,current_directory_visible);
            }
            else
            {
                printf("bash: cd: too many arguments\n");
                printf("<%s@%s:%s> ",username,hostname,current_directory_visible);   
            }
        }
        else if(strcmp(user_input[0],"cd") == 0)
        {
            if(itr == 1) printf("<%s@%s:~> ",username,hostname);
            else if(itr == 2)
            {
                current_directory = getCurrentDirectory(user_input[1],home_directory,current_directory,prev_directory);
                if(strcmp(current_directory,home_directory) == 0) printf("<%s@%s:~> ",username,hostname);
                else
                {
                    strcpy(current_directory_visible,current_directory);
                    remove_initial_substring(current_directory_visible,home_directory);
                    printf("<%s@%s:%s> ",username,hostname,current_directory_visible);
                }
            }
            else
            {
                printf("bash: cd: too many arguments\n");
                printf("<%s@%s:%s> ",username,hostname,current_directory_visible);
            }
        }
        else
        {
            printf("Command '%s' not found\n",user_input[0]);
            printf("<%s@%s:%s> ",username,hostname,current_directory_visible);
        }
    }
    return 0;
}