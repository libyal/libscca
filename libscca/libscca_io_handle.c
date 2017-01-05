/*
 * Input/Output (IO) handle functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libscca_compressed_block.h"
#include "libscca_debug.h"
#include "libscca_definitions.h"
#include "libscca_file_metrics.h"
#include "libscca_io_handle.h"
#include "libscca_libbfio.h"
#include "libscca_libcdata.h"
#include "libscca_libcerror.h"
#include "libscca_libcnotify.h"
#include "libscca_libfdatetime.h"
#include "libscca_libfvalue.h"
#include "libscca_libuna.h"
#include "libscca_unused.h"
#include "libscca_volume_information.h"

#include "scca_file_header.h"
#include "scca_file_metrics_array.h"
#include "scca_trace_chain_array.h"
#include "scca_volume_information.h"

const char *scca_file_signature           = "SCCA";
const char *scca_mam_file_signature_win10 = "MAM\x04";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_initialize(
     libscca_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libscca_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libscca_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libscca_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees a IO handle
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_free(
     libscca_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libscca_io_handle_free";

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_clear(
     libscca_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libscca_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libscca_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the compressed file header
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_read_compressed_file_header(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ 8 ];

	static char *function = "libscca_io_handle_read_compressed_file_header";
	size64_t file_size    = 0;
	ssize_t read_count    = 0;

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
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		return( -1 );
	}
	if( ( file_size < 8 )
	 || ( file_size > (size64_t) UINT32_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid file size value out of bounds.",
		 function );

		return( -1 );
	}
	io_handle->file_size = (uint32_t) file_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading compressed file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_header_data,
	              8,
	              error );

	if( read_count != (ssize_t) 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data.",
		 function );

		return( -1 );
	}
	if( memory_compare(
	     &( file_header_data[ 4 ] ),
	     scca_file_signature,
	     4 ) == 0 )
	{
		io_handle->file_type= LIBSCCA_FILE_TYPE_UNCOMPRESSED;
	}
	else if( memory_compare(
	          file_header_data,
	          scca_mam_file_signature_win10,
	          4 ) == 0 )
	{
		io_handle->file_type = LIBSCCA_FILE_TYPE_COMPRESSED_WINDOWS10;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	if( io_handle->file_type == LIBSCCA_FILE_TYPE_UNCOMPRESSED )
	{
		io_handle->uncompressed_data_size = io_handle->file_size;
	}
	else if( io_handle->file_type == LIBSCCA_FILE_TYPE_COMPRESSED_WINDOWS10 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: signature\t\t: %c%c%c\\x%02x\n",
			 function,
			 file_header_data[ 0 ],
			 file_header_data[ 1 ],
			 file_header_data[ 2 ],
			 file_header_data[ 3 ] );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data[ 4 ] ),
		 io_handle->uncompressed_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: uncompressed data size\t: %" PRIu32 "\n",
			 function,
			 io_handle->uncompressed_data_size );
		}
#endif
		if( io_handle->uncompressed_data_size != ( io_handle->file_size - 8 )  )
		{
/* TODO flag mismatch and file as corrupted? */
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads the compressed blocks
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_read_compressed_blocks(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_t *compressed_blocks_list,
     libfcache_cache_t *compressed_blocks_cache,
     libcerror_error_t **error )
{
	libfdata_list_element_t *compressed_blocks_list_element = NULL;
	libscca_compressed_block_t *compressed_block            = NULL;
	static char *function                                   = "libscca_io_handle_read_compressed_blocks";
	off64_t file_offset                                     = 0;
	size64_t compressed_data_size                           = 0;
	ssize_t read_count                                      = 0;
	uint32_t uncompressed_data_size                         = 0;
	uint32_t uncompressed_block_size                        = 0;
	int compressed_block_index                              = 0;
	int element_index                                       = 0;

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
	if( io_handle->file_type != LIBSCCA_FILE_TYPE_COMPRESSED_WINDOWS10 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported file type.",
		 function );

		return( -1 );
	}
	file_offset = 8;

	uncompressed_data_size = io_handle->uncompressed_data_size;
	compressed_data_size   = io_handle->file_size - 8;

	while( compressed_data_size > 2 )
	{
		uncompressed_block_size = (size_t) uncompressed_data_size;

		if( libscca_compressed_block_initialize(
		     &compressed_block,
		     uncompressed_block_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create compressed block.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading compressed data block at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 file_offset,
			 file_offset );
		}
#endif
		read_count = libscca_compressed_block_read(
		              compressed_block,
		              file_io_handle,
		              file_offset,
		              (size_t) uncompressed_block_size,
		              error );

		if( read_count == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read compressed block data.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compressed block: %d size\t: %" PRIu32 "\n",
			 function,
			 compressed_block_index,
			 compressed_block->data_size );
		}
