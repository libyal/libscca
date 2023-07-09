/*
 * Filename string functions
 *
 * Copyright (C) 2011-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBSCCA_FILENAME_STRING_H )
#define _LIBSCCA_FILENAME_STRING_H

#include <common.h>
#include <types.h>

#include "libscca_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_filename_string libscca_filename_string_t;

struct libscca_filename_string
{
	/* The offset
	 */
	uint32_t offset;

	/* The (string) data
	 */
	const uint8_t *data;

	/* The (string) data size
	 */
	size_t data_size;
};

int libscca_filename_string_initialize(
     libscca_filename_string_t **filename_string,
     uint32_t offset,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libscca_filename_string_free(
     libscca_filename_string_t **filename_string,
     libcerror_error_t **error );

int libscca_filename_string_get_utf8_string_size(
     libscca_filename_string_t *filename_string,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libscca_filename_string_get_utf8_string(
     libscca_filename_string_t *filename_string,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libscca_filename_string_get_utf16_string_size(
     libscca_filename_string_t *filename_string,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libscca_filename_string_get_utf16_string(
     libscca_filename_string_t *filename_string,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_FILENAME_STRING_H ) */

