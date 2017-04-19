/* expression.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Executes the -print or -exec expressions (or both) on the specified path.
 * @param   path        Path to a file or directory
 * @param   settings    Settings structure.
 * @return  Whether or not the execution was successful.
 */
int	    execute(const char *path, const Settings *settings) {

    if(settings->exec_argc) {
        pid_t id = fork();
        if(id > 0) { //this is the parent process
            int status;
            wait(&status);

            if (settings->print)
                puts(path);

            return EXIT_SUCCESS;

        } else if (id == 0) { //this is the child process
            char *exec_arg[settings->exec_argc + 1]; 
            for (int i = 0; i < settings->exec_argc; i++) {
                exec_arg[i] = settings->exec_argv[i];
            }

            char path_nc[strlen(path) + 1];
            strcpy(path_nc, path);
            
            exec_arg[settings->exec_argc - 1] = path_nc;
            
            exec_arg[settings->exec_argc] = NULL; // one extra spot allocated, won't segfault

            if (execvp(exec_arg[0], exec_arg) < 0) {
                fprintf(stderr, "Unable to exec: %s\n", strerror(errno));
            }
            _exit(EXIT_FAILURE);
            
        } else {
            // fork failed
            fprintf(stderr, "Error: %s\n", strerror(errno));
            return EXIT_FAILURE;
        } 
    }

    puts(path);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