#endif
		if( libfdata_list_append_element_with_mapped_size(
		     compressed_blocks_list,
		     &element_index,
		     0,
		     file_offset,
		     (size64_t) read_count,
		     LIBFDATA_RANGE_FLAG_IS_COMPRESSED,
		     compressed_block->data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append compressed block: %d to list.",
			 function,
			 compressed_block_index );

			goto on_error;
		}
		file_offset            += read_count;
		compressed_data_size   -= read_count;
		uncompressed_data_size -= uncompressed_block_size;

		if( libfdata_list_get_list_element_by_index(
		     compressed_blocks_list,
		     element_index,
		     &compressed_blocks_list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve compressed block: %d list element.",
			 function,
			 element_index );

			goto on_error;
		}
		if( libfdata_list_element_set_element_value(
		     compressed_blocks_list_element,
		     (intptr_t *) file_io_handle,
		     compressed_blocks_cache,
		     (intptr_t *) compressed_block,
		     (int (*)(intptr_t **, libcerror_error_t **)) &libscca_compressed_block_free,
		     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set compressed block: %d as element value.",
			 function,
			 element_index );

			goto on_error;
		}
		compressed_block = NULL;

		compressed_block_index++;
	}
	return( 1 );

on_error:
	if( compressed_block != NULL )
	{
		libscca_compressed_block_free(
		 &compressed_block,
		 NULL );
	}
	return( -1 );
}

/* Reads the uncompressed file header
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_read_uncompressed_file_header(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint8_t *executable_filename,
     size_t *executable_filename_size,
     uint32_t *prefetch_hash,
     libcerror_error_t **error )
{
	scca_file_header_t file_header;

	static char *function = "libscca_io_handle_read_uncompressed_file_header";
	ssize_t read_count    = 0;
	uint32_t file_size    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

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
	if( executable_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid executable filename.",
		 function );

		return( -1 );
	}
	if( executable_filename_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid executable filename size.",
		 function );

		return( -1 );
	}
	if( prefetch_hash == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid prefetch hash.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading uncompressed file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libfdata_stream_seek_offset(
	     uncompressed_data_stream,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( scca_file_header_t ),
	              0,
	              error );

	if( read_count != (ssize_t) sizeof( scca_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data.",
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
		 (uint8_t *) &file_header,
		 sizeof( scca_file_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     file_header.signature,
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
	 file_header.format_version,
	 io_handle->format_version );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.file_size,
	 file_size );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.prefetch_hash,
	 *prefetch_hash );

	if( memory_copy(
	     executable_filename,
	     file_header.executable_filename,
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
	for( *executable_filename_size = 0;
	     ( *executable_filename_size + 1 ) < 60;
	     *executable_filename_size += 2 )
	{
		if( ( executable_filename[ *executable_filename_size ] == 0 )
		 && ( executable_filename[ *executable_filename_size + 1 ] == 0 ) )
		{
			break;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: format version\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->format_version );

		libcnotify_printf(
		 "%s: signature\t\t: %c%c%c%c\n",
		 function,
		 file_header.signature[ 0 ],
		 file_header.signature[ 1 ],
		 file_header.signature[ 2 ],
		 file_header.signature[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: file size\t\t: %" PRIu32 "\n",
		 function,
		 file_size );

		if( libscca_debug_print_utf16_string_value(
		     function,
		     "executable filename\t",
		     executable_filename,
		     *executable_filename_size,
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
		 "%s: prefetch hash\t\t: 0x%08" PRIx32 "\n",
		 function,
		 *prefetch_hash );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( io_handle->uncompressed_data_size != file_size )
	{
/* TODO flag mismatch and file as corrupted? */
	}
	return( 1 );
}

