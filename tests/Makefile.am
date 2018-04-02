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
	@LIBSCCA_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYSCCA = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_sccainfo.sh \
	$(TESTS_PYSCCA)

check_SCRIPTS = \
	pyscca_test_file.py \
	pyscca_test_support.py \
	test_library.sh \
	test_python_module.sh \
	test_runner.sh \
	test_sccainfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	scca_test_compressed_block \
	scca_test_error \
	scca_test_file \
	scca_test_file_information \
	scca_test_file_metrics \
	scca_test_filename_strings \
	scca_test_io_handle \
	scca_test_notify \
	scca_test_support \
	scca_test_volume_information

scca_test_compressed_block_SOURCES = \
	scca_test_compressed_block.c \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_compressed_block_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_error_SOURCES = \
	scca_test_error.c \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_unused.h

scca_test_error_LDADD = \
	../libscca/libscca.la

scca_test_file_SOURCES = \
	scca_test_file.c \
	scca_test_functions.c scca_test_functions.h \
	scca_test_getopt.c scca_test_getopt.h \
	scca_test_libbfio.h \
	scca_test_libcerror.h \
	scca_test_libclocale.h \
	scca_test_libcnotify.h \
	scca_test_libscca.h \
	scca_test_libuna.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libscca/libscca.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

scca_test_file_information_SOURCES = \
	scca_test_file_information.c \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_file_information_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_file_metrics_SOURCES = \
	scca_test_file_metrics.c \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_file_metrics_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_filename_strings_SOURCES = \
	scca_test_filename_strings.c \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_filename_strings_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_io_handle_SOURCES = \
	scca_test_io_handle.c \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_io_handle_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_notify_SOURCES = \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_notify.c \
	scca_test_unused.h

scca_test_notify_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_support_SOURCES = \
	scca_test_functions.c scca_test_functions.h \
	scca_test_getopt.c scca_test_getopt.h \
	scca_test_libbfio.h \
	scca_test_libcerror.h \
	scca_test_libclocale.h \
	scca_test_libcnotify.h \
	scca_test_libscca.h \
	scca_test_libuna.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_support.c \
	scca_test_unused.h

scca_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_volume_information_SOURCES = \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h \
	scca_test_volume_information.c

scca_test_volume_information_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

