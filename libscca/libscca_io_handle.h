/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2011-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBSCCA_IO_HANDLE_H )
#define _LIBSCCA_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libscca_libbfio.h"
#include "libscca_libcdata.h"
#include "libscca_libcerror.h"
#include "libscca_libfvalue.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *scca_file_signature;

typedef struct libscca_io_handle libscca_io_handle_t;

struct libscca_io_handle
{
	/* The format version
	 */
	uint32_t format_version;

	/* The file size
	 */
	uint32_t file_size;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libscca_io_handle_initialize(
     libscca_io_handle_t **io_handle,
     libcerror_error_t **error );

int libscca_io_handle_free(
     libscca_io_handle_t **io_handle,
     libcerror_error_t **error );

int libscca_io_handle_clear(
     libscca_io_handle_t *io_handle,
     libcerror_error_t **error );

int libscca_io_handle_read_file_header(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *prefetch_hash,
     libcerror_error_t **error );

int libscca_io_handle_read_metrics_array(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t file_offset,
     uint32_t number_of_entries,
     libcerror_error_t **error );

int libscca_io_handle_read_trace_chain_array(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t file_offset,
     uint32_t number_of_entries,
     libcerror_error_t **error );

int libscca_io_handle_read_filename_strings(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t filename_string_offset,
     uint32_t filename_string_size,
     libfvalue_value_t *filename_strings,
     libcerror_error_t **error );

int libscca_io_handle_read_volumes_information(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t volumes_information_offset,
     uint32_t volumes_information_size,
     uint32_t number_of_volumes,
     libcdata_array_t *volumes_array,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

