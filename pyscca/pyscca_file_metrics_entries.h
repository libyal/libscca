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

#if !defined( _PYSCCA_FILE_METRIC_ENTRIES_H )
#define _PYSCCA_FILE_METRIC_ENTRIES_H

#include <common.h>
#include <types.h>

#include "pyscca_file.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyscca_file_metrics_entries pyscca_file_metrics_entries_t;

struct pyscca_file_metrics_entries
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The file object
	 */
	pyscca_file_t *file_object;

	/* The get file metrics entry by index callback function
	 */
	PyObject* (*get_file_metrics_entry_by_index)(
	             pyscca_file_t *file_object,
	             int entry_index );

	/* The (current) entry index
	 */
	int entry_index;

	/* The number of file metrics entries
	 */
	int number_of_entries;
};

extern PyTypeObject pyscca_file_metrics_entries_type_object;

PyObject *pyscca_file_metrics_entries_new(
           pyscca_file_t *file_object,
           PyObject* (*get_file_metrics_entry_by_index)(
                        pyscca_file_t *file_object,
                        int entry_index ),
           int number_of_entries );

int pyscca_file_metrics_entries_init(
     pyscca_file_metrics_entries_t *pyscca_file_metrics_entries );

void pyscca_file_metrics_entries_free(
      pyscca_file_metrics_entries_t *pyscca_file_metrics_entries );

Py_ssize_t pyscca_file_metrics_entries_len(
            pyscca_file_metrics_entries_t *pyscca_file_metrics_entries );

PyObject *pyscca_file_metrics_entries_getitem(
           pyscca_file_metrics_entries_t *pyscca_file_metrics_entries,
           Py_ssize_t item_index );

PyObject *pyscca_file_metrics_entries_iter(
           pyscca_file_metrics_entries_t *pyscca_file_metrics_entries );

PyObject *pyscca_file_metrics_entries_iternext(
           pyscca_file_metrics_entries_t *pyscca_file_metrics_entries );

#if defined( __cplusplus )
}
#endif

#endif

