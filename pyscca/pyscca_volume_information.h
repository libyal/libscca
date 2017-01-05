/*
 * Python object wrapper of libscca_volume_information_t
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

#if !defined( _PYSCCA_VOLUME_INFORMATION_H )
#define _PYSCCA_VOLUME_INFORMATION_H

#include <common.h>
#include <types.h>

#include "pyscca_libscca.h"
#include "pyscca_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyscca_volume_information pyscca_volume_information_t;

struct pyscca_volume_information
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libscca volume information
	 */
	libscca_volume_information_t *volume_information;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyscca_volume_information_object_methods[];
extern PyTypeObject pyscca_volume_information_type_object;

PyObject *pyscca_volume_information_new(
           PyTypeObject *type_object,
           libscca_volume_information_t *volume_information,
           PyObject *parent_object );

int pyscca_volume_information_init(
     pyscca_volume_information_t *pyscca_volume_information );

void pyscca_volume_information_free(
      pyscca_volume_information_t *pyscca_volume_information );

PyObject *pyscca_volume_information_get_creation_time(
           pyscca_volume_information_t *pyscca_volume_information,
           PyObject *arguments );

PyObject *pyscca_volume_information_get_creation_time_as_integer(
           pyscca_volume_information_t *pyscca_volume_information,
           PyObject *arguments );

PyObject *pyscca_volume_information_get_serial_number(
           pyscca_volume_information_t *pyscca_volume_information,
           PyObject *arguments );

PyObject *pyscca_volume_information_get_device_path(
           pyscca_volume_information_t *pyscca_volume_information,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYSCCA_VOLUME_INFORMATION_H ) */

