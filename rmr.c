#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>

#define BOLD "\033[1m"
#define RESET "\033[0m"
#define RED "\033[31m"

void fn_rmfile(const char *filepath) {
    printf("%s\n%s is a file:\n", BOLD, filepath);
    char command[PATH_MAX + 20];
    snprintf(command, sizeof(command), "ls -ltr %s", filepath);
    system(command);

    printf("\nrmr: remove this file? (y/n) %s", RESET);

    char answer;
    system("stty raw -echo");
    answer = getchar();
    system("stty sane");

    if (answer == 'y' || answer == 'Y') {
        char rm_command[PATH_MAX + 20];
        snprintf(rm_command, sizeof(rm_command), "rm %s", filepath);
        int result = system(rm_command);
        printf("\n\n");
        if (result == 0) {
            printf("\nDone! File \"%s\" removed.\n\n", filepath);
        } else {
            printf("\n\n%s%s not removed, check permissions:\n\n", BOLD, filepath);
            system(command);
        }
    } else {
        printf("\n\n%sFiles remain:\n", RED);
        system(command);
        printf("%s\n", RESET);
    }
}

bool checkwrite(int argc, char *argv[]) {
    bool multiple = false;
    for (int i = 1; i < argc; i++) {
        struct stat buffer;
        if (stat(argv[i], &buffer) == 0) {
            if (i > 1) multiple = true;
        }
    }
    return multiple;
}

void process_path(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);

    if (S_ISDIR(path_stat.st_mode)) {
        printf("%s\n", BOLD);
        char command[PATH_MAX + 20];
        snprintf(command, sizeof(command), "rmdir %s", path);
        if (system(command) == 0) {
            printf("Removing empty directory %s...\n\n$ ls %s/ \n", path, path);
            snprintf(command, sizeof(command), "ls %s", path);
            system(command);
        } else {
            printf("\nRemoving %s...\n\n$ find \"%s\" \n", path, path);
            snprintf(command, sizeof(command), "find %s", path);
            system(command);
            snprintf(command, sizeof(command), "rm -rI %s", path);
            system(command);
            printf("%s", RESET);
        }

        if (stat(path, &path_stat) != 0) {
            printf("\nDone!\n");
        } else {
            printf("\n\n%sRemoval Failed!%s\n\n%s is still present, check ownership and permissions:\n", BOLD, RESET, path);
            snprintf(command, sizeof(command), "ls -lad --color=always %s", path);
            system(command);
        }
    } else if (S_ISREG(path_stat.st_mode)) {
        fn_rmfile(path);
    } else {
        printf("\n\nNo such directory or file found!\n\n");
    }
}

int main(int argc, char *argv[]) {
    char *scriptname = realpath(argv[0], NULL);

    bool multiple = checkwrite(argc, argv);
    if (multiple) {
        for (int i = 1; i < argc; i++) {
            if (access(argv[i], W_OK) != 0) {
                char confirm;
                printf("Unwriteable files; elevate to sudo? (Y/n) ");
                confirm = getchar();
                if (confirm == 'y' || confirm == 'Y' || confirm == '\n') {
                    system("sudo -v");
                } else {
                    exit(1);
                }
            }
        }
    }

    for (int i = 1; i < argc; i++) {
        process_path(argv[i]);
    }

    free(scriptname);
    return 0;
}
