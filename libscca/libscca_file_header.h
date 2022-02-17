/*
 * File header functions
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBSCCA_FILE_HEADER_H )
#define _LIBSCCA_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libscca_libbfio.h"
#include "libscca_libcerror.h"
#include "libscca_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_file_header libscca_file_header_t;

struct libscca_file_header
{
	/* The format version
	 */
	uint32_t format_version;

	/* The file size
	 */
	uint32_t file_size;

	/* The prefetch hash
	 */
	uint32_t prefetch_hash;

	/* The executable filename
	 */
	uint8_t executable_filename[ 60 ];

	/* The executable filename size
	 */
	size_t executable_filename_size;
};

int libscca_file_header_initialize(
     libscca_file_header_t **file_header,
     libcerror_error_t **error );

int libscca_file_header_free(
     libscca_file_header_t **file_header,
     libcerror_error_t **error );

int libscca_file_header_read_data(
     libscca_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libscca_file_header_read_data_stream(
     libscca_file_header_t *file_header,
     libfdata_stream_t *data_stream,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_FILE_HEADER_H ) */

