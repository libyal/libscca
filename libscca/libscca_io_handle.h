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

#if !defined( _LIBSCCA_IO_HANDLE_H )
#define _LIBSCCA_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libscca_filename_strings.h"
#include "libscca_libbfio.h"
#include "libscca_libcdata.h"
#include "libscca_libcerror.h"
#include "libscca_libfcache.h"
#include "libscca_libfdata.h"
#include "libscca_libfvalue.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *scca_file_signature;
extern const char *scca_mam_file_signature_win10;

typedef struct libscca_io_handle libscca_io_handle_t;

struct libscca_io_handle
{
	/* The file type
	 */
	uint8_t file_type;

	/* The uncompressed data size
	 */
	uint32_t uncompressed_data_size;

	/* The format version
	 */
	uint32_t format_version;

	/* The file size
	 */
	uint32_t file_size;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libscca_io_handle_initialize(
     libscca_io_handle_t **io_handle,
     libcerror_error_t **error );

int libscca_io_handle_free(
     libscca_io_handle_t **io_handle,
     libcerror_error_t **error );

int libscca_io_handle_clear(
     libscca_io_handle_t *io_handle,
     libcerror_error_t **error );

int libscca_io_handle_read_compressed_file_header(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libscca_io_handle_read_compressed_blocks(
     libscca_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_t *compressed_blocks_list,
     libfcache_cache_t *compressed_blocks_cache,
     libcerror_error_t **error );

int libscca_io_handle_read_uncompressed_file_header(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint8_t *executable_filename,
     size_t *executable_filename_size,
     uint32_t *prefetch_hash,
     libcerror_error_t **error );

int libscca_io_handle_read_file_metrics_array(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t file_offset,
     uint32_t number_of_entries,
     libscca_filename_strings_t *filename_strings,
     libcdata_array_t *file_metrics_array,
     libcerror_error_t **error );

int libscca_io_handle_read_trace_chain_array(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t file_offset,
     uint32_t number_of_entries,
     libcerror_error_t **error );

int libscca_io_handle_read_volumes_information(
     libscca_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     uint32_t volumes_information_offset,
     uint32_t volumes_information_size,
     uint32_t number_of_volumes,
     libcdata_array_t *volumes_array,
     libcerror_error_t **error );

ssize_t libscca_io_handle_read_segment_data(
         intptr_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags,
         uint8_t read_flags,
         libcerror_error_t **error );

off64_t libscca_io_handle_seek_segment_offset(
         intptr_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         off64_t segment_offset,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_IO_HANDLE_H ) */

