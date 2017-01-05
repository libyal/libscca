/*
 * Python object definition of the sequence and iterator object of filenames
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

#if !defined( _PYSCCA_FILENAMES_H )
#define _PYSCCA_FILENAMES_H

#include <common.h>
#include <types.h>

#include "pyscca_libscca.h"
#include "pyscca_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyscca_filenames pyscca_filenames_t;

struct pyscca_filenames
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyscca_filenames_type_object;

PyObject *pyscca_filenames_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyscca_filenames_init(
     pyscca_filenames_t *filenames_object );

void pyscca_filenames_free(
      pyscca_filenames_t *filenames_object );

Py_ssize_t pyscca_filenames_len(
            pyscca_filenames_t *filenames_object );

PyObject *pyscca_filenames_getitem(
           pyscca_filenames_t *filenames_object,
           Py_ssize_t item_index );

PyObject *pyscca_filenames_iter(
           pyscca_filenames_t *filenames_object );

PyObject *pyscca_filenames_iternext(
           pyscca_filenames_t *filenames_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYSCCA_FILENAMES_H ) */

