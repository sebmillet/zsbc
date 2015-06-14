# src/Makefile.am

SUFFIXES = .c .h .y .l

AM_CPPFLAGS = -Wshadow -Wall -I$(srcdir) -I$(srcdir)/../h
AM_YFLAGS = -d

if DEBUG_FLEX
AM_LFLAGS = --debug
endif

bin_PROGRAMS = zsbc

check_PROGRAMS = zsbc

zsbc_SOURCES = main.c expr.c expr.h vars.c vars.h numwrap.c numwrap.h parser.y lexer.l common.h
zsbc_LDFLAGS = 

LIBBC = ../lib/libbc.a
zsbc_LDADD = -lgmp $(LIBBC)
$(PROGRAMS): $(LIBBC)

BUILT_SOURCES = parser.h

MAINTAINERCLEANFILES = lexer.c parser.c parser.h

