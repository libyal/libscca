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
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBSCCA_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYSCCA = \
	test_python_functions.sh
endif

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_sccainfo.sh \
	$(TESTS_PYSCCA)

check_SCRIPTS = \
	pyscca_test_get_version.py \
	pyscca_test_open_close.py \
	test_api_functions.sh \
	test_api_types.sh \
	test_python_functions.sh \
	test_runner.sh \
	test_sccainfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	scca_test_error \
	scca_test_file \
	scca_test_file_metrics \
	scca_test_notify \
	scca_test_open_close \
	scca_test_support \
	scca_test_volume_information

scca_test_error_SOURCES = \
	scca_test_error.c \
	scca_test_libcstring.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_unused.h

scca_test_error_LDADD = \
	../libscca/libscca.la \
	@LIBCSTRING_LIBADD@

scca_test_notify_SOURCES = \
	scca_test_libcstring.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_notify.c \
	scca_test_unused.h

scca_test_notify_LDADD = \
	../libscca/libscca.la \
	@LIBCSTRING_LIBADD@

scca_test_file_SOURCES = \
	scca_test_file.c \
	scca_test_libcerror.h \
	scca_test_libcstring.h \
	scca_test_libcsystem.h \
	scca_test_libscca.h \
	scca_test_libuna.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_file_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libscca/libscca.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

scca_test_file_metrics_SOURCES = \
	scca_test_file_metrics.c \
	scca_test_libcerror.h \
	scca_test_libcstring.h \
	scca_test_libcsystem.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_file_metrics_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libscca/libscca.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

scca_test_open_close_SOURCES = \
	scca_test_libcerror.h \
	scca_test_libcstring.h \
	scca_test_libcsystem.h \
	scca_test_libscca.h \
	scca_test_open_close.c

scca_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libscca/libscca.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

scca_test_support_SOURCES = \
	scca_test_libcerror.h \
	scca_test_libcstring.h \
	scca_test_libcsystem.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_support.c \
	scca_test_unused.h

scca_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

scca_test_volume_information_SOURCES = \
	scca_test_libcerror.h \
	scca_test_libcstring.h \
	scca_test_libcsystem.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h \
	scca_test_volume_information.c

scca_test_volume_information_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libscca/libscca.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

