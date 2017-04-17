/* driver.c */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <sys/stat.h>
#include <unistd.h>

/* Functions */

void	    usage(const char *program_name, int status) {
    fprintf(stderr, "Usage: %s PATH [OPTIONS] [EXPRESSION]\n", program_name);
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "    -executable     File is executable or directory is searchable to user\n");
    fprintf(stderr, "    -readable       File readable to user\n");
    fprintf(stderr, "    -writable       File is writable to user\n\n");
    fprintf(stderr, "    -type [f|d]     File is of type f for regular file or d for directory\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -name  pattern  Base of file name matches shell pattern\n");
    fprintf(stderr, "    -path  pattern  Path of file matches shell pattern\n\n");
    fprintf(stderr, "    -perm  mode     File's permission bits are exactly mode (octal)\n");
    fprintf(stderr, "    -newer file     File was modified more recently than file\n\n");
    fprintf(stderr, "    -uid   n        File's numeric user ID is n\n");
    fprintf(stderr, "    -gid   n        File's numeric group ID is n\n");
    fprintf(stderr, "\nExpressions:\n\n");
    fprintf(stderr, "    -print          Display file path (default)\n");
    fprintf(stderr, "    -exec cmd {} ;  Execute command on path\n");
    exit(status);
}

/* Main Execution */

int	    main(int argc, char *argv[]) {

    /* Initialize Settings struct */
    Settings settings = {
        .access = 0,
        .uid    = -1, 
        .gid    = -1,
    };

    /* Parse command line arguments */
    char *path;
    char * prog_name = argv[0];
    
    
    if (argc < 2) 
        usage(prog_name, 1);
    else
        path = argv[1];
    
    // starting argument at index 2 since 1 is the root
    int argind = 2;

    while (argind < argc) {
        char *arg = argv[argind++];

        if (streq(arg, "-executable")) {
            settings.access |= X_OK;

        } else if (streq(arg, "-readable")) {
            settings.access |= R_OK;

        } else if (streq(arg, "-writable")) {
            settings.access |= W_OK;

        } else if (streq(arg, "-type")) {
            if(argind < argc) {
                char opt = argv[argind++][0];
                if(opt == 'f') settings.type = 'f';
                else if(opt == 'd') settings.type = 'd';
            } else {
                fprintf(stderr, "Error: -type requires another argument ('f' or 'd')\n");
                usage(prog_name,1);
            }

        } else if (streq(arg, "-empty")) {
            settings.empty = true;

        } else if (streq(arg, "-name")) {
            if(argind < argc) {
                settings.name = argv[argind++];
            } else {
                fprintf(stderr, "Error: -name requires another argument\n");
                usage(prog_name,1);
            }

        } else if (streq(arg, "-path")) {
            if(argind < argc) {
                settings.path = argv[argind++];
            } else {
                fprintf(stderr, "Error: -path requires another argument\n");
                usage(prog_name,1);
            }

        } else if(streq(arg, "-perm")) { 
            if(argind < argc) {
                char *ptr;
                unsigned long int decimal = strtoul(argv[argind++], &ptr, 8);
                settings.perm = decimal & INT_MAX;
            } else {
                fprintf(stderr, "Error: -perm requires another argument\n");
                usage(prog_name,1);
            }

        } else if(streq(arg, "-newer")) { 
            if(argind < argc) {
                settings.newer = get_mtime(argv[argind++]);
            } else {
                fprintf(stderr, "Error: -newer requires another argument\n");
                usage(prog_name,1);
            }

        } else if (streq(arg, "-uid")) {
            if(argind < argc) {
                settings.uid = atoi(argv[argind++]);
            } else {
                fprintf(stderr, "Error: -uid requires another argument\n");
                usage(prog_name,1);
            }

        } else if (streq(arg, "-gid")) {
            if(argind < argc) {
                settings.gid = atoi(argv[argind++]);
            } else {
                fprintf(stderr, "Error: -gid requires another argument\n");
                usage(prog_name,1);
            }

        } else if (streq(arg, "-print")) {
            settings.print = true;

        } else if (streq(arg, "-exec")) {

            settings.exec_argv = &argv[argind++];
            int temp_argc = 1;
            if (argind >= argc) {
                fprintf(stderr, "Error: invalid use of -exec\n");
                usage(prog_name, 1);
            }
            while (!streq(argv[argind++], ";")) {
                temp_argc++;
                if (argind >= argc) {
                    fprintf(stderr, "Error: invalid use of -exec\n");
                    usage(prog_name, 1);
                }
            }
            settings.exec_argc = temp_argc;
            
        }           
           

    }
    search(path, &settings);
    

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
