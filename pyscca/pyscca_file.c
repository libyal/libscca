/*
 * Python object definition of the libscca file
 *
 * Copyright (C) 2011-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include "pyscca_file_object_io_handle.h"
#include "pyscca_filenames.h"
#include "pyscca_integer.h"
#include "pyscca_libbfio.h"
#include "pyscca_libcerror.h"
#include "pyscca_libclocale.h"
#include "pyscca_libcstring.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"
#include "pyscca_unused.h"

#if !defined( LIBSCCA_HAVE_BFIO )
LIBSCCA_EXTERN \
int libscca_file_open_file_io_handle(
     libscca_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libscca_error_t **error );
#endif

PyMethodDef pyscca_file_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyscca_file_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the file to abort the current activity." },

	/* Functions to access the file */

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

	/* Functions to access the metadata */

	{ "get_format_version",
	  (PyCFunction) pyscca_file_get_format_version,
	  METH_NOARGS,
	  "get_format_version() -> Integer\n"
	  "\n"
	  "Retrieves the format version" },

	{ "get_prefetch_hash",
	  (PyCFunction) pyscca_file_get_prefetch_hash,
	  METH_NOARGS,
	  "get_prefetch_hash() -> Integer\n"
	  "\n"
	  "Retrieves the prefetch hash" },

	/* Functions to access the filenames */

	{ "get_number_of_filenames",
	  (PyCFunction) pyscca_file_get_number_of_filenames,
	  METH_NOARGS,
	  "get_number_of_filenames() -> Integer\n"
	  "\n"
	  "Retrieves the number of filenames" },

	/* Functions to access the volumes */

	{ "get_number_of_volumes",
	  (PyCFunction) pyscca_file_get_number_of_volumes,
	  METH_NOARGS,
	  "get_number_of_volumes() -> Integer\n"
	  "\n"
	  "Retrieves the number of volumes" },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyscca_file_object_get_set_definitions[] = {

	{ "format_version",
	  (getter) pyscca_file_get_format_version,
	  (setter) 0,
	  "The format version",
	  NULL },

	{ "prefetch_hash",
	  (getter) pyscca_file_get_prefetch_hash,
	  (setter) 0,
	  "The prefetch hash",
	  NULL },

	{ "number_of_filenames",
	  (getter) pyscca_file_get_number_of_filenames,
	  (setter) 0,
	  "The number of filenames",
	  NULL },

	{ "number_of_volumes",
	  (getter) pyscca_file_get_number_of_volumes,
	  (setter) 0,
	  "The number of volumes",
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
	static char *function    = "pyscca_file_new";

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

/* Creates a new file object and opens it
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
	static char *function    = "pyscca_file_init";
	libcerror_error_t *error = NULL;

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
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
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
	static char *function        = "pyscca_file_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	const char *filename_narrow  = NULL;
	char *mode                   = NULL;
	int result                   = 0;

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
	char *mode                  = NULL;
	static char *keyword_list[] = { "file_object", "mode", NULL };
	static char *function       = "pyscca_file_open_file_object";
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
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_get_format_version";
	uint32_t format_version  = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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
	return( PyLong_FromUnsignedLong(
	         (unsigned long) format_version ) );
}

/* Retrieves the prefetch hash
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_prefetch_hash(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_get_prefetch_hash";
	uint32_t prefetch_hash   = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_prefetch_hash(
	          pyscca_file->file,
	          &prefetch_hash,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
	return( PyLong_FromUnsignedLong(
	         (unsigned long) prefetch_hash ) );
}

/* Retrieves the number of filenames
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_number_of_filenames(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyscca_file_get_number_of_filenames";
	int number_of_filenames  = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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
           pyscca_file_t *pyscca_file,
           int filename_index )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	uint8_t *filename        = NULL;
	const char *errors       = NULL;
	static char *function    = "pyscca_file_get_filename_by_index";
	size_t filename_size     = 0;
	int result               = 0;

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_utf8_filename_size(
	          pyscca_file->file,
	          filename_index,
	          &filename_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename: %d size.",
		 function,
		 filename_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( filename_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	filename = (uint8_t *) PyMem_Malloc(
	                        sizeof( uint8_t ) * filename_size );

	if( filename == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create filename: %d.",
		 function,
		 filename_index );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_get_utf8_filename(
		  pyscca_file->file,
		  filename_index,
		  filename,
		  filename_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename: %d.",
		 function,
		 filename_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) filename,
			 (Py_ssize_t) filename_size - 1,
			 errors );

	PyMem_Free(
	 filename );

	return( string_object );

on_error:
	if( filename != NULL )
	{
		PyMem_Free(
		 filename );
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
	                 pyscca_file,
	                 filename_index );

	return( string_object );
}

/* Retrieves a filenames sequence and iterator object for the filenames
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_filenames(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *filenames_object = NULL;
	static char *function      = "pyscca_file_get_filenames";
	int number_of_filenames    = 0;
	int result                 = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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
	filenames_object = pyscca_filenames_new(
	                    pyscca_file,
	                    &pyscca_file_get_filename_by_index,
	                    number_of_filenames );

	if( filenames_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create filenames object.",
		 function );

		return( NULL );
	}
	return( filenames_object );
}

/* Retrieves the number of volumes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_get_number_of_volumes(
           pyscca_file_t *pyscca_file,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyscca_file_get_number_of_volumes";
	int number_of_volumes    = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
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

