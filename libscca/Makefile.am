AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBSCCA_DLL_EXPORT@

lib_LTLIBRARIES = libscca.la

libscca_la_SOURCES = \
	libscca.c \
	libscca_codepage.h \
	libscca_compressed_block.c libscca_compressed_block.h \
	libscca_compressed_blocks_stream.c libscca_compressed_blocks_stream.h \
	libscca_debug.c libscca_debug.h \
	libscca_definitions.h \
	libscca_error.c libscca_error.h \
	libscca_extern.h \
	libscca_file.c libscca_file.h \
	libscca_file_information.c libscca_file_information.h \
	libscca_file_metrics.c libscca_file_metrics.h \
	libscca_filename_strings.c libscca_filename_strings.h \
	libscca_io_handle.c libscca_io_handle.h \
	libscca_libbfio.h \
	libscca_libcdata.h \
	libscca_libcerror.h \
	libscca_libclocale.h \
	libscca_libcnotify.h \
	libscca_libfcache.h \
	libscca_libfdata.h \
	libscca_libfdatetime.h \
	libscca_libfvalue.h \
	libscca_libfwnt.h \
	libscca_libuna.h \
	libscca_notify.c libscca_notify.h \
	libscca_support.c libscca_support.h \
	libscca_types.h \
	libscca_unused.h \
	libscca_volume_information.c libscca_volume_information.h \
	scca_file_header.h \
	scca_file_information.h \
	scca_file_metrics_array.h \
	scca_trace_chain_array.h \
	scca_volume_information.h

libscca_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@LIBFWNT_LIBADD@ \
	@PTHREAD_LIBADD@

libscca_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libscca_definitions.h.in \
	libscca.rc \
	libscca.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libscca_definitions.h
	/bin/rm -f libscca.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libscca ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libscca_la_SOURCES)

