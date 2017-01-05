/*
 * Python object definition of the sequence and iterator object of volumes
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

#include "pyscca_libcerror.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"
#include "pyscca_volume_information.h"
#include "pyscca_volumes.h"

PySequenceMethods pyscca_volumes_sequence_methods = {
	/* sq_length */
	(lenfunc) pyscca_volumes_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyscca_volumes_getitem,
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

PyTypeObject pyscca_volumes_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyscca._volumes",
	/* tp_basicsize */
	sizeof( pyscca_volumes_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyscca_volumes_free,
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
	&pyscca_volumes_sequence_methods,
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
	"pyscca internal sequence and iterator object of volumes",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyscca_volumes_iter,
	/* tp_iternext */
	(iternextfunc) pyscca_volumes_iternext,
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
	(initproc) pyscca_volumes_init,
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

/* Creates a new volumes object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyscca_volumes_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items )
{
	pyscca_volumes_t *volumes_object = NULL;
	static char *function            = "pyscca_volumes_new";

	if( parent_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid parent object.",
		 function );

		return( NULL );
	}
	if( get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get item by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the volumes values are initialized
	 */
	volumes_object = PyObject_New(
	                  struct pyscca_volumes,
	                  &pyscca_volumes_type_object );

	if( volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create volumes object.",
		 function );

		goto on_error;
	}
	if( pyscca_volumes_init(
	     volumes_object ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volumes object.",
		 function );

		goto on_error;
	}
	volumes_object->parent_object     = parent_object;
	volumes_object->get_item_by_index = get_item_by_index;
	volumes_object->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) volumes_object->parent_object );

	return( (PyObject *) volumes_object );

on_error:
	if( volumes_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) volumes_object );
	}
	return( NULL );
}

/* Intializes a volumes object
 * Returns 0 if successful or -1 on error
 */
int pyscca_volumes_init(
     pyscca_volumes_t *volumes_object )
{
	static char *function = "pyscca_volumes_init";

	if( volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object.",
		 function );

		return( -1 );
	}
	/* Make sure the volumes values are initialized
	 */
	volumes_object->parent_object     = NULL;
	volumes_object->get_item_by_index = NULL;
	volumes_object->current_index     = 0;
	volumes_object->number_of_items   = 0;

	return( 0 );
}

/* Frees a volumes object
 */
void pyscca_volumes_free(
      pyscca_volumes_t *volumes_object )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyscca_volumes_free";

	if( volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           volumes_object );

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
	if( volumes_object->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) volumes_object->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) volumes_object );
}

/* The volumes len() function
 */
Py_ssize_t pyscca_volumes_len(
            pyscca_volumes_t *volumes_object )
{
	static char *function = "pyscca_volumes_len";

	if( volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) volumes_object->number_of_items );
}

/* The volumes getitem() function
 */
PyObject *pyscca_volumes_getitem(
           pyscca_volumes_t *volumes_object,
           Py_ssize_t item_index )
{
	PyObject *volume_information_object = NULL;
	static char *function               = "pyscca_volumes_getitem";

	if( volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object.",
		 function );

		return( NULL );
	}
	if( volumes_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( volumes_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) volumes_object->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	volume_information_object = volumes_object->get_item_by_index(
	                             volumes_object->parent_object,
	                             (int) item_index );

	return( volume_information_object );
}

/* The volumes iter() function
 */
PyObject *pyscca_volumes_iter(
           pyscca_volumes_t *volumes_object )
{
	static char *function = "pyscca_volumes_iter";

	if( volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) volumes_object );

	return( (PyObject *) volumes_object );
}

/* The volumes iternext() function
 */
PyObject *pyscca_volumes_iternext(
           pyscca_volumes_t *volumes_object )
{
	PyObject *volume_information_object = NULL;
	static char *function               = "pyscca_volumes_iternext";

	if( volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object.",
		 function );

		return( NULL );
	}
	if( volumes_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( volumes_object->current_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object - invalid current index.",
		 function );

		return( NULL );
	}
	if( volumes_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volumes object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( volumes_object->current_index >= volumes_object->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	volume_information_object = volumes_object->get_item_by_index(
	                             volumes_object->parent_object,
	                             volumes_object->current_index );

	if( volume_information_object != NULL )
	{
		volumes_object->current_index++;
	}
	return( volume_information_object );
}

