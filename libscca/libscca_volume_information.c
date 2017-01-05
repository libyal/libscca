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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libscca_definitions.h"
#include "libscca_libcerror.h"
#include "libscca_libfvalue.h"
#include "libscca_libuna.h"
#include "libscca_volume_information.h"

/* Creates volume information
 * Make sure the value volume_information is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_initialize(
     libscca_volume_information_t **volume_information,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libscca_volume_information_initialize";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	if( *volume_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume information value already set.",
		 function );

		return( -1 );
	}
	internal_volume_information = memory_allocate_structure(
	                               libscca_internal_volume_information_t );

	if( internal_volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volume information.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_volume_information,
	     0,
	     sizeof( libscca_internal_volume_information_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear volume information.",
		 function );

		goto on_error;
	}
	*volume_information = (libscca_volume_information_t *) internal_volume_information;

	return( 1 );

on_error:
	if( internal_volume_information != NULL )
	{
		memory_free(
		 internal_volume_information );
	}
	return( -1 );
}

/* Frees volume information
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_free(
     libscca_volume_information_t **volume_information,
     libcerror_error_t **error )
{
	static char *function = "libscca_volume_information_free";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	if( *volume_information != NULL )
	{
		*volume_information = NULL;
	}
	return( 1 );
}

/* Frees volume information
 * Returns 1 if successful or -1 on error
 */
int libscca_internal_volume_information_free(
     libscca_internal_volume_information_t **internal_volume_information,
     libcerror_error_t **error )
{
	static char *function = "libscca_volume_information_free";
	int result            = 1;

	if( internal_volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	if( *internal_volume_information != NULL )
	{
		if( ( *internal_volume_information )->device_path != NULL )
		{
			memory_free(
			 ( *internal_volume_information )->device_path );
		}
		if( ( *internal_volume_information )->directory_strings != NULL )
		{
			if( libfvalue_value_free(
			     &( ( *internal_volume_information )->directory_strings ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory strings.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 ( *internal_volume_information ) );

		*internal_volume_information = NULL;
	}
	return( result );
}

/* Retrieves the 64-bit FILETIME value containing the volume creation date and time
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_get_creation_time(
     libscca_volume_information_t *volume_information,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libscca_volume_information_get_creation_time";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libscca_internal_volume_information_t *) volume_information;

	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = internal_volume_information->creation_time;

	return( 1 );
}

/* Retrieves the serial number
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_get_serial_number(
     libscca_volume_information_t *volume_information,
     uint32_t *serial_number,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libscca_volume_information_get_serial_number";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libscca_internal_volume_information_t *) volume_information;

	if( serial_number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid serial number.",
		 function );

		return( -1 );
	}
	*serial_number = internal_volume_information->serial_number;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded device path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_get_utf8_device_path_size(
     libscca_volume_information_t *volume_information,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libscca_volume_information_get_utf8_device_path_size";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libscca_internal_volume_information_t *) volume_information;

	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve device path UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded device path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_get_utf8_device_path(
     libscca_volume_information_t *volume_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libscca_volume_information_get_utf8_device_path";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libscca_internal_volume_information_t *) volume_information;

	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy device path to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded device path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_get_utf16_device_path_size(
     libscca_volume_information_t *volume_information,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libscca_volume_information_get_utf16_device_path_size";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libscca_internal_volume_information_t *) volume_information;

	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve device path UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded device path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_volume_information_get_utf16_device_path(
     libscca_volume_information_t *volume_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libscca_volume_information_get_utf16_device_path";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libscca_internal_volume_information_t *) volume_information;

	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy device path to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

