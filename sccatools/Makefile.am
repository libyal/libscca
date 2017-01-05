AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBSCCA_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	sccainfo

sccainfo_SOURCES = \
	info_handle.c info_handle.h \
	sccainfo.c \
	sccainput.c sccainput.h \
	sccatools_getopt.c sccatools_getopt.h \
	sccatools_i18n.h \
	sccatools_libbfio.h \
	sccatools_libcerror.h \
	sccatools_libclocale.h \
	sccatools_libcnotify.h \
	sccatools_libfdatetime.h \
	sccatools_libscca.h \
	sccatools_libuna.h \
	sccatools_output.c sccatools_output.h \
	sccatools_signal.c sccatools_signal.h \
	sccatools_unused.h

sccainfo_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on sccainfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(sccainfo_SOURCES)

