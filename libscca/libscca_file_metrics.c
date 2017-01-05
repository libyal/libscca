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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libscca_definitions.h"
#include "libscca_file_metrics.h"
#include "libscca_libcerror.h"
#include "libscca_libuna.h"

/* Creates file metrics
 * Make sure the value file_metrics is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_initialize(
     libscca_internal_file_metrics_t **file_metrics,
     libscca_filename_strings_t *filename_strings,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_metrics_initialize";

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	if( *file_metrics != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file metrics value already set.",
		 function );

		return( -1 );
	}
	if( filename_strings == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename strings.",
		 function );

		return( -1 );
	}
	*file_metrics = memory_allocate_structure(
	                 libscca_internal_file_metrics_t );

	if( *file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file metrics.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_metrics,
	     0,
	     sizeof( libscca_internal_file_metrics_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file metrics.",
		 function );

		memory_free(
		 *file_metrics );

		*file_metrics = NULL;

		return( -1 );
	}
	( *file_metrics )->filename_strings = filename_strings;

	return( 1 );

on_error:
	if( *file_metrics != NULL )
	{
		memory_free(
		 *file_metrics );

		*file_metrics = NULL;
	}
	return( -1 );
}

/* Frees file metrics
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_free(
     libscca_file_metrics_t **file_metrics,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_metrics_free";

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	if( *file_metrics != NULL )
	{
		*file_metrics = NULL;
	}
	return( 1 );
}

/* Frees file metrics
 * Returns 1 if successful or -1 on error
 */
int libscca_internal_file_metrics_free(
     libscca_internal_file_metrics_t **file_metrics,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_metrics_free";

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	if( *file_metrics != NULL )
	{
		memory_free(
		 ( *file_metrics ) );

		*file_metrics = NULL;
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_get_utf8_filename_size(
     libscca_file_metrics_t *file_metrics,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *internal_file_metrics = NULL;
	static char *function                                  = "libscca_file_metrics_get_utf8_filename_size";
	int filename_index                                     = 0;

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	internal_file_metrics = (libscca_internal_file_metrics_t *) file_metrics;

	if( libscca_filename_strings_get_index_by_offset(
	     internal_file_metrics->filename_strings,
	     internal_file_metrics->filename_string_offset,
	     &filename_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve index for offset: 0x%08" PRIx32 "",
		 function,
		 internal_file_metrics->filename_string_offset );

		return( -1 );
	}
	if( libscca_filename_strings_get_utf8_filename_size(
	     internal_file_metrics->filename_strings,
	     filename_index,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename: %d UTF-8 string size.",
		 function,
		 filename_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_get_utf8_filename(
     libscca_file_metrics_t *file_metrics,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *internal_file_metrics = NULL;
	static char *function                                  = "libscca_file_metrics_get_utf8_filename";
	int filename_index                                     = 0;

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	internal_file_metrics = (libscca_internal_file_metrics_t *) file_metrics;

	if( libscca_filename_strings_get_index_by_offset(
	     internal_file_metrics->filename_strings,
	     internal_file_metrics->filename_string_offset,
	     &filename_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve index for offset: 0x%08" PRIx32 "",
		 function,
		 internal_file_metrics->filename_string_offset );

		return( -1 );
	}
	if( libscca_filename_strings_get_utf8_filename(
	     internal_file_metrics->filename_strings,
	     filename_index,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filename: %d to UTF-8 string.",
		 function,
		 filename_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_get_utf16_filename_size(
     libscca_file_metrics_t *file_metrics,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *internal_file_metrics = NULL;
	static char *function                                  = "libscca_file_metrics_get_utf16_filename_size";
	int filename_index                                     = 0;

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	internal_file_metrics = (libscca_internal_file_metrics_t *) file_metrics;

	if( libscca_filename_strings_get_index_by_offset(
	     internal_file_metrics->filename_strings,
	     internal_file_metrics->filename_string_offset,
	     &filename_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve index for offset: 0x%08" PRIx32 "",
		 function,
		 internal_file_metrics->filename_string_offset );

		return( -1 );
	}
	if( libscca_filename_strings_get_utf16_filename_size(
	     internal_file_metrics->filename_strings,
	     filename_index,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename: %d UTF-16 string size.",
		 function,
		 filename_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_get_utf16_filename(
     libscca_file_metrics_t *file_metrics,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *internal_file_metrics = NULL;
	static char *function                                  = "libscca_file_metrics_get_utf16_filename";
	int filename_index                                     = 0;

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	internal_file_metrics = (libscca_internal_file_metrics_t *) file_metrics;

	if( libscca_filename_strings_get_index_by_offset(
	     internal_file_metrics->filename_strings,
	     internal_file_metrics->filename_string_offset,
	     &filename_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve index for offset: 0x%08" PRIx32 "",
		 function,
		 internal_file_metrics->filename_string_offset );

		return( -1 );
	}
	if( libscca_filename_strings_get_utf16_filename(
	     internal_file_metrics->filename_strings,
	     filename_index,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filename: %d to UTF-16 string.",
		 function,
		 filename_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the NTFS file reference
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libscca_file_metrics_get_file_reference(
     libscca_file_metrics_t *file_metrics,
     uint64_t *file_reference,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *internal_file_metrics = NULL;
	static char *function                                  = "libscca_file_metrics_get_file_reference";

	if( file_metrics == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file metrics.",
		 function );

		return( -1 );
	}
	internal_file_metrics = (libscca_internal_file_metrics_t *) file_metrics;

	if( file_reference == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file reference.",
		 function );

		return( -1 );
	}
	if( internal_file_metrics->file_reference_is_set == 0 )
	{
		return( 0 );
	}
	*file_reference = internal_file_metrics->file_reference;

	return( 1 );
}

