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

#if !defined( _PYSCCA_FILE_METRICS_H )
#define _PYSCCA_FILE_METRICS_H

#include <common.h>
#include <types.h>

#include "pyscca_libscca.h"
#include "pyscca_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyscca_file_metrics pyscca_file_metrics_t;

struct pyscca_file_metrics
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libscca file metrics
	 */
	libscca_file_metrics_t *file_metrics;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyscca_file_metrics_object_methods[];
extern PyTypeObject pyscca_file_metrics_type_object;

PyObject *pyscca_file_metrics_new(
           PyTypeObject *type_object,
           libscca_file_metrics_t *file_metrics,
           PyObject *parent_object );

int pyscca_file_metrics_init(
     pyscca_file_metrics_t *pyscca_file_metrics );

void pyscca_file_metrics_free(
      pyscca_file_metrics_t *pyscca_file_metrics );

PyObject *pyscca_file_metrics_get_filename(
           pyscca_file_metrics_t *pyscca_file_metrics,
           PyObject *arguments );

PyObject *pyscca_file_metrics_get_file_reference(
           pyscca_file_metrics_t *pyscca_file_metrics,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYSCCA_FILE_METRICS_H ) */

