#include "builtins.h"
#include <unistd.h>
#define MAX_ENTRIES 100

typedef enum {
    TARGET_HOME,
    TARGET_DOT,
    TARGET_DOTDOT,
    TARGET_PREV,
    TARGET_NAME
} hop_where;

typedef struct {
    char path[PATH_MAX];
    int score;        
} FrecencyEntry;

// Forced to use static as the data needs to persist the whole time the shell
//  runs not just when hop 
// is called
char prev_cwd[PATH_MAX] = "";
static FrecencyEntry frequency_db[MAX_ENTRIES];
static int frecency_count = 0;


static void record_visit(const char *path) {
    for (int i = 0; i < frecency_count; i++) {
        if (strcmp(frequency_db[i].path, path) == 0) {
            frequency_db[i].score++;
            return;
        }
    }
    if (frecency_count < MAX_ENTRIES) {
        strcpy(frequency_db[frecency_count].path, path);
        frequency_db[frecency_count].score = 1;
        frecency_count++;
    }
}

static int find_best_match(const char *name) {
    int best_idx = -1, max_score = -1;
    for (int i = 0; i < frecency_count; i++) {
        if (strstr(frequency_db[i].path, name) && frequency_db[i].score > max_score) {
            max_score = frequency_db[i].score;
            best_idx = i;
        }
    }
    return best_idx;
}

int handle_hop(const Token *args){
    
    hop_where target;
    if (args == NULL || args->value == NULL) {
        char temp_cwd[PATH_MAX];
        if (getcwd(temp_cwd, sizeof(temp_cwd)) != NULL) {
            char *home = getenv("HOME");
            if (home && chdir(home) == 0) {
                strcpy(prev_cwd, temp_cwd);
            }
        }
       return 0;
    }

    if (args != NULL && args->value != NULL && strcmp(args->value, "hop") == 0) {
        args = args->next;
    }

    if (args == NULL || args->value == NULL) {
        char temp_cwd[PATH_MAX];
        if (getcwd(temp_cwd, sizeof(temp_cwd)) != NULL) {
            char *home = getenv("HOME");
            if (home && chdir(home) == 0) {
                strcpy(prev_cwd, temp_cwd);
            }
        }
        return 0;
    }


    while( args != NULL){
        if (args->value == NULL) {
            args = args->next;
            continue;
        }

        if (strcmp(args->value, "~") == 0) {
        target = TARGET_HOME;
    } 
    else if (strcmp(args->value, ".") == 0) {
        target = TARGET_DOT;
    } 
    else if (strcmp(args->value, "-") == 0) {
        target = TARGET_PREV;
    } 
    else if (strcmp(args->value, "..") == 0) {
        target = TARGET_DOTDOT;
    }
    else{
        target = TARGET_NAME;
    }
    char temp_cwd[PATH_MAX];
    getcwd(temp_cwd, sizeof(temp_cwd));

    switch (target) {
            case TARGET_HOME: {
                char *home = getenv("HOME");
                if (home && chdir(home) == 0) {
                    strcpy(prev_cwd, temp_cwd);
                    record_visit(home);
                }
                break;
            }

            case TARGET_DOT:
                break;

            case TARGET_DOTDOT:
                if (chdir("..") == 0) {
                    strcpy(prev_cwd, temp_cwd);
                    char new_cwd[PATH_MAX];
                    if (getcwd(new_cwd, sizeof(new_cwd))) {
                        record_visit(new_cwd);
                    }
                }
                break;

            case TARGET_PREV:
                if (prev_cwd[0] == '\0') {
                    printf("Old PWD Not Found\n");
                } else {
                    char target_dir[PATH_MAX];
                    strcpy(target_dir, prev_cwd);
                    if (chdir(target_dir) == 0) {
                        strcpy(prev_cwd, temp_cwd);
                        record_visit(target_dir);
                    }
                }
                break;

            case TARGET_NAME:
                if (chdir(args->value) == 0){
                    strcpy(prev_cwd, temp_cwd);
                    char new_cwd[PATH_MAX];
                    if (getcwd(new_cwd, sizeof(new_cwd))) {
                        record_visit(new_cwd);
                    }
                    
                }
                else {
                    int match = find_best_match(args->value);
                    if (match != -1 && chdir(frequency_db[match].path) == 0) {
                        strcpy(prev_cwd, temp_cwd);
                        record_visit(frequency_db[match].path);
                    } else {
                        printf("Error: Non-existing directory\n");
                    }
                    break;
                }
                
                break;
        }

    args = args->next;
    }

    return 0;

}