/*
 * File metrics functions
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

#if !defined( _LIBSCCA_INTERNAL_FILE_METRICS_H )
#define _LIBSCCA_INTERNAL_FILE_METRICS_H

#include <common.h>
#include <types.h>

#include "libscca_extern.h"
#include "libscca_filename_strings.h"
#include "libscca_libcerror.h"
#include "libscca_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_internal_file_metrics libscca_internal_file_metrics_t;

struct libscca_internal_file_metrics
{
	/* The filename strings
	 */
	libscca_filename_strings_t *filename_strings;

	/* The start time
	 */
	uint32_t start_time;

	/* The duration
	 */
	uint32_t duration;

	/* The filename string offset
	 */
	uint32_t filename_string_offset;

	/* The flags
	 */
	uint32_t flags;

	/* The NTFS file reference
	 */
	uint64_t file_reference;

	/* Value to indicate the file reference was set
	 */
	uint8_t file_reference_is_set;
};

int libscca_file_metrics_initialize(
     libscca_internal_file_metrics_t **file_metrics,
     libscca_filename_strings_t *filename_strings,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_free(
     libscca_file_metrics_t **file_metrics,
     libcerror_error_t **error );

int libscca_internal_file_metrics_free(
     libscca_internal_file_metrics_t **file_metrics,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf8_filename_size(
     libscca_file_metrics_t *file_metrics,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf8_filename(
     libscca_file_metrics_t *file_metrics,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf16_filename_size(
     libscca_file_metrics_t *file_metrics,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf16_filename(
     libscca_file_metrics_t *file_metrics,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_get_file_reference(
     libscca_file_metrics_t *file_metrics,
     uint64_t *file_reference,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_INTERNAL_FILE_METRICS_H ) */

