# Filename:		Makefile
# Date:			11/22/2020
# Author:		Junsik Seo
# Email:		jxs161930@utdallas.edu
# Version:		1.0
# Copyright:		2020, All Rights Reserved
#
# Description:
#
#	A small project that will display a text based
#	GUI based on Curses / CDK.

# The compiler to use
CXX = g++

# C pre-processor flags
CPPFLAGS = -I /scratch/perkins/include -std=c++11

# compiler flags
CXXFLAGS = -Wall -Wno-write-strings

# linker flags
LDFLAGS = -L /scratch/perkins/lib

# More linker flags (order dependent)
LDLIBS = -lcdk -lcurses

# Project name.  This is used in building the file name for the backup target
PROJECTNAME = CDK

# Enter the name for the executable to be created
EXEC = cdk

SRCS = $(wildcard *.cc)
HEADERS = $(wildcard *.h)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

# These targets don't create files that Make should inspect
.PHONY: all clean backup

# The default target.  Its a good idea to use 'all' as the default
# so that the commands 'make' and 'make all' do the same thing.

all: $(EXEC)

#
# Clean up files that we can regenerate or that we don't care about.

clean:
	rm -f $(OBJS) *.d *~ $(EXEC)


# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


#  This is a rule to link the files.  Pretty standard

$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)

Makefile: $(SRCS:.cc=.d)

# Backup Target.   You should perform a "make backup" command often

backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


-include $(SRCS:.cc=.d)

