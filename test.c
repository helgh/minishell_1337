#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <limits.h>

int main() {

    // char buff[PATH_MAX];
    char *cwd;

    // cwd = getcwd(buff, PATH_MAX);
    cwd = getenv("PATH");
    printf("%s\n", cwd);
    return 0;
}
