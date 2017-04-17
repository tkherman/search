/* utilities.c */

#include "search.h"

#include <errno.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Test whether or not a directory is empty.
 * @param   path        Path to directory.
 * @return  Whether or not a directory is empty.
 */
bool        is_directory_empty(const char *path) {
    struct dirent *dp;
    DIR *dir = opendir(path);
    bool is_empty = true;

    if (dir) {
        while ((dp = readdir(dir)) != NULL) {
            // anything that's not an entry
            // (. or .. will satisfy the condition)
            // and set is_empty to false and exit while loop
            
            if (dp->d_type != DT_DIR) {
                is_empty = false;
                break;
            } else if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
                is_empty = false;
                break;
            }
        }
    } else {
        // prints string error if system call fails
        fprintf(stderr, "Error: %s\n", strerror(errno));
        is_empty = false;
    }

    closedir(dir);

    return is_empty;
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t      get_mtime(const char *path) {
    struct stat s;
    lstat(path, &s);
    
    return s.st_mtime;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
