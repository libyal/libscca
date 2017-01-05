/*
 * Python object wrapper of libscca_file_t
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyscca_datetime.h"
#include "pyscca_error.h"
#include "pyscca_file.h"
#include "pyscca_file_metrics.h"
#include "pyscca_file_metrics_entries.h"
#include "pyscca_file_object_io_handle.h"
#include "pyscca_filenames.h"
#include "pyscca_integer.h"
#include "pyscca_libbfio.h"
#include "pyscca_libcerror.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"
#include "pyscca_unused.h"
#include "pyscca_volume_information.h"
#include "pyscca_volumes.h"

#if !defined( LIBSCCA_HAVE_BFIO )

LIBSCCA_EXTERN \
int libscca_file_open_file_io_handle(
     libscca_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libscca_error_t **error );

#endif /* !defined( LIBSCCA_HAVE_BFIO ) */

PyMethodDef pyscca_file_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyscca_file_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the file to abort the current activity." },

	{ "open",
	  (PyCFunction) pyscca_file_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pyscca_file_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a file using a file-like object." },

	{ "close",
	  (PyCFunction) pyscca_file_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a file." },

	{ "get_format_version",
	  (PyCFunction) pyscca_file_get_format_version,
	  METH_NOARGS,
	  "get_format_version() -> Integer or None\n"
	  "\n"
	  "Retrieves the format version." },

	{ "get_executable_filename",
	  (PyCFunction) pyscca_file_get_executable_filename,
	  METH_NOARGS,
	  "get_executable_filename() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the executable filename." },

	{ "get_prefetch_hash",
	  (PyCFunction) pyscca_file_get_prefetch_hash,
	  METH_NOARGS,
	  "get_prefetch_hash() -> Integer or None\n"
	  "\n"
	  "Retrieves the prefetch hash." },

	{ "get_last_run_time",
	  (PyCFunction) pyscca_file_get_last_run_time,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_last_run_time(last_run_time_index) -> Datetime or None\n"
	  "\n"
	  "Retrieves the last run time specified by the index." },

	{ "get_last_run_time_as_integer",
	  (PyCFunction) pyscca_file_get_last_run_time_as_integer,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_last_run_time_as_integer(last_run_time_index) -> Integer or None\n"
	  "\n"
	  "Retrieves the last run time specified by the index as a 64-bit integer containing a FILETIME value." },

	{ "get_run_count",
	  (PyCFunction) pyscca_file_get_run_count,
	  METH_NOARGS,
	  "get_run_count() -> Integer or None\n"
	  "\n"
	  "Retrieves the run count." },

	{ "get_number_of_file_metrics_entries",
	  (PyCFunction) pyscca_file_get_number_of_file_metrics_entries,
	  METH_NOARGS,
	  "get_number_of_file_metrics_entries() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of file metrics entries." },

	{ "get_file_metrics_entry",
	  (PyCFunction) pyscca_file_get_file_metrics_entry,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_file_metrics_entry(entry_index) -> Object or None\n"
	  "\n"
	  "Retrieves the file metrics entry specified by the index." },

	{ "get_number_of_filenames",
	  (PyCFunction) pyscca_file_get_number_of_filenames,
	  METH_NOARGS,
	  "get_number_of_filenames() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of filenames." },

	{ "get_filename",
	  (PyCFunction) pyscca_file_get_filename,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_filename(filename_index) -> Unicode string or None\n"
	  "\n"
	  "Retrieves the filename specified by the index." },

	{ "get_number_of_volumes",
	  (PyCFunction) pyscca_file_get_number_of_volumes,
	  METH_NOARGS,
	  "get_number_of_volumes() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of volumes." },

	{ "get_volume_information",
	  (PyCFunction) pyscca_file_get_volume_information,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_volume_information(volume_index) -> Object or None\n"
	  "\n"
	  "Retrieves the volume information specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyscca_file_object_get_set_definitions[] = {

	{ "format_version",
	  (getter) pyscca_file_get_format_version,
	  (setter) 0,
	  "The format version.",
	  NULL },

	{ "executable_filename",
	  (getter) pyscca_file_get_executable_filename,
	  (setter) 0,
	  "The executable filename.",
	  NULL },

	{ "prefetch_hash",
	  (getter) pyscca_file_get_prefetch_hash,
	  (setter) 0,
	  "The prefetch hash.",
	  NULL },

	{ "run_count",
	  (getter) pyscca_file_get_run_count,
	  (setter) 0,
	  "The run count.",
	  NULL },

	{ "number_of_file_metrics_entries",
	  (getter) pyscca_file_get_number_of_file_metrics_entries,
	  (setter) 0,
	  "The number of file metrics entries.",
	  NULL },

	{ "file_metrics_entries",
	  (getter) pyscca_file_get_file_metrics_entries,
	  (setter) 0,
	  "The file metrics entries.",
	  NULL },

	{ "number_of_filenames",
	  (getter) pyscca_file_get_number_of_filenames,
	  (setter) 0,
	  "The number of filenames.",
	  NULL },

	{ "filenames",
	  (getter) pyscca_file_get_filenames,
	  (setter) 0,
	  "The filenames.",
	  NULL },

	{ "number_of_volumes",
	  (getter) pyscca_file_get_number_of_volumes,
	  (setter) 0,
	  "The number of volumes.",
	  NULL },

	{ "volumes",
	  (getter) pyscca_file_get_volumes,
	  (setter) 0,
	  "The volumes.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyscca_file_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyscca.file",
	/* tp_basicsize */
	sizeof( pyscca_file_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyscca_file_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyscca file object (wraps libscca_file_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyscca_file_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyscca_file_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyscca_file_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new file object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_new(
           void )
{
	pyscca_file_t *pyscca_file = NULL;
	static char *function      = "pyscca_file_new";

	pyscca_file = PyObject_New(
	               struct pyscca_file,
	               &pyscca_file_type_object );

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	if( pyscca_file_init(
	     pyscca_file ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pyscca_file );

on_error:
	if( pyscca_file != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyscca_file );
	}
	return( NULL );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_new_open(
           PyObject *self PYSCCA_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyscca_file = NULL;

	PYSCCA_UNREFERENCED_PARAMETER( self )

	pyscca_file = pyscca_file_new();

	pyscca_file_open(
	 (pyscca_file_t *) pyscca_file,
	 arguments,
	 keywords );

	return( pyscca_file );
}

/* Creates a new file object and opens it using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_new_open_file_object(
           PyObject *self PYSCCA_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyscca_file = NULL;

	PYSCCA_UNREFERENCED_PARAMETER( self )

	pyscca_file = pyscca_file_new();

	pyscca_file_open_file_object(
	 (pyscca_file_t *) pyscca_file,
	 arguments,
	 keywords );

	return( pyscca_file );
}

/* Intializes a file object
 * Returns 0 if successful or -1 on error
 */
int pyscca_file_init(
     pyscca_file_t *pyscca_file )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_init";

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	pyscca_file->file           = NULL;
	pyscca_file->file_io_handle = NULL;

	if( libscca_file_initialize(
	     &( pyscca_file->file ),
	     &error ) != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a file object
 */
void pyscca_file_free(
      pyscca_file_t *pyscca_file )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyscca_file_free";
	int result                  = 0;

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return;
	}
	if( pyscca_file->file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - missing libscca file.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyscca_file );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_free(
	          &( pyscca_file->file ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free libscca file.",
		 function );

		libcerror_error_free(
		 &error );
	}
	ob_type->tp_free(
	 (PyObject*) pyscca_file );
}

/* Signals the file to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_signal_abort(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_signal_abort";
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_signal_abort(
	          pyscca_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_open(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	const char *filename_narrow  = NULL;
	static char *function        = "pyscca_file_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyscca_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libscca_file_open_wide(
		          pyscca_file->file,
		          filename_wide,
		          LIBSCCA_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyscca_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libscca_file_open(
		          pyscca_file->file,
		          filename_narrow,
		          LIBSCCA_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pyscca_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyscca_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libscca_file_open(
		          pyscca_file->file,
		          filename_narrow,
		          LIBSCCA_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyscca_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a file using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_open_file_object(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyscca_file_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
	int result                  = 0;

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	if( pyscca_file->file_io_handle != NULL )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid file - file IO handle already set.",
		 function );

		goto on_error;
	}
	if( pyscca_file_object_initialize(
	     &( pyscca_file->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_open_file_io_handle(
	          pyscca_file->file,
	          pyscca_file->file_io_handle,
	          LIBSCCA_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open file.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyscca_file->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pyscca_file->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_close(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_close";
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_close(
	          pyscca_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close file.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pyscca_file->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pyscca_file->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyscca_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the format version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_format_version(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_get_format_version";
	uint32_t format_version  = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_format_version(
	          pyscca_file->file,
	          &format_version,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve format version.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) format_version );

	return( integer_object );
}

/* Retrieves the executable filename
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_executable_filename(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pyscca_file_get_executable_filename";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_utf8_executable_filename_size(
	          pyscca_file->file,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of executable filename as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_utf8_executable_filename(
	          pyscca_file->file,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve executable filename as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

/* Retrieves the prefetch hash
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_prefetch_hash(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_get_prefetch_hash";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_prefetch_hash(
	          pyscca_file->file,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve prefetch hash.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the last run date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_last_run_time(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	PyObject *date_time_object  = NULL;
	static char *function       = "pyscca_file_get_last_run_time";
	static char *keyword_list[] = { "last_run_time_index", NULL };
	uint64_t filetime           = 0;
	int last_run_time_index     = 0;
	int result                  = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &last_run_time_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_last_run_time(
	          pyscca_file->file,
	          last_run_time_index,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve last run time: %d.",
		 function,
		 last_run_time_index );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pyscca_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the last run date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_last_run_time_as_integer(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	PyObject *integer_object    = NULL;
	static char *function       = "pyscca_file_get_last_run_time_as_integer";
	static char *keyword_list[] = { "last_run_time_index", NULL };
	uint64_t filetime           = 0;
	int last_run_time_index     = 0;
	int result                  = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &last_run_time_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_last_run_time(
	          pyscca_file->file,
	          last_run_time_index,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve last run time: %d.",
		 function,
		 last_run_time_index );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyscca_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the run count
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_run_count(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_get_run_count";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_run_count(
	          pyscca_file->file,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve run count.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the number of file metrics entries
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_number_of_file_metrics_entries(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object           = NULL;
	libcerror_error_t *error           = NULL;
	static char *function              = "pyscca_file_get_number_of_file_metrics_entries";
	int number_of_file_metrics_entries = 0;
	int result                         = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_number_of_file_metrics_entries(
	          pyscca_file->file,
	          &number_of_file_metrics_entries,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of file metrics entries.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_file_metrics_entries );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_file_metrics_entries );
#endif
	return( integer_object );
}

/* Retrieves a specific file metrics entry by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_file_metrics_entry_by_index(
           PyObject *pyscca_file,
           int entry_index )
{
	PyObject *file_metrics_entry_object        = NULL;
	libcerror_error_t *error                   = NULL;
	libscca_file_metrics_t *file_metrics_entry = NULL;
	static char *function                      = "pyscca_file_get_file_metrics_entry_by_index";
	int result                                 = 0;

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_file_metrics_entry(
	          ( (pyscca_file_t *) pyscca_file )->file,
	          entry_index,
	          &file_metrics_entry,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file metrics entry: %d.",
		 function,
		 entry_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	file_metrics_entry_object = pyscca_file_metrics_new(
	                             &pyscca_file_metrics_type_object,
	                             file_metrics_entry,
	                             (PyObject *) pyscca_file );

	if( file_metrics_entry_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create file metrics object.",
		 function );

		goto on_error;
	}
	return( file_metrics_entry_object );

on_error:
	if( file_metrics_entry != NULL )
	{
		libscca_file_metrics_free(
		 &file_metrics_entry,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific file metrics entry
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_file_metrics_entry(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_metrics_entry_object = NULL;
	static char *keyword_list[]         = { "entry_index", NULL };
	int entry_index        = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &entry_index ) == 0 )
	{
		return( NULL );
	}
	file_metrics_entry_object = pyscca_file_get_file_metrics_entry_by_index(
	                             (PyObject *) pyscca_file,
	                             entry_index );

	return( file_metrics_entry_object );
}

/* Retrieves a sequence and iterator object for the file metrics entries
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_file_metrics_entries(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object          = NULL;
	libcerror_error_t *error           = NULL;
	static char *function              = "pyscca_file_get_file_metrics_entries";
	int number_of_file_metrics_entries = 0;
	int result                         = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_number_of_file_metrics_entries(
	          pyscca_file->file,
	          &number_of_file_metrics_entries,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of file metrics entries.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyscca_file_metrics_entries_new(
	                   (PyObject *) pyscca_file,
	                   &pyscca_file_get_file_metrics_entry_by_index,
	                   number_of_file_metrics_entries );

	if( sequence_object == NULL )
	{
		pyscca_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

/* Retrieves the number of filenames
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_number_of_filenames(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_get_number_of_filenames";
	int number_of_filenames  = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_number_of_filenames(
	          pyscca_file->file,
	          &number_of_filenames,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of filenames.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_filenames );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_filenames );
#endif
	return( integer_object );
}

/* Retrieves a specific filename by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_filename_by_index(
           PyObject *pyscca_file,
           int filename_index )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	uint8_t *utf8_string     = NULL;
	const char *errors       = NULL;
	static char *function    = "pyscca_file_get_filename_by_index";
	size_t utf8_string_size  = 0;
	int result               = 0;

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_utf8_filename_size(
	          ( (pyscca_file_t *) pyscca_file )->file,
	          filename_index,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of filename: %d as UTF-8 string.",
		 function,
		 filename_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (uint8_t *) PyMem_Malloc(
	                           sizeof( uint8_t ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_utf8_filename(
	          ( (pyscca_file_t *) pyscca_file )->file,
	          filename_index,
	          utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename: %d as UTF-8 string.",
		 function,
		 filename_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 (char *) utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

/* Retrieves a specific filename
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_filename(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	static char *keyword_list[] = { "filename_index", NULL };
	int filename_index          = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &filename_index ) == 0 )
	{
		return( NULL );
	}
	string_object = pyscca_file_get_filename_by_index(
	                 (PyObject *) pyscca_file,
	                 filename_index );

	return( string_object );
}

/* Retrieves a sequence and iterator object for the filenames
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_filenames(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyscca_file_get_filenames";
	int number_of_filenames   = 0;
	int result                = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_number_of_filenames(
	          pyscca_file->file,
	          &number_of_filenames,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of filenames.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyscca_filenames_new(
	                   (PyObject *) pyscca_file,
	                   &pyscca_file_get_filename_by_index,
	                   number_of_filenames );

	if( sequence_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

/* Retrieves the number of volumes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_number_of_volumes(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_get_number_of_volumes";
	int number_of_volumes    = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_number_of_volumes(
	          pyscca_file->file,
	          &number_of_volumes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of volumes.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_volumes );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_volumes );
#endif
	return( integer_object );
}

/* Retrieves a specific volume information by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_volume_information_by_index(
           PyObject *pyscca_file,
           int volume_index )
{
	PyObject *volume_information_object              = NULL;
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	static char *function                            = "pyscca_file_get_volume_information_by_index";
	int result                                       = 0;

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_volume_information(
	          ( (pyscca_file_t *) pyscca_file )->file,
	          volume_index,
	          &volume_information,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve volume information: %d.",
		 function,
		 volume_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	volume_information_object = pyscca_volume_information_new(
	                             &pyscca_volume_information_type_object,
	                             volume_information,
	                             (PyObject *) pyscca_file );

	if( volume_information_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create volume information object.",
		 function );

		goto on_error;
	}
	return( volume_information_object );

on_error:
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific volume information
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_volume_information(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *volume_information_object = NULL;
	static char *keyword_list[]         = { "volume_index", NULL };
	int volume_index                    = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &volume_index ) == 0 )
	{
		return( NULL );
	}
	volume_information_object = pyscca_file_get_volume_information_by_index(
	                             (PyObject *) pyscca_file,
	                             volume_index );

	return( volume_information_object );
}

/* Retrieves a sequence and iterator object for the volumes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_volumes(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyscca_file_get_volumes";
	int number_of_volumes     = 0;
	int result                = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_number_of_volumes(
	          pyscca_file->file,
	          &number_of_volumes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of volumes.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyscca_volumes_new(
	                   (PyObject *) pyscca_file,
	                   &pyscca_file_get_volume_information_by_index,
	                   number_of_volumes );

	if( sequence_object == NULL )
	{
		pyscca_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