/* Reads the file metrics array
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_read_file_metrics_array(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t file_offset,
     uint32_t number_of_entries,
     libscca_filename_strings_t *filename_strings,
     libcdata_array_t *file_metrics_array,
     libcerror_error_t **error )
{
	libscca_internal_file_metrics_t *file_metrics = NULL;
	uint8_t *entry_data                           = NULL;
	uint8_t *file_metrics_array_data              = NULL;
	static char *function                         = "libscca_io_handle_read_file_metrics_array";
	size_t entry_data_size                        = 0;
	size_t read_size                              = 0;
	ssize_t read_count                            = 0;
	uint32_t file_metrics_entry_index             = 0;
	int entry_index                               = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                          = 0;
#endif

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
	if( ( io_handle->format_version != 17 )
	 && ( io_handle->format_version != 23 )
	 && ( io_handle->format_version != 26 )
	 && ( io_handle->format_version != 30 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported format version.",
		 function );

		return( -1 );
	}
#if SIZEOF_SIZE_T <= 4
	if( (size_t) number_of_entries > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of values value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
	if( io_handle->format_version == 17 )
	{
		entry_data_size = sizeof( scca_file_metrics_array_entry_v17_t );
	}
	else if( ( io_handle->format_version == 23 )
	      || ( io_handle->format_version == 26 )
	      || ( io_handle->format_version == 30 ) )
	{
		entry_data_size = sizeof( scca_file_metrics_array_entry_v23_t );
	}
	if( (size_t) number_of_entries > ( (size_t) SSIZE_MAX / entry_data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of entries value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file metrics array at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libfdata_stream_seek_offset(
	     uncompressed_data_stream,
	     (off64_t) file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file metrics array offset: %" PRIu32 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	read_size = number_of_entries * entry_data_size;

	file_metrics_array_data = (uint8_t *) memory_allocate(
	                                       sizeof( uint8_t ) * read_size );

	if( file_metrics_array_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file metrics array data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              file_metrics_array_data,
	              read_size,
	              0,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file metrics array data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file metrics array data:\n",
		 function );
		libcnotify_print_data(
		 file_metrics_array_data,
		 read_size,
		 0 );
	}
#endif
	entry_data = file_metrics_array_data;

	for( file_metrics_entry_index = 0;
	     file_metrics_entry_index < number_of_entries;
	     file_metrics_entry_index++ )
	{
		if( libscca_file_metrics_initialize(
		     &file_metrics,
		     filename_strings,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create file metrics: %" PRIu32 ".",
			 function,
			 file_metrics_entry_index );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: file metrics array entry: %" PRIu32 " data:\n",
			 function,
			 file_metrics_entry_index );
			libcnotify_print_data(
			 entry_data,
			 entry_data_size,
			 0 );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_metrics_array_entry_v17_t *) entry_data )->start_time,
		 file_metrics->start_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_metrics_array_entry_v17_t *) entry_data )->duration,
		 file_metrics->duration );

		if( io_handle->format_version == 17 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_metrics_array_entry_v17_t *) entry_data )->filename_string_offset,
			 file_metrics->filename_string_offset );

			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_metrics_array_entry_v17_t *) entry_data )->flags,
			 file_metrics->flags );
		}
		else if( ( io_handle->format_version == 23 )
		      || ( io_handle->format_version == 26 )
		      || ( io_handle->format_version == 30 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_metrics_array_entry_v23_t *) entry_data )->filename_string_offset,
			 file_metrics->filename_string_offset );

			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_metrics_array_entry_v23_t *) entry_data )->flags,
			 file_metrics->flags );

			byte_stream_copy_to_uint64_little_endian(
			 ( (scca_file_metrics_array_entry_v23_t *) entry_data )->file_reference,
			 file_metrics->file_reference );

			file_metrics->file_reference_is_set = 1;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: start time\t\t\t\t: %" PRIu32 " ms\n",
			 function,
			 file_metrics->start_time );

			libcnotify_printf(
			 "%s: duration\t\t\t\t: %" PRIu32 " ms\n",
			 function,
			 file_metrics->duration );

			if( ( io_handle->format_version == 23 )
			 || ( io_handle->format_version == 26 )
			 || ( io_handle->format_version == 30 ) )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_file_metrics_array_entry_v23_t *) entry_data )->average_duration,
				 value_32bit );
				libcnotify_printf(
				 "%s: average duration\t\t\t: %" PRIu32 " ms\n",
				 function,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: filename string offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 file_metrics->filename_string_offset );

			if( io_handle->format_version == 17 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_file_metrics_array_entry_v17_t *) entry_data )->filename_string_numbers_of_characters,
				 value_32bit );
			}
			else if( ( io_handle->format_version == 23 )
			      || ( io_handle->format_version == 26 )
			      || ( io_handle->format_version == 30 ) )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_file_metrics_array_entry_v23_t *) entry_data )->filename_string_numbers_of_characters,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: filename string number of characters\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: flags\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 file_metrics->flags );

			if( file_metrics->file_reference_is_set != 0 )
			{
				if( file_metrics->file_reference == 0 )
				{
					libcnotify_printf(
					 "%s: file reference\t\t\t: %" PRIu64 "\n",
					 function,
					 file_metrics->file_reference );
				}
				else
				{
					libcnotify_printf(
					 "%s: file reference\t\t\t: MFT entry: %" PRIu64 ", sequence: %" PRIu64 "\n",
					 function,
					 file_metrics->file_reference & 0xffffffffffffUL,
					 file_metrics->file_reference >> 48 );
				}
			}
			libcnotify_printf(
			 "\n" );
		}
#endif
		entry_data += entry_data_size;

		if( libcdata_array_append_entry(
		     file_metrics_array,
		     &entry_index,
		     (intptr_t *) file_metrics,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append file metrics: %" PRIu32 " to array.",
			 function,
			 file_metrics_entry_index );

			goto on_error;
		}
		file_metrics = NULL;
	}
	memory_free(
	 file_metrics_array_data );

	return( 1 );

on_error:
	if( file_metrics != NULL )
	{
		libscca_internal_file_metrics_free(
		 &file_metrics,
		 NULL );
	}
	if( file_metrics_array_data != NULL )
	{
		memory_free(
		 file_metrics_array_data );
	}
	return( -1 );
}

/* Reads the trace chain array
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_read_trace_chain_array(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t file_offset,
     uint32_t number_of_entries,
     libcerror_error_t **error )
{
	uint8_t *entry_data             = NULL;
	uint8_t *trace_chain_array_data = NULL;
	static char *function           = "libscca_io_handle_read_trace_chain_array";
	size_t entry_data_size          = 0;
	size_t read_size                = 0;
	ssize_t read_count              = 0;
	uint32_t entry_index            = 0;
	uint32_t next_table_index       = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit            = 0;
	uint16_t value_16bit            = 0;
#endif

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
	if( ( io_handle->format_version != 17 )
	 && ( io_handle->format_version != 23 )
	 && ( io_handle->format_version != 26 )
	 && ( io_handle->format_version != 30 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported format version.",
		 function );

		return( -1 );
	}
#if SIZEOF_SIZE_T <= 4
	if( (size_t) number_of_entries > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of values value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
	if( ( io_handle->format_version == 17 )
	 || ( io_handle->format_version == 23 )
	 || ( io_handle->format_version == 26 ) )
	{
		entry_data_size = sizeof( scca_trace_chain_array_entry_v17_t );
	}
	else if( io_handle->format_version == 30 )
	{
		entry_data_size = sizeof( scca_trace_chain_array_entry_v30_t );
	}
	if( (size_t) number_of_entries > ( (size_t) SSIZE_MAX / entry_data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of entries value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading trace chain array at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libfdata_stream_seek_offset(
	     uncompressed_data_stream,
	     (off64_t) file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek trace chain array offset: %" PRIu32 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	read_size = number_of_entries * entry_data_size;

	trace_chain_array_data = (uint8_t *) memory_allocate(
	                                      sizeof( uint8_t ) * read_size );

	if( trace_chain_array_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create trace chain array data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              trace_chain_array_data,
	              read_size,
	              0,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read trace chain array data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: trace chain array data:\n",
		 function );
		libcnotify_print_data(
		 trace_chain_array_data,
		 read_size,
		 0 );
	}
#endif
	entry_data = trace_chain_array_data;

	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: trace chain array entry: %" PRIu32 " data:\n",
			 function,
			 entry_index );
			libcnotify_print_data(
			 entry_data,
			 entry_data_size,
			 0 );
		}
#endif
		if( entry_data_size == 8 )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_trace_chain_array_entry_v30_t *) entry_data )->total_block_load_count,
				 value_32bit );
				libcnotify_printf(
				 "%s: total block load count\t: %" PRIu32 " blocks (%" PRIu64 " bytes)\n",
				 function,
				 value_32bit,
				 (uint64_t) value_32bit * 512 * 1024 );

				libcnotify_printf(
				 "%s: unknown1\t\t\t: 0x%02" PRIx8 "\n",
				 function,
				 ( (scca_trace_chain_array_entry_v30_t *) entry_data )->unknown1 );

				libcnotify_printf(
				 "%s: unknown2\t\t\t: 0x%02" PRIx8 "\n",
				 function,
				 ( (scca_trace_chain_array_entry_v30_t *) entry_data )->unknown2 );

				byte_stream_copy_to_uint16_little_endian(
				 ( (scca_trace_chain_array_entry_v30_t *) entry_data )->unknown3,
				 value_16bit );
				libcnotify_printf(
				 "%s: unknown3\t\t\t: 0x%04" PRIx16 "\n",
				 function,
				 value_16bit );
			}
#endif
		}
		else if( entry_data_size == 12 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_trace_chain_array_entry_v17_t *) entry_data )->next_array_entry_index,
			 next_table_index );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				if( next_table_index == 0xffffffffUL )
				{
					libcnotify_printf(
					 "%s: next table index\t\t: 0x%08" PRIx32 "\n",
					 function,
					 next_table_index );
				}
				else
				{
					libcnotify_printf(
					 "%s: next table index\t\t: %" PRIu32 "\n",
					 function,
					 next_table_index );
				}
				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_trace_chain_array_entry_v17_t *) entry_data )->total_block_load_count,
				 value_32bit );
				libcnotify_printf(
				 "%s: total block load count\t: %" PRIu32 " blocks (%" PRIu64 " bytes)\n",
				 function,
				 value_32bit,
				 (uint64_t) value_32bit * 512 * 1024 );

				libcnotify_printf(
				 "%s: unknown1\t\t\t: 0x%02" PRIx8 "\n",
				 function,
				 ( (scca_trace_chain_array_entry_v17_t *) entry_data )->unknown1 );

				libcnotify_printf(
				 "%s: unknown2\t\t\t: 0x%02" PRIx8 "\n",
				 function,
				 ( (scca_trace_chain_array_entry_v17_t *) entry_data )->unknown2 );

				byte_stream_copy_to_uint16_little_endian(
				 ( (scca_trace_chain_array_entry_v17_t *) entry_data )->unknown3,
				 value_16bit );
				libcnotify_printf(
				 "%s: unknown3\t\t\t: 0x%04" PRIx16 "\n",
				 function,
				 value_16bit );
			}
#endif
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		entry_data += entry_data_size;
	}
	memory_free(
	 trace_chain_array_data );

	return( 1 );

on_error:
	if( trace_chain_array_data != NULL )
	{
		memory_free(
		 trace_chain_array_data );
	}
	return( -1 );
}

/* Reads the volumes information
 * Returns 1 if successful or -1 on error
 */
