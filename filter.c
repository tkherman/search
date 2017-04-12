/* filter.c */

#include "search.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <stdlib.h>

#include <stdio.h>

/**
 * Test whether or not the given path should be filtered out of the output.
 * @param   path        Path to file or directory.
 * @param   settings    Settings structure.
 * @return  Whether or not the path should be excluded from the output (true to
 * exclude, false to include).
 */
bool        filter(const char *path, const Settings *settings) {
    // get struct stat of the file
    struct stat s;
    lstat(path, &s);
    
    
    // check -executable -readable -writable
    if (settings->access && access(path, settings->access) != 0)
        return true;


    // check type f for file d for directory
    if (settings->type) {
        if (settings->type == 'f' && !S_ISREG(s.st_mode))
            return true;
        else if (settings->type == 'd' && !S_ISDIR(s.st_mode))
            return true;
    }


    // check if it's empty, return true if not
    if (settings->empty && s.st_size != 0)
        return true;


    // check if base of file name matches shell pattern
    if (settings->name) {
        char *pathname = strdup(path); // since basename expects char*
        if (fnmatch(settings->name, basename(pathname), 0)) {
            free(pathname);
            return true;
        }
        free(pathname);
    }

    // check if path of file matches shell pattern
    if (settings->path) {
        char *pathname = strdup(path);
        if (fnmatch(settings->path, pathname, FNM_PATHNAME)) {
            free(pathname);
            return true;
        }
        free(pathname);
    }


    // check permission assuming settings->perm was set in octal
    if (settings->perm) {
        int file_perm = s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
        printf ("%d\n", file_perm);
        if (settings->perm != file_perm)
            return true;
    }

    // check if it's newer than file
    if (settings->newer && settings->newer < get_mtime(path))
        return true;


    // check if uid matches
    if (settings->uid && s.st_uid != settings->uid) {
        return true;
    }

    // check if gid matches
    if (settings->gid && s.st_gid != settings->gid)
        return true;


    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
