Project 01 - README
===================

Members
-------

- John McGuinness (jmcguin1@nd.edu)
- Kwan Ho Herman Tong (ktong1@nd.edu)
- Kendyll Krauss (kkraus1@nd.edu)

Responses
---------

1. We handled parsing the command line options by using if statements inside of a while loop.  We first checked to make sure there were at least 2 arguments, and if so, we set the program name to the first argument and the path equal to the second argument.  The argument index was set at 2, and while this was less than the total number of arguments, we checked each specified option.  If any of these options were entered, then the corresponding variable in settings was set to the correct value.  Some of the options required more than one argument, so this was checked and handled inside the if statement. Search was then run on the path and the settings.
2. The directory tree was walked in search.c.  We started by opening the root directory and if this was successful, assigning a pointer to the first entry in the directory.  A while loop was used to make sure every entry was stepped through.  If the filename was ".", then filter was run to see if execute should run also.  If te filename was "..", then nothing was done.  Otherwise, a new path was generated with the new file such that the name appeared as root/filename.  If this was a directory, then search was recursively run on this directory.  Otherwise, filter was run to see if execute needed to be run.  The directory was closed, and EXIT_SUCCESS was returned.  If the directory was not able to be opened, then filter was run to see if execute needed to run as well, the directory was closed, and EXIT_FAILURE was returned.  
3. We determined whether or not to print a filesystem objects path with the command line parsing.  If -print was specified, then the settings option for print was set to true.  In execute.c, we first checked if -exec was specified and if it was, we also checked if -print was specified.  If it was, then we printed the path.  If -exec was not specified, then we assumed that -print was specified and we printed the path.
4. Find uses a lesser number of system calls, but uses more types of calls.  I noticed that both programs took the exact same total time to run.  Also, I noticed that the strace of find had twice the amount of errors as search did.  Find has 82 errors on open whereas search only has 40 (for a search /etc).  I think that this means that find has access to more directories and is able to search more directories since it is a linux command.

Contributions
-------------
Herman: 

* Completed Makefile and utilities.c.
* Added test_utils.c which was used to test utilities.c
* Wrote and debugged search.c.
* Added test_search.c and tested search.c
* Completed filter.c, everything tested except for permission
* Added test_filter.c
* Helped writing and debugging execute.c and main.c

Kendyll: 

* Debugged main.c, execute.c, and filter.c
* Completed README.md
* Completed syscalls.py

John:	

* Wrote and helped debug execute.c.
* Wrote the majority of main.c and debugged many errors.
* Fixed errors in filter.c.
* Helped debug search.c.
* Added TROLL as an easter egg.
		
