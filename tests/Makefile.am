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
	test_sccainfo.sh \
	$(TESTS_PYSCCA)

check_SCRIPTS = \
	pyscca_test_get_version.py \
	pyscca_test_open_close.py \
	test_api_functions.sh \
	test_python_functions.sh \
	test_runner.sh \
	test_sccainfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	scca_test_get_version \
	scca_test_open_close

scca_test_get_version_SOURCES = \
	scca_test_get_version.c \
	scca_test_libcstring.h \
	scca_test_libscca.h \
	scca_test_unused.h

scca_test_get_version_LDADD = \
	../libscca/libscca.la \
	@LIBCSTRING_LIBADD@

scca_test_open_close_SOURCES = \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_libcstring.h \
	scca_test_libcsystem.h \
	scca_test_open_close.c

scca_test_open_close_LDADD = \
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

