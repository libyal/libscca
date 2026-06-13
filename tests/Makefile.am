AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

check_PYTHONdir = $(abs_top_builddir)

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_PYTHON_SCRIPTS = \
	pyscca_test_file.py \
	pyscca_test_support.py

check_PROGRAMS = \
	scca_test_compressed_block \
	scca_test_error \
	scca_test_file \
	scca_test_file_header \
	scca_test_file_information \
	scca_test_file_metrics \
	scca_test_filename_string \
	scca_test_filename_strings \
	scca_test_io_handle \
	scca_test_notify \
	scca_test_support \
	scca_test_tools_info_handle \
	scca_test_tools_output \
	scca_test_tools_path_string \
	scca_test_tools_signal \
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

scca_test_file_header_SOURCES = \
	scca_test_file_header.c \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_file_header_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

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

scca_test_filename_string_SOURCES = \
	scca_test_filename_string.c \
	scca_test_libcerror.h \
	scca_test_libscca.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_unused.h

scca_test_filename_string_LDADD = \
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

scca_test_tools_info_handle_SOURCES = \
	../sccatools/info_handle.c ../sccatools/info_handle.h \
	../sccatools/path_string.c ../sccatools/path_string.h \
	../sccatools/sccainput.c ../sccatools/sccainput.h \
	scca_test_libcerror.h \
	scca_test_macros.h \
	scca_test_memory.c scca_test_memory.h \
	scca_test_tools_info_handle.c \
	scca_test_unused.h

scca_test_tools_info_handle_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_tools_output_SOURCES = \
	../sccatools/sccatools_output.c ../sccatools/sccatools_output.h \
	scca_test_libcerror.h \
	scca_test_macros.h \
	scca_test_tools_output.c \
	scca_test_unused.h

scca_test_tools_output_LDADD = \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

scca_test_tools_path_string_SOURCES = \
	../sccatools/path_string.c ../sccatools/path_string.h \
	scca_test_libcerror.h \
	scca_test_libcpath.h \
	scca_test_macros.h \
	scca_test_tools_path_string.c \
	scca_test_unused.h

scca_test_tools_path_string_LDADD = \
	@LIBUNA_LIBADD@ \
	../libscca/libscca.la \
	@LIBCERROR_LIBADD@

scca_test_tools_signal_SOURCES = \
	../sccatools/sccatools_signal.c ../sccatools/sccatools_signal.h \
	scca_test_libcerror.h \
	scca_test_macros.h \
	scca_test_tools_signal.c \
	scca_test_unused.h

scca_test_tools_signal_LDADD = \
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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libscca.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libscca

test_inputs_pyscca.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyscca

test_inputs_sccainfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) sccainfo

test_library: package.m4 test_inputs_libscca.at test_library.at test_macros.at

test_manpages: package.m4 test_manpages.at

test_python_module: package.m4 test_inputs_pyscca.at test_python_module.at

test_tools: package.m4 test_macros.at test_inputs_sccainfo.at test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_PYTHON_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