int libscca_io_handle_read_volumes_information(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t volumes_information_offset,
     uint32_t volumes_information_size,
     uint32_t number_of_volumes,
     libcdata_array_t *volumes_array,
     libcerror_error_t **error )
{
	libscca_internal_volume_information_t *volume_information = NULL;
	uint8_t *volume_information_data                          = NULL;
	uint8_t *volumes_information_data                         = NULL;
	static char *function                                     = "libscca_io_handle_read_volumes_information";
	ssize_t value_data_size                                   = 0;
	ssize_t volume_information_size                           = 0;
	ssize_t read_count                                        = 0;
	uint32_t directory_strings_array_offset                   = 0;
	uint32_t directory_strings_array_size                     = 0;
	uint32_t device_path_offset                               = 0;
	uint32_t device_path_size                                 = 0;
	uint32_t file_references_index                            = 0;
	uint32_t file_references_offset                           = 0;
	uint32_t file_references_size                             = 0;
	uint32_t number_of_directory_strings                      = 0;
	uint32_t number_of_file_references                        = 0;
	uint32_t version                                          = 0;
	uint32_t volume_index                                     = 0;
	uint32_t volume_information_offset                        = 0;
	int entry_index                                           = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                                      = 0;
	uint32_t value_32bit                                      = 0;
#endif

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
	if( ( io_handle->format_version != 17 )
	 && ( io_handle->format_version != 23 )
	 && ( io_handle->format_version != 26 )
	 && ( io_handle->format_version != 30 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported format version.",
		 function );

		return( -1 );
	}
#if SIZEOF_SIZE_T <= 4
	if( (size_t) volumes_information_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid volume information size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( (size_t) number_of_volumes > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of volumes value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading volumes information at offset: %" PRIi32 " (0x%08" PRIx32 ")\n",
		 function,
		 volumes_information_offset,
		 volumes_information_offset );
	}
#endif
	if( libfdata_stream_seek_offset(
	     uncompressed_data_stream,
	     (off64_t) volumes_information_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek volumes information offset: %" PRIi32 " (0x%08" PRIx32 ").",
		 function,
		 volumes_information_offset,
		 volumes_information_offset );

		goto on_error;
	}
	volumes_information_data = (uint8_t *) memory_allocate(
	                                        sizeof( uint8_t ) * volumes_information_size );

	if( volumes_information_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volumes information data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              volumes_information_data,
	              volumes_information_size,
	              0,
	              error );

	if( read_count != (ssize_t) volumes_information_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read volumes information data.",
		 function );

		goto on_error;
	}
	if( io_handle->format_version == 17 )
	{
		volume_information_size = sizeof( scca_volume_information_v17_t );
	}
	else if( ( io_handle->format_version == 23 )
	      || ( io_handle->format_version == 26 ) )
	{
		volume_information_size = sizeof( scca_volume_information_v23_t );
	}
	else if( io_handle->format_version == 30 )
	{
		volume_information_size = sizeof( scca_volume_information_v30_t );
	}
	if( volume_information_size > volumes_information_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid volume information size value out of bounds.",
		 function );

		goto on_error;
	}
	for( volume_index = 0;
	     volume_index < number_of_volumes;
	     volume_index++ )
	{
		if( libscca_volume_information_initialize(
		     (libscca_volume_information_t **) &volume_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create volume: %" PRIu32 " information.",
			 function,
			 volume_index );

			goto on_error;
		}
		if( volume_information_offset > ( volumes_information_size - volume_information_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid volume information offset value out of bounds.",
			 function );

			goto on_error;
		}
		volume_information_data = &( volumes_information_data[ volume_information_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: volume: %d information data:\n",
			 function,
			 volume_index );
			libcnotify_print_data(
			 volume_information_data,
			 volume_information_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->device_path_offset,
		 device_path_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->device_path_number_of_characters,
		 device_path_size );

		byte_stream_copy_to_uint64_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->creation_time,
		 volume_information->creation_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->serial_number,
		 volume_information->serial_number );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->file_references_offset,
		 file_references_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->file_references_size,
		 file_references_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->directory_strings_array_offset,
		 directory_strings_array_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_volume_information_v17_t *) volume_information_data )->number_of_directory_strings,
		 number_of_directory_strings );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: device path offset\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 device_path_offset );

			libcnotify_printf(
			 "%s: device path number of characters\t: %" PRIu32 "\n",
			 function,
			 device_path_size );

			if( libscca_debug_print_filetime_value(
			     function,
			     "creation time\t\t\t",
			     ( (scca_volume_information_v17_t *) volume_information_data )->creation_time,
			     8,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print filetime value.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: serial number\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 volume_information->serial_number );

			libcnotify_printf(
			 "%s: file references offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 file_references_offset );

			libcnotify_printf(
			 "%s: file references size\t\t: %" PRIu32 "\n",
			 function,
			 file_references_size );

			libcnotify_printf(
			 "%s: directory strings array offset\t: 0x%08" PRIx32 "\n",
			 function,
			 directory_strings_array_offset );

			libcnotify_printf(
			 "%s: number of directory strings\t\t: %" PRIu32 "\n",
			 function,
			 number_of_directory_strings );

			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_volume_information_v17_t *) volume_information_data )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( ( io_handle->format_version == 23 )
			 || ( io_handle->format_version == 26 ) )
			{
				libcnotify_printf(
				 "%s: unknown2:\n",
				 function );
				libcnotify_print_data(
				 ( (scca_volume_information_v23_t *) volume_information_data )->unknown2,
				 28,
				 0 );

				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_volume_information_v23_t *) volume_information_data )->unknown3,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				libcnotify_printf(
				 "%s: unknown4:\n",
				 function );
				libcnotify_print_data(
				 ( (scca_volume_information_v23_t *) volume_information_data )->unknown4,
				 28,
				 0 );

				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_volume_information_v23_t *) volume_information_data )->unknown5,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );
			}
			else if( io_handle->format_version == 30 )
			{
				libcnotify_printf(
				 "%s: unknown2:\n",
				 function );
				libcnotify_print_data(
				 ( (scca_volume_information_v30_t *) volume_information_data )->unknown2,
				 24,
				 0 );

				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_volume_information_v30_t *) volume_information_data )->unknown3,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				libcnotify_printf(
				 "%s: unknown4:\n",
				 function );
				libcnotify_print_data(
				 ( (scca_volume_information_v30_t *) volume_information_data )->unknown4,
				 24,
				 0 );

				byte_stream_copy_to_uint32_little_endian(
				 ( (scca_volume_information_v30_t *) volume_information_data )->unknown5,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );
			}
			libcnotify_printf(
			 "\n" );
		}
