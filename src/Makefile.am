# src/Makefile.am

SUFFIXES = .c .h .y .l

AM_CPPFLAGS = -Wshadow -Wall -I$(srcdir) -I$(srcdir)/../h
AM_YFLAGS = -d

if DEBUG_FLEX
AM_LFLAGS = --debug
endif

bin_PROGRAMS = zsbc

check_PROGRAMS = zsbc

zsbc_SOURCES = main.c expr.c expr.h vars.c vars.h array.c array.h numwrap.c numwrap.h \
               program.c program.h parser.y lexer.l common.h bc/libmath.c
zsbc_LDFLAGS = 

# TODO: allow the user to NOT include libbc in compilation
#zsbc_SOURCES += bc/libmath.c

LIBBC = ../lib/libbc.a
zsbc_LDADD = -lgmp $(LIBBC)
$(PROGRAMS): $(LIBBC)

BUILT_SOURCES = parser.h

MAINTAINERCLEANFILES = lexer.c parser.c parser.h

bc/libmath.c: bc/libmath.b
	bc/mkreslib.sh $<

