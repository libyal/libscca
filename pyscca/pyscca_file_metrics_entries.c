/*
 * Python object definition of the file metrics entries sequence and iterator
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyscca_file.h"
#include "pyscca_file_metrics.h"
#include "pyscca_file_metrics_entries.h"
#include "pyscca_libcerror.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"

PySequenceMethods pyscca_file_metrics_entries_sequence_methods = {
	/* sq_length */
	(lenfunc) pyscca_file_metrics_entries_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyscca_file_metrics_entries_getitem,
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

PyTypeObject pyscca_file_metrics_entries_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyscca._file_metrics_entries",
	/* tp_basicsize */
	sizeof( pyscca_file_metrics_entries_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyscca_file_metrics_entries_free,
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
	&pyscca_file_metrics_entries_sequence_methods,
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
	"internal pyscca file metrics entries sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyscca_file_metrics_entries_iter,
	/* tp_iternext */
	(iternextfunc) pyscca_file_metrics_entries_iternext,
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
	(initproc) pyscca_file_metrics_entries_init,
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

/* Creates a new file metrics entries object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_file_metrics_entries_new(
           pyscca_file_t *file_object,
           PyObject* (*get_file_metrics_entry_by_index)(
                        pyscca_file_t *file_object,
                        int entry_index ),
           int number_of_entries )
{
	pyscca_file_metrics_entries_t *pyscca_file_metrics_entries = NULL;
	static char *function                                      = "pyscca_file_metrics_entries_new";

	if( file_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file object.",
		 function );

		return( NULL );
	}
	if( get_file_metrics_entry_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get file metrics entry by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the file metrics entries values are initialized
	 */
	pyscca_file_metrics_entries = PyObject_New(
	                               struct pyscca_file_metrics_entries,
	                               &pyscca_file_metrics_entries_type_object );

	if( pyscca_file_metrics_entries == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file metrics entries.",
		 function );

		goto on_error;
	}
	if( pyscca_file_metrics_entries_init(
	     pyscca_file_metrics_entries ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file metrics entries.",
		 function );

		goto on_error;
	}
	pyscca_file_metrics_entries->file_object                     = file_object;
	pyscca_file_metrics_entries->get_file_metrics_entry_by_index = get_file_metrics_entry_by_index;
	pyscca_file_metrics_entries->number_of_entries               = number_of_entries;

	Py_IncRef(
	 (PyObject *) pyscca_file_metrics_entries->file_object );

	return( (PyObject *) pyscca_file_metrics_entries );

on_error:
	if( pyscca_file_metrics_entries != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyscca_file_metrics_entries );
	}
	return( NULL );
}

/* Intializes a file metrics entries object
 * Returns 0 if successful or -1 on error
 */
int pyscca_file_metrics_entries_init(
     pyscca_file_metrics_entries_t *pyscca_file_metrics_entries )
{
	static char *function = "pyscca_file_metrics_entries_init";

	if( pyscca_file_metrics_entries == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries.",
		 function );

		return( -1 );
	}
	/* Make sure the file metrics entries values are initialized
	 */
	pyscca_file_metrics_entries->file_object                     = NULL;
	pyscca_file_metrics_entries->get_file_metrics_entry_by_index = NULL;
	pyscca_file_metrics_entries->entry_index                     = 0;
	pyscca_file_metrics_entries->number_of_entries               = 0;

	return( 0 );
}

/* Frees a file metrics entries object
 */
void pyscca_file_metrics_entries_free(
      pyscca_file_metrics_entries_t *pyscca_file_metrics_entries )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyscca_file_metrics_entries_free";

	if( pyscca_file_metrics_entries == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyscca_file_metrics_entries );

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
	if( pyscca_file_metrics_entries->file_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyscca_file_metrics_entries->file_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyscca_file_metrics_entries );
}

/* The file metrics entries len() function
 */
Py_ssize_t pyscca_file_metrics_entries_len(
            pyscca_file_metrics_entries_t *pyscca_file_metrics_entries )
{
	static char *function = "pyscca_file_metrics_entries_len";

	if( pyscca_file_metrics_entries == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyscca_file_metrics_entries->number_of_entries );
}

/* The file metrics entries getitem() function
 */
PyObject *pyscca_file_metrics_entries_getitem(
           pyscca_file_metrics_entries_t *pyscca_file_metrics_entries,
           Py_ssize_t item_index )
{
	PyObject *file_metrics_object = NULL;
	static char *function         = "pyscca_file_metrics_entries_getitem";

	if( pyscca_file_metrics_entries == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries.",
		 function );

		return( NULL );
	}
	if( pyscca_file_metrics_entries->get_file_metrics_entry_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries - missing get file metrics entry by index function.",
		 function );

		return( NULL );
	}
	if( pyscca_file_metrics_entries->number_of_entries < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries - invalid number of entries.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyscca_file_metrics_entries->number_of_entries ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	file_metrics_object = pyscca_file_metrics_entries->get_file_metrics_entry_by_index(
	                       pyscca_file_metrics_entries->file_object,
	                       (int) item_index );

	return( file_metrics_object );
}

/* The file metrics entries iter() function
 */
PyObject *pyscca_file_metrics_entries_iter(
           pyscca_file_metrics_entries_t *pyscca_file_metrics_entries )
{
	static char *function = "pyscca_file_metrics_entries_iter";

	if( pyscca_file_metrics_entries == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyscca_file_metrics_entries );

	return( (PyObject *) pyscca_file_metrics_entries );
}

/* The file_metrics_entries iternext() function
 */
PyObject *pyscca_file_metrics_entries_iternext(
           pyscca_file_metrics_entries_t *pyscca_file_metrics_entries )
{
	PyObject *file_metrics_object = NULL;
	static char *function         = "pyscca_file_metrics_entries_iternext";

	if( pyscca_file_metrics_entries == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries.",
		 function );

		return( NULL );
	}
	if( pyscca_file_metrics_entries->get_file_metrics_entry_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries - missing get file metrics entry information by index function.",
		 function );

		return( NULL );
	}
	if( pyscca_file_metrics_entries->entry_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries - invalid entry index.",
		 function );

		return( NULL );
	}
	if( pyscca_file_metrics_entries->number_of_entries < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file metrics entries - invalid number of entries.",
		 function );

		return( NULL );
	}
	if( pyscca_file_metrics_entries->entry_index >= pyscca_file_metrics_entries->number_of_entries )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	file_metrics_object = pyscca_file_metrics_entries->get_file_metrics_entry_by_index(
	                       pyscca_file_metrics_entries->file_object,
	                       pyscca_file_metrics_entries->entry_index );

	if( file_metrics_object != NULL )
	{
		pyscca_file_metrics_entries->entry_index++;
	}
	return( file_metrics_object );
}

