/*
 * File functions
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

#if !defined( _LIBSCCA_INTERNAL_FILE_H )
#define _LIBSCCA_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include "libscca_extern.h"
#include "libscca_file_information.h"
#include "libscca_filename_strings.h"
#include "libscca_io_handle.h"
#include "libscca_libbfio.h"
#include "libscca_libcdata.h"
#include "libscca_libcerror.h"
#include "libscca_libfcache.h"
#include "libscca_libfdata.h"
#include "libscca_libfvalue.h"
#include "libscca_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libscca_internal_file libscca_internal_file_t;

struct libscca_internal_file
{
	/* The IO handle
	 */
	libscca_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The compressed blocks list
	 */
	libfdata_list_t *compressed_blocks_list;

	/* The compressed blocks cache
	 */
	libfcache_cache_t *compressed_blocks_cache;

	/* The uncompressed data stream
	 */
	libfdata_stream_t *uncompressed_data_stream;

	/* The executable filename
	 */
	uint8_t executable_filename[ 60 ];

	/* The executable filename size
	 */
	size_t executable_filename_size;

	/* The prefetch hash
	 */
	uint32_t prefetch_hash;

	/* The file information
	 */
	libscca_file_information_t *file_information;

	/* The file metrics array
	 */
	libcdata_array_t *file_metrics_array;

	/* The filename strings
	 */
	libscca_filename_strings_t *filename_strings;

	/* The volumes array
	 */
	libcdata_array_t *volumes_array;
};

LIBSCCA_EXTERN \
int libscca_file_initialize(
     libscca_file_t **file,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_free(
     libscca_file_t **file,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_signal_abort(
     libscca_file_t *file,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_open(
     libscca_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBSCCA_EXTERN \
int libscca_file_open_wide(
     libscca_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );
#endif

LIBSCCA_EXTERN \
int libscca_file_open_file_io_handle(
     libscca_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_close(
     libscca_file_t *file,
     libcerror_error_t **error );

int libscca_file_open_read(
     libscca_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_format_version(
     libscca_file_t *file,
     uint32_t *format_version,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf8_executable_filename_size(
     libscca_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf8_executable_filename(
     libscca_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf16_executable_filename_size(
     libscca_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf16_executable_filename(
     libscca_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_prefetch_hash(
     libscca_file_t *file,
     uint32_t *prefetch_hash,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_last_run_time(
     libscca_file_t *file,
     int last_run_time_index,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_run_count(
     libscca_file_t *file,
     uint32_t *run_count,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_number_of_file_metrics_entries(
     libscca_file_t *file,
     int *number_of_entries,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_file_metrics_entry(
     libscca_file_t *file,
     int entry_index,
     libscca_file_metrics_t **file_metrics,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_number_of_filenames(
     libscca_file_t *file,
     int *number_of_filenames,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf8_filename_size(
     libscca_file_t *file,
     int filename_index,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf8_filename(
     libscca_file_t *file,
     int filename_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf16_filename_size(
     libscca_file_t *file,
     int filename_index,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_utf16_filename(
     libscca_file_t *file,
     int filename_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_number_of_volumes(
     libscca_file_t *file,
     int *number_of_volumes,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_get_volume_information(
     libscca_file_t *file,
     int volume_index,
     libscca_volume_information_t **volume_information,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_INTERNAL_FILE_H ) */

