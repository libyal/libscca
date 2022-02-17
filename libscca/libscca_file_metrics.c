/*
 * File metrics functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libscca_definitions.h"
#include "libscca_file_metrics.h"
#include "libscca_libcerror.h"
#include "libscca_libcnotify.h"
#include "libscca_libuna.h"

#include "scca_file_metrics_array.h"

/* Creates file metrics
 * Make sure the value file_metrics is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_initialize(
     libscca_file_metrics_t **file_metrics,
     libscca_filename_strings_t *filename_strings,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *internal_file_metrics = NULL;
	static char *function                                  = "libscca_file_metrics_initialize";

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
	internal_file_metrics = memory_allocate_structure(
	                         libscca_internal_file_metrics_t );

	if( internal_file_metrics == NULL )
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
	     internal_file_metrics,
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
		 internal_file_metrics );

		return( -1 );
	}
	internal_file_metrics->filename_strings = filename_strings;

	*file_metrics = (libscca_file_metrics_t *) internal_file_metrics;

	return( 1 );

on_error:
	if( internal_file_metrics != NULL )
	{
		memory_free(
		 internal_file_metrics );
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

/* Reads file metrics from data
 * Returns 1 if successful or -1 on error
 */
int libscca_file_metrics_read_data(
     libscca_file_metrics_t *file_metrics,
     libscca_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *internal_file_metrics = NULL;
	static char *function                                  = "libscca_file_metrics_read_data";
	size_t file_metrics_data_size                          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                                   = 0;
#endif

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

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->format_version == 17 )
	{
		file_metrics_data_size = sizeof( scca_file_metrics_array_entry_v17_t );
	}
	else if( ( io_handle->format_version == 23 )
	      || ( io_handle->format_version == 26 )
	      || ( io_handle->format_version == 30 ) )
	{
		file_metrics_data_size = sizeof( scca_file_metrics_array_entry_v23_t );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < file_metrics_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file metrics data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 file_metrics_data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_metrics_array_entry_v17_t *) data )->start_time,
	 internal_file_metrics->start_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_metrics_array_entry_v17_t *) data )->duration,
	 internal_file_metrics->duration );

	if( io_handle->format_version == 17 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_metrics_array_entry_v17_t *) data )->filename_string_offset,
		 internal_file_metrics->filename_string_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_metrics_array_entry_v17_t *) data )->flags,
		 internal_file_metrics->flags );
	}
	else if( ( io_handle->format_version == 23 )
	      || ( io_handle->format_version == 26 )
	      || ( io_handle->format_version == 30 ) )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_metrics_array_entry_v23_t *) data )->filename_string_offset,
		 internal_file_metrics->filename_string_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_metrics_array_entry_v23_t *) data )->flags,
		 internal_file_metrics->flags );

		byte_stream_copy_to_uint64_little_endian(
		 ( (scca_file_metrics_array_entry_v23_t *) data )->file_reference,
		 internal_file_metrics->file_reference );

		internal_file_metrics->file_reference_is_set = 1;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: start time\t\t\t\t: %" PRIu32 " ms\n",
		 function,
		 internal_file_metrics->start_time );

		libcnotify_printf(
		 "%s: duration\t\t\t\t: %" PRIu32 " ms\n",
		 function,
		 internal_file_metrics->duration );

		if( ( io_handle->format_version == 23 )
		 || ( io_handle->format_version == 26 )
		 || ( io_handle->format_version == 30 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_metrics_array_entry_v23_t *) data )->average_duration,
			 value_32bit );
			libcnotify_printf(
			 "%s: average duration\t\t\t: %" PRIu32 " ms\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: filename string offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_file_metrics->filename_string_offset );

		if( io_handle->format_version == 17 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_metrics_array_entry_v17_t *) data )->filename_string_numbers_of_characters,
			 value_32bit );
		}
		else if( ( io_handle->format_version == 23 )
		      || ( io_handle->format_version == 26 )
		      || ( io_handle->format_version == 30 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_metrics_array_entry_v23_t *) data )->filename_string_numbers_of_characters,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: filename string number of characters\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: flags\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_file_metrics->flags );

		if( internal_file_metrics->file_reference_is_set != 0 )
		{
			if( internal_file_metrics->file_reference == 0 )
			{
				libcnotify_printf(
				 "%s: file reference\t\t\t\t: %" PRIu64 "\n",
				 function,
				 internal_file_metrics->file_reference );
			}
			else
			{
				libcnotify_printf(
				 "%s: file reference\t\t\t\t: MFT entry: %" PRIu64 ", sequence: %" PRIu64 "\n",
				 function,
				 internal_file_metrics->file_reference & 0xffffffffffffUL,
				 internal_file_metrics->file_reference >> 48 );
			}
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

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

/* Retrieves the file reference
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

