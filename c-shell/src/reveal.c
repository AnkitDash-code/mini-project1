#include "builtins.h"
#include <sys/stat.h>
#include <dirent.h>

extern char prev_cwd[PATH_MAX];

static void reveal_dir(const char *path, const char *prefix, int show_all, int recursive) {
    DIR *dir = opendir(path);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    char entries[1000][PATH_MAX];
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!show_all && entry->d_name[0] == '.') {
            continue;
        }
        if (count < 1000) {
            strcpy(entries[count], entry->d_name);
            count++;
        }
    }
    closedir(dir);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(entries[i], entries[j]) > 0) {
                char temp[PATH_MAX];
                strcpy(temp, entries[i]);
                strcpy(entries[i], entries[j]);
                strcpy(entries[j], temp);
            }
        }
    }

    for (int i = 0; i < count; i++) {
        char full_path[PATH_MAX * 2];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entries[i]);

        struct stat st;
        int is_dir = (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode));

        if (is_dir) {
            printf("%s%s/\n", prefix, entries[i]);
            if (recursive) {
                if (strcmp(entries[i], ".") != 0 && strcmp(entries[i], "..") != 0) {
                    char sub_prefix[PATH_MAX * 2];
                    snprintf(sub_prefix, sizeof(sub_prefix), "%s%s/", prefix, entries[i]);
                    reveal_dir(full_path, sub_prefix, show_all, recursive);
                }
            }
        } 
        else {
            printf("%s%s\n", prefix, entries[i]);
        }
    }
}

int handle_reveal(const Token *args) {
    int show_all = 0;
    int recursive = 0;
    int target_found = 0;
    char *target = NULL;

    if (args != NULL && args->value != NULL && strcmp(args->value, "reveal") == 0) {
        args = args->next;
    }

    while (args != NULL) {
        if (args->value == NULL) {
            args = args->next;
            continue;
        }

        if (args->value[0] == '-' && args->value[1] != '\0') {
            for (int i = 1; args->value[i] != '\0'; i++) {
                if (args->value[i] == 'a') {
                    show_all = 1;
                } 
                else if (args->value[i] == 't') {
                    recursive = 1;
                } 
                else {
                    printf("reveal: invalid syntax\n");
                    return 0;
                }
            }
        } 
        else {
            if (target_found) {
                printf("reveal: invalid syntax\n");
                return 0;
            }
            target = args->value;
            target_found = 1;
        }

        args = args->next;
    }

    char resolved[PATH_MAX];

    if (!target || strcmp(target, ".") == 0) {
        if (getcwd(resolved, sizeof(resolved)) == NULL) {
            printf("reveal: no such directory\n");
            return 0;
        }
    } 

    else if (strcmp(target, "~") == 0) {
        char *home = getenv("HOME");
        if (!home) {
            printf("reveal: no such directory\n");
            return 0;
        }
        strcpy(resolved, home);
    } 

    else if (strcmp(target, "-") == 0) {
        if (prev_cwd[0] == '\0') {
            printf("reveal: no such dir\n");
            return 0;
        }
        strcpy(resolved, prev_cwd);
    } 

    else {
        strcpy(resolved, target);
    }

    struct stat st;
    if (stat(resolved, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("reveal: no such dir\n");
        return 0;
    }

    reveal_dir(resolved, "", show_all, recursive);
    return 0;

    
}