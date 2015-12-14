# doc/Makefile.am

MANPAGEEN=${srcdir}/zsbc.1
HTMLPAGEEN=${srcdir}/zsbc.html
TEXTPAGEEN=${srcdir}/zsbc.txt

dist_doc_DATA=${HTMLPAGEEN} ${TEXTPAGEEN}

EXTRA_DIST=${HTMLPAGEEN}

dist_man_MANS=${MANPAGEEN}

if BUILD_DOCS

${HTMLPAGEEN}: ${MANPAGEEN}
	man2html ${MANPAGEEN} > $@
${TEXTPAGEEN}: ${MANPAGEEN}
	nroff -man ${MANPAGEEN} | col -b > $@

endif

