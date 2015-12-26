/*
 * File metrics functions
 *
 * Copyright (C) 2011-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include "libscca_libcerror.h"
#include "libscca_libfvalue.h"
#include "libscca_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_internal_file_metrics libscca_internal_file_metrics_t;

struct libscca_internal_file_metrics
{
	/* The start time
	 */
	uint32_t start_time;

	/* The duration
	 */
	uint32_t duration;

	/* The offset of the filename string
	 */
	uint32_t filename_string_offset;

	/* The flags
	 */
	uint32_t flags;

	/* The NTFS file reference
	 */
	uint64_t file_reference;
};

int libscca_file_metrics_initialize(
     libscca_internal_file_metrics_t **file_metrics,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_free(
     libscca_file_metrics_t **file_metrics,
     libcerror_error_t **error );

int libscca_internal_file_metrics_free(
     libscca_internal_file_metrics_t **file_metrics,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_metrics_get_file_reference(
     libscca_file_metrics_t *file_metrics,
     uint64_t *file_reference,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

