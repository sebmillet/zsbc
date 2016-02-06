# Makefile.am

AUTOMAKE_OPTIONS = dejagnu
RUNTESTDEFAULTFLAGS = --all --tool zsbc --srcdir tests

SUBDIRS = lib src doc
ACLOCAL_AMFLAGS = -I admin

dist_doc_DATA=README

EXTRA_DIST=bootstrap makefile.mingw makefile.vc src/parser.h src/prepb.sh src/prept.sh \
		   h/number.h extracfg.h FAQ tests prof

dist-hook:
	rm -rf `find $(distdir) -name .git`

appsdir = $(datadir)/applications

