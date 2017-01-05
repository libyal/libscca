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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libscca_definitions.h"
#include "libscca_filename_strings.h"
#include "libscca_libbfio.h"
#include "libscca_libcdata.h"
#include "libscca_libcerror.h"
#include "libscca_libcnotify.h"
#include "libscca_libfdata.h"
#include "libscca_libfvalue.h"

/* Frees a filename string offset
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_string_offset_free(
     uint32_t **filename_string_offset,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_string_offset_free";

	if( filename_string_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename string offset.",
		 function );

		return( -1 );
	}
	if( *filename_string_offset != NULL )
	{
		memory_free(
		 *filename_string_offset );

		*filename_string_offset = NULL;
	}
	return( 1 );
}

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
	     &( ( *filename_strings )->offsets_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create offsets array.",
		 function );

		goto on_error;
	}
	if( libfvalue_value_type_initialize(
	     &( ( *filename_strings )->strings ),
	     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create strings value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *filename_strings != NULL )
	{
		if( ( *filename_strings )->offsets_array != NULL )
		{
			libcdata_array_free(
			 &( ( *filename_strings )->offsets_array ),
			 NULL,
			 NULL );
		}
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
		     &( ( *filename_strings )->offsets_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libscca_filename_string_offset_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free offsets array.",
			 function );

			result = -1;
		}
		if( libfvalue_value_free(
		     &( ( *filename_strings )->strings ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free strings values.",
			 function );

			result = -1;
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
	     filename_strings->offsets_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libscca_filename_string_offset_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty offsets array.",
		 function );

		result = -1;
	}
	if( libfvalue_value_clear(
	     filename_strings->strings,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear strings values.",
		 function );

		result = -1;
	}
	return( result );
}

/* Reads the filename strings
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_read(
     libscca_filename_strings_t *filename_strings,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t filename_strings_offset,
     uint32_t filename_strings_size,
     libcerror_error_t **error )
{
	uint32_t *filename_string_offset = NULL;
	uint8_t *filename_strings_data   = NULL;
	static char *function            = "libscca_filename_strings_read";
	ssize_t data_offset              = 0;
	ssize_t last_data_offset         = 0;
	ssize_t read_count               = 0;
	int entry_index                  = 0;
	int filename_strings_index       = 0;

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
#if SIZEOF_SIZE_T <= 4
	if( (size_t) filename_strings_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid filenames string size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
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
	if( libfdata_stream_seek_offset(
	     uncompressed_data_stream,
	     (off64_t) filename_strings_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek filename strings offset: %" PRIu32 ".",
		 function,
		 filename_strings_offset );

		goto on_error;
	}
	filename_strings_data = (uint8_t *) memory_allocate(
	                                     sizeof( uint8_t ) * filename_strings_size );

	if( filename_strings_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create filename strings data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              filename_strings_data,
	              (size_t) filename_strings_size,
	              0,
	              error );

	if( read_count != (ssize_t) filename_strings_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read filename strings data.",
		 function );

		goto on_error;
	}
	while( last_data_offset < read_count )
	{
		data_offset = libfvalue_value_type_get_string_size(
			       filename_strings->strings,
		               &( filename_strings_data[ last_data_offset ] ),
		               read_count - last_data_offset,
			       error );

		if( data_offset == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to determine data string size.",
			 function );

			goto on_error;
		}
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
			 &( filename_strings_data[ last_data_offset ] ),
			 (size_t) data_offset,
			 0 );
		}
#endif
		filename_string_offset = (uint32_t *) memory_allocate(
		                                       sizeof( uint32_t ) );

		if( filename_string_offset == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create filename string offset.",
			 function );

			goto on_error;
		}
		*filename_string_offset = last_data_offset;

		if( libcdata_array_append_entry(
		     filename_strings->offsets_array,
		     &entry_index,
		     (intptr_t *) filename_string_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append filename strings: %d offset to array.",
			 function,
			 filename_strings_index );

			goto on_error;
		}
		filename_string_offset = NULL;

		if( libfvalue_value_append_entry_data(
		     filename_strings->strings,
		     &entry_index,
		     &( filename_strings_data[ last_data_offset ] ),
		     (size_t) data_offset,
		     LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append filename strings: %d value entry data.",
			 function,
			 filename_strings_index );

			return( -1 );
		}
		last_data_offset += data_offset;

		filename_strings_index++;
	}
	memory_free(
	 filename_strings_data );

	return( 1 );

on_error:
	if( filename_string_offset != NULL )
	{
		memory_free(
		 filename_string_offset );
	}
	if( filename_strings_data != NULL )
	{
		memory_free(
		 filename_strings_data );
	}
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
	uint32_t *filename_string_offset = NULL;
	static char *function            = "libscca_filename_strings_get_index_by_offset";
	int entry_index                  = 0;
	int number_of_entries            = 0;

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
	     filename_strings->offsets_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets array entries.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     filename_strings->offsets_array,
		     entry_index,
		     (intptr_t **) &filename_string_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offsets array entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( filename_string_offset == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offsets array entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( *filename_string_offset == filename_offset )
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
	if( libfvalue_value_get_number_of_value_entries(
	     filename_strings->strings,
	     number_of_filenames,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of strings.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_get_utf8_filename_size(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_strings_get_utf8_filename_size";

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
	if( libfvalue_value_get_utf8_string_size(
	     filename_strings->strings,
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

/* Retrieves a specific UTF-8 encoded filename
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
	static char *function = "libscca_filename_strings_get_utf8_filename";

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
	if( libfvalue_value_copy_to_utf8_string(
	     filename_strings->strings,
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

/* Retrieves the size of a specific UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libscca_filename_strings_get_utf16_filename_size(
     libscca_filename_strings_t *filename_strings,
     int filename_index,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libscca_filename_strings_get_utf16_filename_size";

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
	if( libfvalue_value_get_utf16_string_size(
	     filename_strings->strings,
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

/* Retrieves a specific UTF-16 encoded filename
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
	static char *function = "libscca_filename_strings_get_utf16_filename";

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
	if( libfvalue_value_copy_to_utf16_string(
	     filename_strings->strings,
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

