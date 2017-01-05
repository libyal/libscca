/*
 * Compressed block functions
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
#include "libscca_definitions.h"
#include "libscca_file.h"
#include "libscca_io_handle.h"
#include "libscca_libcerror.h"
#include "libscca_libcnotify.h"
#include "libscca_libfcache.h"
#include "libscca_libfdata.h"
#include "libscca_libfwnt.h"
#include "libscca_unused.h"

/* Creates compressed block
 * Make sure the value compressed_block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_compressed_block_initialize(
     libscca_compressed_block_t **compressed_block,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libscca_compressed_block_initialize";

	if( compressed_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed block.",
		 function );

		return( -1 );
	}
	if( *compressed_block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid compressed block value already set.",
		 function );

		return( -1 );
	}
	if( ( data_size == 0 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	*compressed_block = memory_allocate_structure(
	                     libscca_compressed_block_t );

	if( *compressed_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *compressed_block,
	     0,
	     sizeof( libscca_compressed_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear compressed block.",
		 function );

		memory_free(
		 *compressed_block );

		*compressed_block = NULL;

		return( -1 );
	}
	( *compressed_block )->data = (uint8_t *) memory_allocate(
	                                           sizeof( uint8_t ) * data_size );

	if( ( *compressed_block )->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     ( *compressed_block )->data,
	     0,
	     sizeof( uint8_t ) * data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear compressed block.",
		 function );

		goto on_error;
	}
	( *compressed_block )->data_size = data_size;

	return( 1 );

on_error:
	if( *compressed_block != NULL )
	{
		if( ( *compressed_block )->data != NULL )
		{
			memory_free(
			 ( *compressed_block )->data );
		}
		memory_free(
		 *compressed_block );

		*compressed_block = NULL;
	}
	return( -1 );
}

/* Frees compressed block
 * Returns 1 if successful or -1 on error
 */
int libscca_compressed_block_free(
     libscca_compressed_block_t **compressed_block,
     libcerror_error_t **error )
{
	static char *function = "libscca_compressed_block_free";

	if( compressed_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed block.",
		 function );

		return( -1 );
	}
	if( *compressed_block != NULL )
	{
		if( ( *compressed_block )->data != NULL )
		{
			memory_free(
			 ( *compressed_block )->data );
		}
		memory_free(
		 *compressed_block );

		*compressed_block = NULL;
	}
	return( 1 );
}

/* Reads a compressed block
 * Returns the number of bytes of read on success or -1 on error
 */
ssize_t libscca_compressed_block_read(
         libscca_compressed_block_t *compressed_block,
         libbfio_handle_t *file_io_handle,
         off64_t compressed_block_offset,
         size_t compressed_block_size,
         libcerror_error_t **error )
{
	uint8_t *compressed_data      = NULL;
	static char *function         = "libscca_compressed_block_read";
	size_t uncompressed_data_size = 0;
	ssize_t read_count            = 0;

	if( compressed_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed block.",
		 function );

		return( -1 );
	}
	if( ( compressed_block_size == 0 )
	 || ( compressed_block_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid compressed block size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     compressed_block_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek compressed block offset: %" PRIi64 ".",
		 function,
		 compressed_block_offset );

		goto on_error;
	}
	compressed_data = (uint8_t *) memory_allocate(
	                               sizeof( uint8_t ) * compressed_block_size );

	if( compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
		      file_io_handle,
		      compressed_data,
		      compressed_block_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed block.",
		 function );

		goto on_error;
	}
	uncompressed_data_size = compressed_block->data_size;

	if( libfwnt_lzxpress_huffman_decompress(
	     compressed_data,
	     (size_t) read_count,
	     compressed_block->data,
	     &uncompressed_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
		 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
		 "%s: unable to decompress compressed data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: uncompressed data:\n",
		 function );
		libcnotify_print_data(
		 compressed_block->data,
		 compressed_block->data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	memory_free(
	 compressed_data );

	compressed_data = NULL;

	return( read_count );

on_error:
	if( compressed_data != NULL )
	{
		memory_free(
		 compressed_data );
	}
	return( -1 );
}

/* Reads a compressed block
 * Callback function for the compressed blocks list
 * Returns 1 if successful or -1 on error
 */
int libscca_compressed_block_read_element_data(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfcache_cache_t *cache,
     int element_file_index LIBSCCA_ATTRIBUTE_UNUSED,
     off64_t compressed_block_offset,
     size64_t compressed_block_size,
     uint32_t compressed_block_flags,
     uint8_t read_flags LIBSCCA_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libscca_compressed_block_t *compressed_block = NULL;
	static char *function                        = "libscca_compressed_block_read_element_data";
	size64_t uncompressed_size                   = 0;
	ssize_t read_count                           = 0;

	LIBSCCA_UNREFERENCED_PARAMETER( element_file_index )
	LIBSCCA_UNREFERENCED_PARAMETER( read_flags )

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
	if( compressed_block_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid compressed block size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( compressed_block_flags & LIBFDATA_RANGE_FLAG_IS_COMPRESSED ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: compressed range flags not set.",
		 function );

		return( -1 );
	}
	if( libfdata_list_element_get_mapped_size(
	     element,
	     &uncompressed_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element mapped size.",
		 function );

		goto on_error;
	}
	if( libscca_compressed_block_initialize(
	     &compressed_block,
	     (size_t) uncompressed_size,
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
	read_count = libscca_compressed_block_read(
	              compressed_block,
	              file_io_handle,
	              compressed_block_offset,
	              (size_t) compressed_block_size,
	              error );

	if( read_count != (ssize_t) compressed_block_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed block.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: uncompressed data:\n",
		 function );
		libcnotify_print_data(
		 compressed_block->data,
		 compressed_block->data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libfdata_list_element_set_element_value(
	     element,
	     (intptr_t *) file_io_handle,
	     cache,
	     (intptr_t *) compressed_block,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libscca_compressed_block_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set compressed block as element value.",
		 function );

		goto on_error;
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

