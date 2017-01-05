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

#if !defined( _LIBSCCA_COMPRESSED_BLOCK_H )
#define _LIBSCCA_COMPRESSED_BLOCK_H

#include <common.h>
#include <types.h>

#include "libscca_io_handle.h"
#include "libscca_libcerror.h"
#include "libscca_libfcache.h"
#include "libscca_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_compressed_block libscca_compressed_block_t;

struct libscca_compressed_block
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int libscca_compressed_block_initialize(
     libscca_compressed_block_t **compressed_block,
     size_t data_size,
     libcerror_error_t **error );

int libscca_compressed_block_free(
     libscca_compressed_block_t **compressed_block,
     libcerror_error_t **error );

ssize_t libscca_compressed_block_read(
         libscca_compressed_block_t *compressed_block,
         libbfio_handle_t *file_io_handle,
         off64_t compressed_block_offset,
         size_t compressed_block_size,
         libcerror_error_t **error );

int libscca_compressed_block_read_element_data(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfcache_cache_t *cache,
     int element_file_index,
     off64_t compressed_block_offset,
     size64_t compressed_block_size,
     uint32_t compressed_block_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_COMPRESSED_BLOCK_H ) */

