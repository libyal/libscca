/*
 * Python object wrapper of libscca_file_t
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

#if !defined( _PYSCCA_FILE_H )
#define _PYSCCA_FILE_H

#include <common.h>
#include <types.h>

#include "pyscca_libbfio.h"
#include "pyscca_libscca.h"
#include "pyscca_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyscca_file pyscca_file_t;

struct pyscca_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libscca file
	 */
	libscca_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyscca_file_object_methods[];
extern PyTypeObject pyscca_file_type_object;

PyObject *pyscca_file_new(
           void );

PyObject *pyscca_file_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pyscca_file_init(
     pyscca_file_t *pyscca_file );

void pyscca_file_free(
      pyscca_file_t *pyscca_file );

PyObject *pyscca_file_signal_abort(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_open(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_open_file_object(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_close(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_format_version(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_executable_filename(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_prefetch_hash(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_last_run_time(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_get_last_run_time_as_integer(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_get_run_count(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_number_of_file_metrics_entries(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_file_metrics_entry_by_index(
           PyObject *pyscca_file,
           int entry_index );

PyObject *pyscca_file_get_file_metrics_entry(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_get_file_metrics_entries(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_number_of_filenames(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_filename_by_index(
           PyObject *pyscca_file,
           int filename_index );

PyObject *pyscca_file_get_filename(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_get_filenames(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_number_of_volumes(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

PyObject *pyscca_file_get_volume_information_by_index(
           PyObject *pyscca_file,
           int volume_index );

PyObject *pyscca_file_get_volume_information(
           pyscca_file_t *pyscca_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyscca_file_get_volumes(
           pyscca_file_t *pyscca_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYSCCA_FILE_H ) */

