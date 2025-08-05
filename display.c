#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    // Get hostname
    char systemname[1024];
    if (gethostname(systemname, sizeof(systemname)) != 0) 
    {
        perror("gethostname failed");
        return 1;
    }

    // Get username using getpwuid
    struct passwd *pw = getpwuid(getuid());
    if (pw == NULL) 
    {
        perror("getpwuid failed");
        return 1;
    }
    char *username = pw->pw_name;

    // Get current working directory
    char cwd[FILENAME_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) 
    {
        perror("getcwd failed");
        return 1;
    }

    printf("%s@%s:%s$\n", username, systemname, cwd);
    return 0;
}