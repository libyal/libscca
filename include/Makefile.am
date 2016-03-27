include_HEADERS = \
	libscca.h

pkginclude_HEADERS = \
	libscca/codepage.h \
	libscca/definitions.h \
	libscca/error.h \
	libscca/extern.h \
	libscca/features.h \
	libscca/types.h

EXTRA_DIST = \
	libscca.h.in \
	libscca/definitions.h.in \
	libscca/features.h.in \
	libscca/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libscca.h
	/bin/rm -f libscca/definitions.h
	/bin/rm -f libscca/features.h
	/bin/rm -f libscca/types.h
	/bin/rm -f Makefile

