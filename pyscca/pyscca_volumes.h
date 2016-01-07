/*
 * Python object definition of the volumes sequence and iterator
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

#if !defined( _PYSCCA_VOLUMES_H )
#define _PYSCCA_VOLUMES_H

#include <common.h>
#include <types.h>

#include "pyscca_file.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyscca_volumes pyscca_volumes_t;

struct pyscca_volumes
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The file object
	 */
	pyscca_file_t *file_object;

	/* The get volume information by index callback function
	 */
	PyObject* (*get_volume_information_by_index)(
	             pyscca_file_t *file_object,
	             int volume_index );

	/* The (current) volume index
	 */
	int volume_index;

	/* The number of volumes
	 */
	int number_of_volumes;
};

extern PyTypeObject pyscca_volumes_type_object;

PyObject *pyscca_volumes_new(
           pyscca_file_t *file_object,
           PyObject* (*get_volume_information_by_index)(
                        pyscca_file_t *file_object,
                        int volume_index ),
           int number_of_volumes );

int pyscca_volumes_init(
     pyscca_volumes_t *pyscca_volumes );

void pyscca_volumes_free(
      pyscca_volumes_t *pyscca_volumes );

Py_ssize_t pyscca_volumes_len(
            pyscca_volumes_t *pyscca_volumes );

PyObject *pyscca_volumes_getitem(
           pyscca_volumes_t *pyscca_volumes,
           Py_ssize_t item_index );

PyObject *pyscca_volumes_iter(
           pyscca_volumes_t *pyscca_volumes );

PyObject *pyscca_volumes_iternext(
           pyscca_volumes_t *pyscca_volumes );

#if defined( __cplusplus )
}
#endif

#endif

