# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

am_pyscca_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
	pyscca.c pyscca.h \
	pyscca_datetime.c pyscca_datetime.h \
	pyscca_error.c pyscca_error.h \
	pyscca_file.c pyscca_file.h \
	pyscca_file_metrics.c pyscca_file_metrics.h \
	pyscca_file_metrics_entries.c pyscca_file_metrics_entries.h \
	pyscca_file_object_io_handle.c pyscca_file_object_io_handle.h \
	pyscca_filenames.c pyscca_filenames.h \
	pyscca_integer.c pyscca_integer.h \
	pyscca_libbfio.h \
	pyscca_libcerror.h \
	pyscca_libclocale.h \
	pyscca_libscca.h \
	pyscca_python.h \
	pyscca_unused.h \
	pyscca_volume_information.c pyscca_volume_information.h \
	pyscca_volumes.c pyscca_volumes.h

pyexec_LTLIBRARIES = pyscca.la

nodist_pyscca_la_SOURCES = $(BUILT_SOURCES)

pyscca_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libscca/libscca.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyscca_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyscca_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyscca/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyscca*.[ch]

distclean: clean
	/bin/rm -f Makefile

