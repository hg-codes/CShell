#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include <limits.h>
#include<dirent.h>
#include<errno.h>
#include<malloc.h>
#define MAX_PATH_LENGTH 1024

char **tokenization(char *input){
    char *token = strtok(input, "/");
    char **result;
    result = (char **) malloc(1000 * sizeof(char*));
    int itr = 0;
    while(token != NULL){ 
        result[itr] = (char *) malloc((1000)*sizeof(char));
        result[itr] = token;
        token = strtok(NULL,"/");
        itr++;
    }
    return result;
}

void remove_last_segment(char *str, const char *delim) {
    char *last_delim = strrchr(str, *delim); 
    if (last_delim != NULL) {
        *last_delim = '\0'; 
    }
}


char* getCurrentDirectory(char input[],char* home_directory, char* current_directory, char* prev_directory){
    if(input == NULL){
        strcpy(prev_directory,current_directory);
        strcpy(current_directory,home_directory);
        printf("%s\n",current_directory);
    }
    else{
        if(strcmp(input,"/") == 0 ){
            strcpy(current_directory,"/");
        }
        else{
            char *path_token = strtok(input,"/");
            char **path;
            path = (char **) malloc(10000 * sizeof(char*));
            int itr2 = 0;
            while(path_token != NULL){ 
                path[itr2] = (char *)malloc((1000)*sizeof(char));
                path[itr2] = path_token;
                if((strcmp(path_token,"..") == 0 ) && strcmp(current_directory,home_directory) != 0){
                    char *temp_dir = (char *) malloc(strlen(current_directory)*10*sizeof(char));
                    strcpy(temp_dir,current_directory);
                    // char **current_path = tokenization(temp_dir);
                    // int n = 0;
                    // for(int i=0;current_path[i]!=NULL;i++) n++;
                    // strcpy(dir,"/");
                    // for(int i=0;i<n-1;i++){
                    //     dir = strcat(dir,current_path[i]);
                    //     if(i != n-2)
                    //         dir = strcat(dir,"/");
                    // }
                    const char delimiter = '/';
                    remove_last_segment(temp_dir, &delimiter);
                    strcpy(prev_directory,current_directory);
                    strcpy(current_directory,temp_dir);
                }
                else if(strcmp(path_token,"..") == 0 && strcmp(current_directory,home_directory) == 0){
                    // 
                }
                else if(strcmp(path_token,".") == 0){
                    //
                }
                else if(strcmp(path_token,"~") == 0){
                    strcpy(prev_directory,current_directory);
                    strcpy(current_directory,home_directory);
                }
                else if(strcmp(path_token,"-") == 0){
                    printf("%s\n",prev_directory);
                    char *temp;
                    temp = (char *)malloc(strlen(prev_directory) + 1);
                    strcpy(temp,prev_directory);
                    strcpy(current_directory,prev_directory);
                    strcpy(prev_directory,temp);
                }
                else{
                    DIR *directory;
                    struct dirent * entry;
                    int isValid = 0;
                    if((directory = opendir(current_directory)) == NULL){
                        perror("opendir() error");
                    }   
                    else{
                        strcpy(prev_directory,current_directory);
                        while((entry = readdir(directory)) != NULL){                
                            if(strcmp(entry->d_name,path_token) == 0){
                                if(strcmp(current_directory,"/") != 0){
                                    char *extention = "/";
                                    strcat(current_directory,extention);                        
                                }                                            
                                strcat(current_directory,path_token);                                
                                isValid = 1;
                                break;
                            }   
                        }
                        closedir(directory);
                    }
                    
                    if(!isValid)
                        printf("bash: cd: %s: No such file or directory\n",path_token);
                }
                path_token = strtok(NULL,"/");
                itr2++;
            }
        }

    }
    return current_directory;
}

// int main(){

//     char home_directory[FILENAME_MAX];
//     getcwd(home_directory, sizeof(home_directory));

//     char *current_directory,*prev_directory ;
//     current_directory = (char *)malloc(strlen(home_directory)*100*sizeof(char));
//     prev_directory = (char *)malloc(strlen(home_directory)*100*sizeof(char));

//     if (current_directory == NULL || prev_directory == NULL) {
//         printf("Memory allocation failed.\n");
//         return 1;
//     }

//     strcpy(current_directory,home_directory);
//     strcpy(prev_directory,home_directory);
//     printf("%s\n",current_directory);

//     while(1){
//         char input[1024];
//         scanf("%[^\n]%*c",input);
//         current_directory = getCurrentDirectory(input,home_directory,current_directory,prev_directory);
//         printf("ans--->%s\n",current_directory);
//     }

//     return 0;
// }
