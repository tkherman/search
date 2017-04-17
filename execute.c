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
        if(id == -1) {
            //fork failed
            fprintf(stderr, "Error: %s\n", strerror(errno));
            return EXIT_FAILURE;
        } else if(id > 0) { //this is the parent process
            int status;
            wait(&status);

            if (settings->print)
                puts(path);

            return EXIT_SUCCESS;

        } else { //this is the child process
            char **exec_arg = settings->exec_argv;
            // attach path to the end of exec_arg
            char *path_nc = strdup(path);
            exec_arg[settings->exec_argc - 2] = path_nc;
            exec_arg[settings->exec_argc - 1] = NULL;
            
            execvp(exec_arg[0], exec_arg);  //command executed
            
            //if it gets here, execution failed
            fprintf(stderr, "Error: %s\n", strerror(errno));
            return EXIT_FAILURE;
           } 
        }

<<<<<<< HEAD
    }
=======
    };
    
    puts(path);

>>>>>>> 7933dcdf069cd6f93bb3d4f19c01b123b006adfd

    return EXIT_SUCCESS;
};

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
