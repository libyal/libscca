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

#if !defined( _PYSCCA_FILENAMES_H )
#define _PYSCCA_STRINGS_H

#include <common.h>
#include <types.h>

#include "pyscca_file.h"
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

	/* The file object
	 */
	pyscca_file_t *file_object;

	/* The get filename by index callback function
	 */
	PyObject* (*get_filename_by_index)(
	             pyscca_file_t *file_object,
	             int filename_index );

	/* The (current) filename index
	 */
	int filename_index;

	/* The number of filenames
	 */
	int number_of_filenames;
};

extern PyTypeObject pyscca_filenames_type_object;

PyObject *pyscca_filenames_new(
           pyscca_file_t *file_object,
           PyObject* (*get_filename_by_index)(
                        pyscca_file_t *file_object,
                        int filename_index ),
           int number_of_filenames );

int pyscca_filenames_init(
     pyscca_filenames_t *pyscca_filenames );

void pyscca_filenames_free(
      pyscca_filenames_t *pyscca_filenames );

Py_ssize_t pyscca_filenames_len(
            pyscca_filenames_t *pyscca_filenames );

PyObject *pyscca_filenames_getitem(
           pyscca_filenames_t *pyscca_filenames,
           Py_ssize_t item_index );

PyObject *pyscca_filenames_iter(
           pyscca_filenames_t *pyscca_filenames );

PyObject *pyscca_filenames_iternext(
           pyscca_filenames_t *pyscca_filenames );

#if defined( __cplusplus )
}
#endif

#endif

