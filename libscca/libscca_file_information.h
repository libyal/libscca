/*
 * File information functions
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

#if !defined( _LIBSCCA_FILE_INFORMATION_H )
#define _LIBSCCA_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#include "libscca_io_handle.h"
#include "libscca_libbfio.h"
#include "libscca_libcerror.h"
#include "libscca_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_file_information libscca_file_information_t;

struct libscca_file_information
{
	/* The offset of the metrics array
	 */
	uint32_t metrics_array_offset;

	/* The number of file metrics array entries
	 */
	uint32_t number_of_file_metrics_entries;

	/* The offset of the trace chain array
	 */
	uint32_t trace_chain_array_offset;

	/* The number of trace chain array entries
	 */
	uint32_t number_of_trace_chain_array_entries;

	/* The filename strings offset
	 */
	uint32_t filename_strings_offset;

	/* The filename strings size
	 */
	uint32_t filename_strings_size;

	/* The volumes information offset
	 */
	uint32_t volumes_information_offset;

	/* The number of volumes
	 */
	uint32_t number_of_volumes;

	/* The volumes information size
	 */
	uint32_t volumes_information_size;

	/* The last run time
	 */
	uint64_t last_run_time[ 8 ];

	/* The run count
	 */
	uint32_t run_count;
};

int libscca_file_information_initialize(
     libscca_file_information_t **file_information,
     libcerror_error_t **error );

int libscca_file_information_free(
     libscca_file_information_t **file_information,
     libcerror_error_t **error );

int libscca_file_information_read(
     libscca_file_information_t *file_information,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     libscca_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_FILE_INFORMATION_H ) */

