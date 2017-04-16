/* search.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>

/**
 * Recursively search through the provided root directory
 * @param   root        Path to directory
 * @param   settings    Settings structure
 * @return  Whether or not the search was successful.
 */
int	    search(const char *root, const Settings *settings) {
    struct dirent *dp;
    DIR *dir = opendir(root);
    
    if (dir) {
        while ((dp = readdir(dir)) != NULL) {
            
            //check if . or ..
            if(streq(dp->d_name,".")) {
                // run filter and execute on root
                if (!filter(root, settings))
                    execute(root, settings);
            } else if(streq(dp->d_name,".."))
                continue;
            else {
                // generate new path
                char newpath[strlen(root) + strlen(dp->d_name) + 2];
                sprintf(newpath, "%s/%s", root, dp->d_name);
                
                // check if it is a directory, if so, recurse
                if (dp->d_type == DT_DIR)
                    search(newpath, settings);

                // pass this directory/file into filter to determine if
                // it has to be executed
                else 
                    if (!filter(newpath, settings))
                        execute(newpath, settings);

            }

        }
    } else {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        closedir(dir);
        return EXIT_FAILURE;
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
