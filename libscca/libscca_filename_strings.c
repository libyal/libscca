/*
 * Filename strings functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libscca_definitions.h"
#include "libscca_filename_string.h"
#include "libscca_filename_strings.h"
#include "libscca_libbfio.h"
#include "libscca_libcdata.h"
#include "libscca_libcerror.h"
#include "libscca_libcnotify.h"
#include "libscca_libfdata.h"

/* Creates filename strings
 * Make sure the value filename_strings is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_initialize(
     libscca_filename_strings_t **filename_strings,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_strings_initialize";

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
	if( *filename_strings != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid filename strings value already set.",
		 function );

		return( -1 );
	}
	*filename_strings = memory_allocate_structure(
	                     libscca_filename_strings_t );

	if( *filename_strings == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create filename strings.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *filename_strings,
	     0,
	     sizeof( libscca_filename_strings_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		memory_free(
		 *filename_strings );

		*filename_strings = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *filename_strings )->strings_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create strings array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *filename_strings != NULL )
	{
		memory_free(
		 *filename_strings );

		*filename_strings = NULL;
	}
	return( -1 );
}

/* Frees filename strings
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_free(
     libscca_filename_strings_t **filename_strings,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_strings_free";
	int result            = 1;

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
	if( *filename_strings != NULL )
	{
		if( libcdata_array_free(
		     &( ( *filename_strings )->strings_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libscca_filename_string_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free strings array.",
			 function );

			result = -1;
		}
		if( ( *filename_strings )->data != NULL )
		{
			memory_free(
			 ( *filename_strings )->data );
		}
		memory_free(
		 *filename_strings );

		*filename_strings = NULL;
	}
	return( result );
}

/* Clears the filename strings
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_clear(
     libscca_filename_strings_t *filename_strings,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_strings_clear";
	int result            = 1;

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
	if( libcdata_array_empty(
	     filename_strings->strings_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libscca_filename_string_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty strings array.",
		 function );

		result = -1;
	}
	if( filename_strings->data != NULL )
	{
		memory_free(
		 filename_strings->data );

		filename_strings->data = NULL;
	}
	filename_strings->data_size = 0;

	return( result );
}

/* Reads the filename strings
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_read_data(
     libscca_filename_strings_t *filename_strings,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libscca_filename_string_t *filename_string = NULL;
	static char *function                      = "libscca_filename_strings_read_data";
	size_t data_offset                         = 0;
	size_t filename_string_size                = 0;
	size_t last_data_offset                    = 0;
	int entry_index                            = 0;
	int filename_strings_index                 = 0;

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
	if( ( data_size < 2 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcdata_array_empty(
	     filename_strings->strings_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libscca_filename_string_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty strings array.",
		 function );

		goto on_error;
	}
	while( last_data_offset < ( data_size - 1 ) )
	{
		if( filename_strings_index > LIBSCCA_MAXIMUM_NUMBER_OF_FILENAME_STRINGS )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid filename strings index value out of bounds.",
			 function );

			goto on_error;
		}
		for( data_offset = last_data_offset;
		     data_offset < ( data_size - 1 );
		     data_offset += 2 )
		{
			if( ( data[ data_offset ] == 0 )
			 && ( data[ data_offset + 1 ] == 0 ) )
			{
				data_offset += 2;

				break;
			}
		}
		filename_string_size = data_offset - last_data_offset;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: filename strings entry: %d data offset: 0x%08" PRIzx "\n",
			 function,
			 filename_strings_index, 
			 last_data_offset );

			libcnotify_printf(
			 "%s: filename strings entry: %d data:\n",
			 function,
			 filename_strings_index );
			libcnotify_print_data(
			 &( data[ last_data_offset ] ),
			 filename_string_size,
			 0 );
		}
#endif
		if( libscca_filename_string_initialize(
		     &filename_string,
		     (uint32_t) last_data_offset,
		     &( data[ last_data_offset ] ),
		     filename_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create filename string: %d.",
			 function,
			 filename_strings_index );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     filename_strings->strings_array,
		     &entry_index,
		     (intptr_t *) filename_string,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append filename string: %d to array.",
			 function,
			 filename_strings_index );

			goto on_error;
		}
		filename_string = NULL;

		last_data_offset += filename_string_size;

		filename_strings_index++;
	}
	return( 1 );

on_error:
	if( filename_string != NULL )
	{
		libscca_filename_string_free(
		 &filename_string,
		 NULL );
	}
	libcdata_array_empty(
	 filename_strings->strings_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libscca_filename_string_free,
	 NULL );

	return( -1 );
}

/* Reads the filename strings
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_read_stream(
     libscca_filename_strings_t *filename_strings,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t filename_strings_offset,
     uint32_t filename_strings_size,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_strings_read_stream";
	ssize_t read_count    = 0;

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
	if( filename_strings->data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid filename strings - data value already set.",
		 function );

		return( -1 );
	}
	if( ( filename_strings_size == 0 )
	 || ( filename_strings_size > (uint32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid filenames string size value out of bounds.",
		 function );

		return( -1 );
	}
	filename_strings->data = (uint8_t *) memory_allocate(
	                                      sizeof( uint8_t ) * filename_strings_size );

	if( filename_strings->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create filename strings data.",
		 function );

		goto on_error;
	}
	filename_strings->data_size = (size_t) filename_strings_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading filename strings at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 filename_strings_offset,
		 filename_strings_offset );
	}
#endif
	read_count = libfdata_stream_read_buffer_at_offset(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              filename_strings->data,
	              filename_strings->data_size,
	              (off64_t) filename_strings_offset,
	              0,
	              error );

	if( read_count != (ssize_t) filename_strings_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read filename strings data at offset: %" PRIu32 " (0x%08" PRIx32 ").",
		 function,
		 filename_strings_offset,
		 filename_strings_offset );

		goto on_error;
	}
	if( libscca_filename_strings_read_data(
	     filename_strings,
              filename_strings->data,
              filename_strings->data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read filename strings.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( filename_strings->data != NULL )
	{
		memory_free(
		 filename_strings->data );

		filename_strings->data = NULL;
	}
	filename_strings->data_size = 0;

	libcdata_array_empty(
	 filename_strings->strings_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libscca_filename_string_free,
	 NULL );

	return( -1 );
}

/* Retrieves the filename index for a specific offset
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libscca_filename_strings_get_index_by_offset(
     libscca_filename_strings_t *filename_strings,
     uint32_t filename_offset,
     int *filename_index,
     libcerror_error_t **error )
{
	libscca_filename_string_t *filename_string = NULL;
	static char *function                      = "libscca_filename_strings_get_index_by_offset";
	int entry_index                            = 0;
	int number_of_entries                      = 0;

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
	if( filename_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename index.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     filename_strings->strings_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of strings array entries.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     filename_strings->strings_array,
		     entry_index,
		     (intptr_t **) &filename_string,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve strings array entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( filename_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing strings array entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( filename_string->offset == filename_offset )
		{
			*filename_index = entry_index;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the number of filenames
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_get_number_of_filenames(
     libscca_filename_strings_t *filename_strings,
     int *number_of_filenames,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_strings_get_number_of_filenames";

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
	if( libcdata_array_get_number_of_entries(
	     filename_strings->strings_array,
	     number_of_filenames,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of strings array entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-8 encoded filename
 * This function uses UTF-8 RFC 2279 (or 6-byte UTF-8) to support characters outside Unicode
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_get_utf8_filename_size(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libscca_filename_string_t *filename_string = NULL;
	static char *function                      = "libscca_filename_strings_get_utf8_filename_size";

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
	if( libcdata_array_get_entry_by_index(
	     filename_strings->strings_array,
	     filename_index,
	     (intptr_t **) &filename_string,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve strings array entry: %d.",
		 function,
		 filename_index );

		return( -1 );
	}
	if( libscca_filename_string_get_utf8_string_size(
	     filename_string,
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

/* Retrieves a specific UTF-8 encoded filename
 * This function uses UTF-8 RFC 2279 (or 6-byte UTF-8) to support characters outside Unicode
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_get_utf8_filename(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libscca_filename_string_t *filename_string = NULL;
	static char *function                      = "libscca_filename_strings_get_utf8_filename";

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
	if( libcdata_array_get_entry_by_index(
	     filename_strings->strings_array,
	     filename_index,
	     (intptr_t **) &filename_string,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve strings array entry: %d.",
		 function,
		 filename_index );

		return( -1 );
	}
	if( libscca_filename_string_get_utf8_string(
	     filename_string,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename: %d UTF-8 string.",
		 function,
		 filename_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-16 encoded filename
 * This function uses UCS-2 (with surrogates) to support characters outside Unicode
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_get_utf16_filename_size(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libscca_filename_string_t *filename_string = NULL;
	static char *function                      = "libscca_filename_strings_get_utf16_filename_size";

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
	if( libcdata_array_get_entry_by_index(
	     filename_strings->strings_array,
	     filename_index,
	     (intptr_t **) &filename_string,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve strings array entry: %d.",
		 function,
		 filename_index );

		return( -1 );
	}
	if( libscca_filename_string_get_utf16_string_size(
	     filename_string,
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

/* Retrieves a specific UTF-16 encoded filename
 * This function uses UCS-2 (with surrogates) to support characters outside Unicode
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_get_utf16_filename(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libscca_filename_string_t *filename_string = NULL;
	static char *function                      = "libscca_filename_strings_get_utf16_filename";

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
	if( libcdata_array_get_entry_by_index(
	     filename_strings->strings_array,
	     filename_index,
	     (intptr_t **) &filename_string,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve strings array entry: %d.",
		 function,
		 filename_index );

		return( -1 );
	}
	if( libscca_filename_string_get_utf16_string(
	     filename_string,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename: %d UTF-16 string.",
		 function,
		 filename_index );

		return( -1 );
	}
	return( 1 );
}

