#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char home_dir[1024];

void capture_prompt(void) {
    if (!getcwd(home_dir, sizeof(home_dir))) {
        home_dir[0] = '\0';
    }
}

void show_prompt(void) {
    char host[256];
    char cwd[1024];

    char *user = getenv("USER");
    if (!user) {
        user = "user";
    }

    gethostname(host, sizeof(host));

    if (!getcwd(cwd, sizeof(cwd))) {
        strcpy(cwd, "?");
    }

    size_t len = strlen(home_dir);

    if (len > 0 && strncmp(cwd, home_dir, len) == 0 && (cwd[len] == '\0' || cwd[len] == '/')) {
        printf("<%s@%s:~%s> ", user, host, cwd + len);
    } else {
        printf("<%s@%s:%s> ", user, host, cwd);
    }

    fflush(stdout);
}