#endif
		volume_information_offset += volume_information_size;

		if( ( device_path_offset != 0 )
		 && ( device_path_size != 0 ) )
		{
			if( device_path_offset > volumes_information_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid volume device path offset value out of bounds.",
				 function );

				goto on_error;
			}
			if( device_path_size >= ( UINT32_MAX / 2 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid volume device path string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			device_path_size *= 2;

			if( ( device_path_size > volumes_information_size )
			 || ( device_path_offset > ( volumes_information_size - device_path_size ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid volume device path size value out of bounds.",
				 function );

				goto on_error;
			}
			volume_information->device_path = (uint8_t *) memory_allocate(
			                                               sizeof( uint8_t ) * device_path_size );

			if( volume_information->device_path == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create device path.",
				 function );

				goto on_error;
			}
			volume_information->device_path_size = device_path_size;

			if( memory_copy(
			     volume_information->device_path,
			     &( volumes_information_data[ device_path_offset ] ),
			     device_path_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy device path.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				if( libscca_debug_print_utf16_string_value(
				     function,
				     "volume device path\t\t\t",
				     volume_information->device_path,
				     volume_information->device_path_size,
				     LIBUNA_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print UTF-16 string value.",
					 function );

					goto on_error;
				}
			}
#endif
		}
		if( file_references_offset != 0 )
		{
			if( file_references_offset > volumes_information_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid file references offset value out of bounds.",
				 function );

				goto on_error;
			}
			if( ( file_references_size > volumes_information_size )
			 || ( file_references_offset > ( volumes_information_size - file_references_size ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid file references size value out of bounds.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: file references data:\n",
				 function );
				libcnotify_print_data(
				 &( volumes_information_data[ file_references_offset ] ),
				 file_references_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			byte_stream_copy_to_uint32_little_endian(
			 &( volumes_information_data[ file_references_offset ] ),
			 version );

			byte_stream_copy_to_uint32_little_endian(
			 &( volumes_information_data[ file_references_offset + 4 ] ),
			 number_of_file_references );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: version\t\t\t\t: %" PRIu32 "\n",
				 function,
				 version );

				libcnotify_printf(
				 "%s: number of file references\t\t: %" PRIu32 "\n",
				 function,
				 number_of_file_references );

				byte_stream_copy_to_uint64_little_endian(
				 &( volumes_information_data[ file_references_offset + 8 ] ),
				 value_64bit );
				libcnotify_printf(
				 "%s: unknown1\t\t\t\t: 0x%08" PRIx64 "\n",
				 function,
				 value_64bit );
			}
#endif
			for( file_references_index = 1;
			     file_references_index < number_of_file_references;
			     file_references_index++ )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					byte_stream_copy_to_uint64_little_endian(
					 &( volumes_information_data[ file_references_offset + 8 + ( file_references_index * 8 ) ] ),
					 value_64bit );

					if( value_64bit == 0 )
					{
						libcnotify_printf(
						 "%s: file reference: %d\t\t\t: %" PRIu64 "\n",
						 function,
						 file_references_index,
						 value_64bit );
					}
					else
					{
						libcnotify_printf(
						 "%s: file reference: %d\t\t\t: MFT entry: %" PRIu64 ", sequence: %" PRIu64 "\n",
						 function,
						 file_references_index,
						 value_64bit & 0xffffffffffffUL,
						 value_64bit >> 48 );
					}
				}
#endif
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "\n" );
			}
