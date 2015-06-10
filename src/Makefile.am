# src/Makefile.am

SUFFIXES = .c .h .y .l

AM_CPPFLAGS = -Wshadow -Wall
AM_YFLAGS = -d

if DEBUG_FLEX
AM_LFLAGS = --debug
endif

bin_PROGRAMS = zsbc

check_PROGRAMS = zsbc

zsbc_SOURCES = expr.c expr.h parser.y lexer.l common.h
zsbc_LDFLAGS = 
zsbc_LDADD = -lgmp

BUILT_SOURCES = parser.h

MAINTAINERCLEANFILES = lexer.c parser.c parser.h

