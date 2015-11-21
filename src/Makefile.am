# src/Makefile.am

SUFFIXES = .c .h .y .l

AM_CFLAGS = @CFLAGS@ -Wshadow -Wall -I$(srcdir) -I$(srcdir)/../h
AM_LDFLAGS = @LDFLAGS@
AM_YFLAGS = -d

if DEBUG_FLEX
AM_LFLAGS = --debug
endif

bin_PROGRAMS = zsbc

check_PROGRAMS = zsbc

zsbc_SOURCES = main.c expr.c expr.h vars.c vars.h array.c array.h numwrap.c numwrap.h \
               program.c program.h parser.y lexer.l common.h uthash.h
zsbc_LDFLAGS = 

LIBBC = ../lib/libbc.a

if WITH_GMP
zsbc_LDFLAGS += -lgmp
endif

if WITH_LIBBC
$(PROGRAMS): $(LIBBC)
zsbc_SOURCES += bc/libmath.c bc/libmath.b
zsbc_LDADD = $(LIBBC)
endif

if WITH_READLINE
zsbc_LDFLAGS += -lreadline
endif

BUILT_SOURCES = parser.h

MAINTAINERCLEANFILES = lexer.c parser.c parser.h

bc/libmath.c: bc/libmath.b
	./prepb.sh "libbc_libmath" $<

