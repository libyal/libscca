/*
 * Filename strings functions
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

#if !defined( _LIBSCCA_FILENAME_STRINGS_H )
#define _LIBSCCA_FILENAME_STRINGS_H

#include <common.h>
#include <types.h>

#include "libscca_libbfio.h"
#include "libscca_libcdata.h"
#include "libscca_libcerror.h"
#include "libscca_libfdata.h"
#include "libscca_libfvalue.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_filename_strings libscca_filename_strings_t;

struct libscca_filename_strings
{
	/* The offsets array
	 */
	libcdata_array_t *offsets_array;

	/* The filenames strings value
	 */
	libfvalue_value_t *strings;
};

int libscca_filename_string_offset_free(
     uint32_t **filename_string_offset,
     libcerror_error_t **error );

int libscca_filename_strings_initialize(
     libscca_filename_strings_t **filename_strings,
     libcerror_error_t **error );

int libscca_filename_strings_free(
     libscca_filename_strings_t **filename_strings,
     libcerror_error_t **error );

int libscca_filename_strings_clear(
     libscca_filename_strings_t *filename_strings,
     libcerror_error_t **error );

int libscca_filename_strings_read(
     libscca_filename_strings_t *filename_strings,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t filename_strings_offset,
     uint32_t filename_strings_size,
     libcerror_error_t **error );

int libscca_filename_strings_get_index_by_offset(
     libscca_filename_strings_t *filename_strings,
     uint32_t filename_offset,
     int *filename_index,
     libcerror_error_t **error );

int libscca_filename_strings_get_number_of_filenames(
     libscca_filename_strings_t *filename_strings,
     int *number_of_filenames,
     libcerror_error_t **error );

int libscca_filename_strings_get_utf8_filename_size(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libscca_filename_strings_get_utf8_filename(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libscca_filename_strings_get_utf16_filename_size(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libscca_filename_strings_get_utf16_filename(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_FILENAME_STRINGS_H ) */

