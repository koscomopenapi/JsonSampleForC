########################################################################
#	Makefile
#	Copyright (c) HTOne Co.,Ltd.
#	All right reserved.
#       Author : Kwang-Ho Choi <ksoren21@paran.com>
########################################################################
TARGET 	= test_json
OBJS 	= test_json.o

_OSTYPE_	= linux

DEVDIR = $(HOME)
SRCDIR	= $(DEVDIR)/src/json/test

BINDIR	= $(SRCDIR)
USRLIBS = -L$(DEVDIR)/lib
USRINCL = $(DEVDIR)/include
JANSSONINCL = $(HOME)/jansson-2.6

SOLARIS_SYSLIBLIST	= -lthread -lsocket -lnsl -lm -ljansson -lkplpstringmani -lkplpdatetime
LINUX_SYSLIBLIST	= -lpthread -lnsl -lm -ljansson -lkplpstringmani -lkplpdatetime
AIX_LIBLIST		= -lnsl -lpthread -lm -ldl -ljansson -lkplpstringmani -lkplpdatetime

OUTPUT_OPTION= -o $@
CFLAGS = -D_REENTRANT -I$(USRINCL)
CCFLAGS= -DXOR_KEY_DEFINE -D_REENTRANT -D$(_OSTYPE_) -I$(USRINCL) -I$(JANSSONINCL)
CPPFLAGS=

CC=gcc
GCC64=-m64
COMPILE=$(CC) $(CCFLAGS) $(CPPFLAGS) $(GCC64) -c -g
COMPILE.cpp=$(CC) $(CCFLAGS) $(CPPFLAGS) $(GCC64) -c -g

.SUFFIXES : .c .o .cc
.c.o   : 
	$(COMPILE) $<
.cc.o   : 
	$(COMPILE.cpp) $<

all : $(OBJS)
	$(CC) $(GCC64) -o $(TARGET) $(CFLAGS) $(OBJS) $(LINUX_SYSLIBLIST) $(USRLIBS)

linux : $(OBJS)
	$(CC) $(GCC64) -o $(TARGET) $(CFLAGS) $(OBJS) -rdynamic $(LINUX_SYSLIBLIST) $(USRLIBS)

solaris : $(OBJS)
	$(CC) $(GCC64) -o $(TARGET) $(CFLAGS) $(OBJS) $(SOLARIS_SYSLIBLIST) $(USRLIBS)

aix : $(OBJS)
	$(CC) $(GCC64) -o $(TARGET) $(CFLAGS) $(OBJS) $(AIX_LIBLIST) $(USRLIBS)
	
install :
	mv -f $(TARGET) $(BINDIR)

clean:
	rm -f *.o core $(TARGET)
