if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

pyexec_LTLIBRARIES = pyscca.la

pyscca_la_SOURCES = \
	pyscca.c pyscca.h \
	pyscca_datetime.c pyscca_datetime.h \
	pyscca_error.c pyscca_error.h \
	pyscca_file.c pyscca_file.h \
	pyscca_file_object_io_handle.c pyscca_file_object_io_handle.h \
	pyscca_integer.c pyscca_integer.h \
	pyscca_libbfio.h \
	pyscca_libcerror.h \
	pyscca_libclocale.h \
	pyscca_libcstring.h \
	pyscca_libscca.h \
	pyscca_python.h \
	pyscca_unused.h \
	pyscca_volume_information.c pyscca_volume_information.h

pyscca_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libscca/libscca.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyscca_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyscca_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

EXTRA_DIST = \
	setup.py \
	setup.py.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f setup.py
	/bin/rm -f Makefile

