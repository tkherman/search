CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	search

all:		$(TARGETS)

search: execute.o filter.o main.o search.o utilities.o
	@echo Linking search...
	@$(LD) $(LDFLAGS) -o $@ $^

main.o: main.c search.h
	@echo Compiling main.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

execute.o: execute.c search.h
	@echo Compiling execute.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

filter.o: filter.c search.h
	@echo Compiling filter.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

search.o: search.c search.h
	@echo Compiling search.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

utilities.o: utilities.c search.h
	@echo Compiling utilities.o...
	@$(CC) $(CFLAGS) -o $@ -c $<

test:		search test_search.sh
	@echo Testing $<...
	@./test_search.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o *.log *.input

.PHONY:		all test benchmark clean

