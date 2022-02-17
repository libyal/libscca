/*
 * File header functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libscca_debug.h"
#include "libscca_file_header.h"
#include "libscca_io_handle.h"
#include "libscca_libbfio.h"
#include "libscca_libcerror.h"
#include "libscca_libcnotify.h"
#include "libscca_libfdata.h"
#include "libscca_libuna.h"

#include "scca_file_header.h"

/* Creates file header
 * Make sure the value file_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_file_header_initialize(
     libscca_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_header_initialize";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file header value already set.",
		 function );

		return( -1 );
	}
	*file_header = memory_allocate_structure(
	                libscca_file_header_t );

	if( *file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_header,
	     0,
	     sizeof( libscca_file_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( -1 );
}

/* Frees file header
 * Returns 1 if successful or -1 on error
 */
int libscca_file_header_free(
     libscca_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_header_free";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( 1 );
}

/* Reads the file header data
 * Returns 1 if successful or -1 on error
 */
int libscca_file_header_read_data(
     libscca_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
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
	if( ( data_size < sizeof( scca_file_header_t ) )
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( scca_file_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     ( (scca_file_header_t *) data )->signature,
	     scca_file_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_header_t *) data )->format_version,
	 file_header->format_version );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_header_t *) data )->file_size,
	 file_header->file_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_header_t *) data )->prefetch_hash,
	 file_header->prefetch_hash );

	if( memory_copy(
	     file_header->executable_filename,
	     ( (scca_file_header_t *) data )->executable_filename,
	     60 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy executable filename.",
		 function );

		return( -1 );
	}
	for( file_header->executable_filename_size = 0;
	     ( file_header->executable_filename_size + 1 ) < 60;
	     file_header->executable_filename_size += 2 )
	{
		if( ( file_header->executable_filename[ file_header->executable_filename_size ] == 0 )
		 && ( file_header->executable_filename[ file_header->executable_filename_size + 1 ] == 0 ) )
		{
			break;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: format version\t\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->format_version );

		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (scca_file_header_t *) data )->signature[ 0 ],
		 ( (scca_file_header_t *) data )->signature[ 1 ],
		 ( (scca_file_header_t *) data )->signature[ 2 ],
		 ( (scca_file_header_t *) data )->signature[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: file size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->file_size );

		if( libscca_debug_print_utf16_string_value(
		     function,
		     "executable filename\t\t\t",
		     file_header->executable_filename,
		     file_header->executable_filename_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print UTF-16 string value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: prefetch hash\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_header->prefetch_hash );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_header_t *) data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the file header data
 * Returns 1 if successful or -1 on error
 */
int libscca_file_header_read_data_stream(
     libscca_file_header_t *file_header,
     libfdata_stream_t *data_stream,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ sizeof( scca_file_header_t ) ];

	static char *function = "libscca_file_header_read_data_stream";
	ssize_t read_count    = 0;

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading (uncompressed) file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	read_count = libfdata_stream_read_buffer_at_offset(
	              data_stream,
	              (intptr_t *) file_io_handle,
	              file_header_data,
	              sizeof( scca_file_header_t ),
	              0,
	              0,
	              error );

	if( read_count != (ssize_t) sizeof( scca_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data at offset: 0 (0x00000000).",
		 function );

		return( -1 );
	}
	if( libscca_file_header_read_data(
	     file_header,
	     file_header_data,
	     sizeof( scca_file_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