#endif
		}
		if( directory_strings_array_offset != 0 )
		{
			if( directory_strings_array_offset > volumes_information_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid directory strings array offset value out of bounds.",
				 function );

				goto on_error;
			}
/* TODO fix size calculation */
			directory_strings_array_size = volumes_information_size - directory_strings_array_offset;

			if( libfvalue_value_type_initialize(
			     &( volume_information->directory_strings ),
			     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create directory strings value.",
				 function );

				goto on_error;
			}
			value_data_size = libfvalue_value_type_set_data_strings_array(
					   volume_information->directory_strings,
					   &( volumes_information_data[ directory_strings_array_offset ] ),
					   directory_strings_array_size,
					   LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
					   error );

			if( value_data_size == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data of directory strings value.",
				 function );

				goto on_error;
			}
		}
		if( libcdata_array_append_entry(
		     volumes_array,
		     &entry_index,
		     (intptr_t *) volume_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append volume: %" PRIu32 " information to array.",
			 function,
			 volume_index );

			goto on_error;
		}
		volume_information = NULL;
	}
/* TODO print trailing data */
	memory_free(
	 volumes_information_data );

	return( 1 );

on_error:
	if( volume_information != NULL )
	{
		libscca_internal_volume_information_free(
		 &volume_information,
		 NULL );
	}
	if( volumes_information_data != NULL )
	{
		memory_free(
		 volumes_information_data );
	}
	return( -1 );
}

