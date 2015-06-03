# src/Makefile.am

SUFFIXES = .c .h .y .l

AM_CPPFLAGS = -Wshadow -Wall
AM_YFLAGS = -d

bin_PROGRAMS = zsbc

zsbc_SOURCES = parser.y lexer.l common.h
zsbc_LDFLAGS = 
zsbc_LDADD = -lgmp

BUILT_SOURCES = parser.h

MAINTAINERCLEANFILES = lexer.c parser.c parser.h

