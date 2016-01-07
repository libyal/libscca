/*
 * Python object definition of the filenames sequence and iterator
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyscca_file.h"
#include "pyscca_filenames.h"
#include "pyscca_libcerror.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"

PySequenceMethods pyscca_filenames_sequence_methods = {
	/* sq_length */
	(lenfunc) pyscca_filenames_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyscca_filenames_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pyscca_filenames_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyscca._filenames",
	/* tp_basicsize */
	sizeof( pyscca_filenames_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyscca_filenames_free,
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
	&pyscca_filenames_sequence_methods,
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
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"internal pyscca filenames sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyscca_filenames_iter,
	/* tp_iternext */
	(iternextfunc) pyscca_filenames_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
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
	(initproc) pyscca_filenames_init,
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

/* Creates a new filenames object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_filenames_new(
           pyscca_file_t *file_object,
           PyObject* (*get_filename_by_index)(
                        pyscca_file_t *file_object,
                        int filename_index ),
           int number_of_filenames )
{
	pyscca_filenames_t *pyscca_filenames = NULL;
	static char *function                = "pyscca_filenames_new";

	if( file_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file object.",
		 function );

		return( NULL );
	}
	if( get_filename_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get filename by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the filenames values are initialized
	 */
	pyscca_filenames = PyObject_New(
	                    struct pyscca_filenames,
	                    &pyscca_filenames_type_object );

	if( pyscca_filenames == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize filenames.",
		 function );

		goto on_error;
	}
	if( pyscca_filenames_init(
	     pyscca_filenames ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize filenames.",
		 function );

		goto on_error;
	}
	pyscca_filenames->file_object           = file_object;
	pyscca_filenames->get_filename_by_index = get_filename_by_index;
	pyscca_filenames->number_of_filenames   = number_of_filenames;

	Py_IncRef(
	 (PyObject *) pyscca_filenames->file_object );

	return( (PyObject *) pyscca_filenames );

on_error:
	if( pyscca_filenames != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyscca_filenames );
	}
	return( NULL );
}

/* Intializes a filenames object
 * Returns 0 if successful or -1 on error
 */
int pyscca_filenames_init(
     pyscca_filenames_t *pyscca_filenames )
{
	static char *function = "pyscca_filenames_init";

	if( pyscca_filenames == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames.",
		 function );

		return( -1 );
	}
	/* Make sure the filenames values are initialized
	 */
	pyscca_filenames->file_object           = NULL;
	pyscca_filenames->get_filename_by_index = NULL;
	pyscca_filenames->filename_index        = 0;
	pyscca_filenames->number_of_filenames   = 0;

	return( 0 );
}

/* Frees a filenames object
 */
void pyscca_filenames_free(
      pyscca_filenames_t *pyscca_filenames )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyscca_filenames_free";

	if( pyscca_filenames == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyscca_filenames );

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
	if( pyscca_filenames->file_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyscca_filenames->file_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyscca_filenames );
}

/* The filenames len() function
 */
Py_ssize_t pyscca_filenames_len(
            pyscca_filenames_t *pyscca_filenames )
{
	static char *function = "pyscca_filenames_len";

	if( pyscca_filenames == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyscca_filenames->number_of_filenames );
}

/* The filenames getitem() function
 */
PyObject *pyscca_filenames_getitem(
           pyscca_filenames_t *pyscca_filenames,
           Py_ssize_t item_index )
{
	PyObject *filename_object = NULL;
	static char *function     = "pyscca_filenames_getitem";

	if( pyscca_filenames == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames.",
		 function );

		return( NULL );
	}
	if( pyscca_filenames->get_filename_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames - missing get filename by index function.",
		 function );

		return( NULL );
	}
	if( pyscca_filenames->number_of_filenames < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames - invalid number of filenames.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyscca_filenames->number_of_filenames ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	filename_object = pyscca_filenames->get_filename_by_index(
	                   pyscca_filenames->file_object,
	                   (int) item_index );

	return( filename_object );
}

/* The filenames iter() function
 */
PyObject *pyscca_filenames_iter(
           pyscca_filenames_t *pyscca_filenames )
{
	static char *function = "pyscca_filenames_iter";

	if( pyscca_filenames == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyscca_filenames );

	return( (PyObject *) pyscca_filenames );
}

/* The filenames iternext() function
 */
PyObject *pyscca_filenames_iternext(
           pyscca_filenames_t *pyscca_filenames )
{
	PyObject *filename_object = NULL;
	static char *function     = "pyscca_filenames_iternext";

	if( pyscca_filenames == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames.",
		 function );

		return( NULL );
	}
	if( pyscca_filenames->get_filename_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames - missing get filename by index function.",
		 function );

		return( NULL );
	}
	if( pyscca_filenames->filename_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames - invalid filename index.",
		 function );

		return( NULL );
	}
	if( pyscca_filenames->number_of_filenames < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid filenames - invalid number of filenames.",
		 function );

		return( NULL );
	}
	if( pyscca_filenames->filename_index >= pyscca_filenames->number_of_filenames )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	filename_object = pyscca_filenames->get_filename_by_index(
	                   pyscca_filenames->file_object,
	                   pyscca_filenames->filename_index );

	if( filename_object != NULL )
	{
		pyscca_filenames->filename_index++;
	}
	return( filename_object );
}