/* Reads data from the current offset into a buffer
 * Callback for the uncompressed block stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t libscca_io_handle_read_segment_data(
         intptr_t *data_handle LIBSCCA_ATTRIBUTE_UNUSED,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index LIBSCCA_ATTRIBUTE_UNUSED,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags LIBSCCA_ATTRIBUTE_UNUSED,
         uint8_t read_flags LIBSCCA_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	static char *function = "libscca_io_handle_read_segment_data";
	ssize_t read_count    = 0;

	LIBSCCA_UNREFERENCED_PARAMETER( data_handle )
	LIBSCCA_UNREFERENCED_PARAMETER( segment_file_index )
	LIBSCCA_UNREFERENCED_PARAMETER( segment_flags )
	LIBSCCA_UNREFERENCED_PARAMETER( read_flags )

	if( segment_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment data size value out of bounds.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              (libbfio_handle_t *) file_io_handle,
	              segment_data,
	              segment_data_size,
	              error );

	if( read_count != (ssize_t) segment_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment: %d data.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the data
 * Callback for the uncompressed block stream
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libscca_io_handle_seek_segment_offset(
         intptr_t *data_handle LIBSCCA_ATTRIBUTE_UNUSED,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index LIBSCCA_ATTRIBUTE_UNUSED,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "libscca_io_handle_seek_segment_offset";

	LIBSCCA_UNREFERENCED_PARAMETER( data_handle )
	LIBSCCA_UNREFERENCED_PARAMETER( segment_file_index )

	if( libbfio_handle_seek_offset(
	     (libbfio_handle_t *) file_io_handle,
	     segment_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek segment: %d offset: %" PRIi64 ".",
		 function,
		 segment_index,
		 segment_offset );

		return( -1 );
	}
	return( segment_offset );
}

