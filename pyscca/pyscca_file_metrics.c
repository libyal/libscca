/*
 * Python object wrapper of libscca_file_metrics_t
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

#include "pyscca_error.h"
#include "pyscca_file_metrics.h"
#include "pyscca_integer.h"
#include "pyscca_libcerror.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"
#include "pyscca_unused.h"

PyMethodDef pyscca_file_metrics_object_methods[] = {

	{ "get_filename",
	  (PyCFunction) pyscca_file_metrics_get_filename,
	  METH_NOARGS,
	  "get_filename() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the filename." },

	{ "get_file_reference",
	  (PyCFunction) pyscca_file_metrics_get_file_reference,
	  METH_NOARGS,
	  "get_file_reference() -> Integer or None\n"
	  "\n"
	  "Retrieves the file reference." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyscca_file_metrics_object_get_set_definitions[] = {

	{ "filename",
	  (getter) pyscca_file_metrics_get_filename,
	  (setter) 0,
	  "The filename.",
	  NULL },

	{ "file_reference",
	  (getter) pyscca_file_metrics_get_file_reference,
	  (setter) 0,
	  "The file reference.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyscca_file_metrics_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyscca.file_metrics",
	/* tp_basicsize */
	sizeof( pyscca_file_metrics_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyscca_file_metrics_free,
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
	"pyscca file metrics object (wraps libscca_file_metrics_t)",
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
	pyscca_file_metrics_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyscca_file_metrics_object_get_set_definitions,
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
	(initproc) pyscca_file_metrics_init,
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

/* Creates a new file metrics object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_metrics_new(
           PyTypeObject *type_object,
           libscca_file_metrics_t *file_metrics,
           PyObject *parent_object )
{
	pyscca_file_metrics_t *pyscca_file_metrics = NULL;
	static char *function                      = "pyscca_file_metrics_new";

	if( file_metrics == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics.",
		 function );

		return( NULL );
	}
	pyscca_file_metrics = PyObject_New(
	                       struct pyscca_file_metrics,
	                       type_object );

	if( pyscca_file_metrics == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file metrics.",
		 function );

		goto on_error;
	}
	if( pyscca_file_metrics_init(
	     pyscca_file_metrics ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file metrics.",
		 function );

		goto on_error;
	}
	pyscca_file_metrics->file_metrics  = file_metrics;
	pyscca_file_metrics->parent_object = parent_object;

	Py_IncRef(
	 (PyObject *) pyscca_file_metrics->parent_object );

	return( (PyObject *) pyscca_file_metrics );

on_error:
	if( pyscca_file_metrics != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyscca_file_metrics );
	}
	return( NULL );
}

/* Intializes a file metrics object
 * Returns 0 if successful or -1 on error
 */
int pyscca_file_metrics_init(
     pyscca_file_metrics_t *pyscca_file_metrics )
{
	static char *function = "pyscca_file_metrics_init";

	if( pyscca_file_metrics == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	/* Make sure libscca file metrics is set to NULL
	 */
	pyscca_file_metrics->file_metrics = NULL;

	return( 0 );
}

/* Frees a file metrics object
 */
void pyscca_file_metrics_free(
      pyscca_file_metrics_t *pyscca_file_metrics )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyscca_file_metrics_free";
	int result                  = 0;

	if( pyscca_file_metrics == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics.",
		 function );

		return;
	}
	if( pyscca_file_metrics->file_metrics == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics - missing libscca file metrics.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyscca_file_metrics );

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

	result = libscca_file_metrics_free(
	          &( pyscca_file_metrics->file_metrics ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libscca file metrics.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyscca_file_metrics->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyscca_file_metrics->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyscca_file_metrics );
}

/* Retrieves the filename
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_metrics_get_filename(
           pyscca_file_metrics_t *pyscca_file_metrics,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pyscca_file_metrics_get_filename";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file_metrics == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_metrics_get_utf8_filename_size(
	          pyscca_file_metrics->file_metrics,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of filename as UTF-8 string.",
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

	result = libscca_file_metrics_get_utf8_filename(
	          pyscca_file_metrics->file_metrics,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename as UTF-8 string.",
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

/* Retrieves the file reference
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_metrics_get_file_reference(
           pyscca_file_metrics_t *pyscca_file_metrics,
           PyObject *arguments PYSCCA_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyscca_file_metrics_get_file_reference";
	uint64_t value_64bit     = 0;
	int result               = 0;

	PYSCCA_UNREFERENCED_PARAMETER( arguments )

	if( pyscca_file_metrics == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libscca_file_metrics_get_file_reference(
	          pyscca_file_metrics->file_metrics,
	          &value_64bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyscca_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file reference.",
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
	integer_object = pyscca_integer_unsigned_new_from_64bit(
	                  (uint64_t) value_64bit );

	return( integer_object );
}

