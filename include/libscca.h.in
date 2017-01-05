/*
 * Library to access the Windows Prefetch File (PF) format
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

#if !defined( _LIBSCCA_H )
#define _LIBSCCA_H

#include <libscca/codepage.h>
#include <libscca/definitions.h>
#include <libscca/error.h>
#include <libscca/extern.h>
#include <libscca/features.h>
#include <libscca/types.h>

#include <stdio.h>

#if defined( LIBSCCA_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBSCCA_EXTERN \
const char *libscca_get_version(
             void );

/* Returns the access flags for reading
 */
LIBSCCA_EXTERN \
int libscca_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_get_codepage(
     int *codepage,
     libscca_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_set_codepage(
     int codepage,
     libscca_error_t **error );

/* Determines if a file contains a SCCA file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_check_file_signature(
     const char *filename,
     libscca_error_t **error );

#if defined( LIBSCCA_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a SCCA file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_check_file_signature_wide(
     const wchar_t *filename,
     libscca_error_t **error );

#endif /* defined( LIBSCCA_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBSCCA_HAVE_BFIO )

/* Determines if a file contains a SCCA file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libscca_error_t **error );

#endif /* defined( LIBSCCA_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBSCCA_EXTERN \
void libscca_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_notify_set_stream(
     FILE *stream,
     libscca_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_notify_stream_open(
     const char *filename,
     libscca_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_notify_stream_close(
     libscca_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBSCCA_EXTERN \
void libscca_error_free(
      libscca_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_error_fprint(
     libscca_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_error_sprint(
     libscca_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_error_backtrace_fprint(
     libscca_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_error_backtrace_sprint(
     libscca_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_initialize(
     libscca_file_t **file,
     libscca_error_t **error );

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_free(
     libscca_file_t **file,
     libscca_error_t **error );

/* Signals the libscca file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_signal_abort(
     libscca_file_t *file,
     libscca_error_t **error );

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_open(
     libscca_file_t *file,
     const char *filename,
     int access_flags,
     libscca_error_t **error );

#if defined( LIBSCCA_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_open_wide(
     libscca_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libscca_error_t **error );

#endif /* defined( LIBSCCA_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBSCCA_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_open_file_io_handle(
     libscca_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libscca_error_t **error );

#endif /* defined( LIBSCCA_HAVE_BFIO ) */

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_close(
     libscca_file_t *file,
     libscca_error_t **error );

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_format_version(
     libscca_file_t *file,
     uint32_t *format_version,
     libscca_error_t **error );

/* Retrieves the size of a specific UTF-8 encoded executable filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf8_executable_filename_size(
     libscca_file_t *file,
     size_t *utf8_string_size,
     libscca_error_t **error );

/* Retrieves a specific UTF-8 encoded executable filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf8_executable_filename(
     libscca_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libscca_error_t **error );

/* Retrieves the size of a specific UTF-16 encoded executable filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf16_executable_filename_size(
     libscca_file_t *file,
     size_t *utf16_string_size,
     libscca_error_t **error );

/* Retrieves a specific UTF-16 encoded executable filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf16_executable_filename(
     libscca_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libscca_error_t **error );

/* Retrieves the prefetch hash
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_prefetch_hash(
     libscca_file_t *file,
     uint32_t *prefetch_hash,
     libscca_error_t **error );

/* Retrieves a specific last run time
 * The timestamp is a 64-bit FILETIME date and time value
 * Files of format version 23 and earlier contain a single last run time
 * Files of format version 26 and later contain up to 8 last run times
 * A value if 0 means the last run time is not set
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_last_run_time(
     libscca_file_t *file,
     int last_run_time_index,
     uint64_t *filetime,
     libscca_error_t **error );

/* Retrieves the run count
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_run_count(
     libscca_file_t *file,
     uint32_t *run_count,
     libscca_error_t **error );

/* Retrieves the number of file metrics entries
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_number_of_file_metrics_entries(
     libscca_file_t *file,
     int *number_of_entries,
     libscca_error_t **error );

/* Retrieves a specific file metrics entry
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_file_metrics_entry(
     libscca_file_t *file,
     int entry_index,
     libscca_file_metrics_t **file_metrics,
     libscca_error_t **error );

/* Retrieves the number of filenames
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_number_of_filenames(
     libscca_file_t *file,
     int *number_of_filenames,
     libscca_error_t **error );

/* Retrieves the size of a specific UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf8_filename_size(
     libscca_file_t *file,
     int filename_index,
     size_t *utf8_string_size,
     libscca_error_t **error );

/* Retrieves a specific UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf8_filename(
     libscca_file_t *file,
     int filename_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libscca_error_t **error );

/* Retrieves the size of a specific UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf16_filename_size(
     libscca_file_t *file,
     int filename_index,
     size_t *utf16_string_size,
     libscca_error_t **error );

/* Retrieves a specific UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_utf16_filename(
     libscca_file_t *file,
     int filename_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libscca_error_t **error );

/* Retrieves the number of volumes
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_number_of_volumes(
     libscca_file_t *file,
     int *number_of_volumes,
     libscca_error_t **error );

/* Retrieves a specific volume information
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_get_volume_information(
     libscca_file_t *file,
     int volume_index,
     libscca_volume_information_t **volume_information,
     libscca_error_t **error );

/* -------------------------------------------------------------------------
 * File metrics functions
 * ------------------------------------------------------------------------- */

/* Frees file metrics
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_metrics_free(
     libscca_file_metrics_t **file_metrics,
     libscca_error_t **error );

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf8_filename_size(
     libscca_file_metrics_t *file_metrics,
     size_t *utf8_string_size,
     libscca_error_t **error );

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf8_filename(
     libscca_file_metrics_t *file_metrics,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libscca_error_t **error );

/* Retrieves the size of the UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf16_filename_size(
     libscca_file_metrics_t *file_metrics,
     size_t *utf16_string_size,
     libscca_error_t **error );

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_metrics_get_utf16_filename(
     libscca_file_metrics_t *file_metrics,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libscca_error_t **error );

/* Retrieves the NTFS file reference
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_metrics_get_file_reference(
     libscca_file_metrics_t *file_metrics,
     uint64_t *file_reference,
     libscca_error_t **error );

/* -------------------------------------------------------------------------
 * Volume information functions
 * ------------------------------------------------------------------------- */

/* Frees volume information
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_volume_information_free(
     libscca_volume_information_t **volume_information,
     libscca_error_t **error );

/* Retrieves the 64-bit FILETIME value containing the volume creation date and time
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_volume_information_get_creation_time(
     libscca_volume_information_t *volume_information,
     uint64_t *filetime,
     libscca_error_t **error );

/* Retrieves the serial number
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_volume_information_get_serial_number(
     libscca_volume_information_t *volume_information,
     uint32_t *serial_number,
     libscca_error_t **error );

/* Retrieves the size of the UTF-8 encoded device path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_volume_information_get_utf8_device_path_size(
     libscca_volume_information_t *volume_information,
     size_t *utf8_string_size,
     libscca_error_t **error );

/* Retrieves the UTF-8 encoded device path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_volume_information_get_utf8_device_path(
     libscca_volume_information_t *volume_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libscca_error_t **error );

/* Retrieves the size of the UTF-16 encoded device path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_volume_information_get_utf16_device_path_size(
     libscca_volume_information_t *volume_information,
     size_t *utf16_string_size,
     libscca_error_t **error );

/* Retrieves the UTF-16 encoded device path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_volume_information_get_utf16_device_path(
     libscca_volume_information_t *volume_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libscca_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_H ) */

