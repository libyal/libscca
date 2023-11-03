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
	-rm -f libscca.h
	-rm -f libscca/definitions.h
	-rm -f libscca/features.h
	-rm -f libscca/types.h
	-rm -f Makefile

