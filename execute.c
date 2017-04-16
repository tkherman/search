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
    
    if(settings->print)
        puts(path);

    if(settings->access == X_OK) {

        pid_t id = fork();
        if(id == -1) {
            //fork failed
            fprintf(stderr, "Error: %s\n", strerror(errno));
            return EXIT_FAILURE;
        } else if(id > 0) { //this is the parent process
            int status;
            while(wait(&status) != id);

        } else { //this is the child process
            if(execvp(path, settings->exec_argv) < 0) { //command executed
                //if here, execution failed
                fprintf(stderr, "Error: %s\n", strerror(errno));
                return EXIT_FAILURE;
           } 
        }

    } else puts(path);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
