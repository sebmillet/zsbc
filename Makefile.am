# Makefile.am

AUTOMAKE_OPTIONS = dejagnu
RUNTESTDEFAULTFLAGS = --all --tool zsbc --srcdir $$srcdir/tests

SUBDIRS = src
ACLOCAL_AMFLAGS = -I admin

dist_doc_DATA=README

EXTRA_DIST=bootstrap makefile.mingw src/parser.h tests

dist-hook:
	rm -rf `find $(distdir) -name .git`

appsdir = $(datadir)/applications

