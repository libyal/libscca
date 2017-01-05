/*
 * The compressed blocks stream functions
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

#if !defined( _LIBSCCA_COMPRESSED_BLOCKS_STREAM_H )
#define _LIBSCCA_COMPRESSED_BLOCKS_STREAM_H

#include <common.h>
#include <types.h>

#include "libscca_libcerror.h"
#include "libscca_libfcache.h"
#include "libscca_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_compressed_blocks_stream_data_handle libscca_compressed_blocks_stream_data_handle_t;

struct libscca_compressed_blocks_stream_data_handle
{
	/* The current offset
	 */
	off64_t current_offset;

	/* The compressed blocks list
	 */
	libfdata_list_t *compressed_blocks_list;

	/* The compressed blocks cache
	 */
	libfcache_cache_t *compressed_blocks_cache;
};

int libscca_compressed_blocks_stream_data_handle_initialize(
     libscca_compressed_blocks_stream_data_handle_t **data_handle,
     libcerror_error_t **error );

int libscca_compressed_blocks_stream_data_handle_free(
     libscca_compressed_blocks_stream_data_handle_t **data_handle,
     libcerror_error_t **error );

ssize_t libscca_compressed_blocks_stream_data_handle_read_segment_data(
         libscca_compressed_blocks_stream_data_handle_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags,
         uint8_t read_flags,
         libcerror_error_t **error );

off64_t libscca_compressed_blocks_stream_data_handle_seek_segment_offset(
         libscca_compressed_blocks_stream_data_handle_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         off64_t segment_offset,
         libcerror_error_t **error );

int libscca_compressed_blocks_stream_initialize(
     libfdata_stream_t **compressed_blocks_stream,
     libfdata_list_t *compressed_blocks_list,
     libfcache_cache_t *compressed_blocks_cache,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_COMPRESSED_BLOCKS_STREAM_H ) */

