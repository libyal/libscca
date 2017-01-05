/*
 * Volume information functions
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

#if !defined( _LIBSCCA_INTERNAL_VOLUME_INFORMATION_H )
#define _LIBSCCA_INTERNAL_VOLUME_INFORMATION_H

#include <common.h>
#include <types.h>

#include "libscca_extern.h"
#include "libscca_libcerror.h"
#include "libscca_libfvalue.h"
#include "libscca_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_internal_volume_information libscca_internal_volume_information_t;

struct libscca_internal_volume_information
{
	/* The volume device path
	 */
	uint8_t *device_path;

	/* The volume device path size
	 */
	uint32_t device_path_size;

	/* The volume creation time
	 */
	uint64_t creation_time;

	/* The volume serial number
	 */
	uint32_t serial_number;

	/* The directory strings
	 */
	libfvalue_value_t *directory_strings;
};

int libscca_volume_information_initialize(
     libscca_volume_information_t **volume_information,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_volume_information_free(
     libscca_volume_information_t **volume_information,
     libcerror_error_t **error );

int libscca_internal_volume_information_free(
     libscca_internal_volume_information_t **internal_volume_information,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_volume_information_get_creation_time(
     libscca_volume_information_t *volume_information,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_volume_information_get_serial_number(
     libscca_volume_information_t *volume_information,
     uint32_t *serial_number,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_volume_information_get_utf8_device_path_size(
     libscca_volume_information_t *volume_information,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_volume_information_get_utf8_device_path(
     libscca_volume_information_t *volume_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_volume_information_get_utf16_device_path_size(
     libscca_volume_information_t *volume_information,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_volume_information_get_utf16_device_path(
     libscca_volume_information_t *volume_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_INTERNAL_VOLUME_INFORMATION_H ) */

