AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBSCCA_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	sccainfo

sccainfo_SOURCES = \
	info_handle.c info_handle.h \
	sccainfo.c \
	sccainput.c sccainput.h \
	sccaoutput.c sccaoutput.h \
	sccatools_libbfio.h \
	sccatools_libcerror.h \
	sccatools_libclocale.h \
	sccatools_libcnotify.h \
	sccatools_libcstring.h \
	sccatools_libcsystem.h \
	sccatools_libfdatetime.h \
	sccatools_libscca.h \
	sccatools_libuna.h

sccainfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	../libscca/libscca.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on sccainfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(sccainfo_SOURCES)

