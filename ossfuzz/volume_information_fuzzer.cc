/*
 * OSS-Fuzz target for libscca volume information type
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libscca.h"

#if !defined( LIBSCCA_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBSCCA_EXTERN \
int libscca_file_open_file_io_handle(
     libscca_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libscca_error_t **error );

#endif /* !defined( LIBSCCA_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t utf8_string[ 512 ];
	uint16_t utf16_string[ 256 ];

	libbfio_handle_t *file_io_handle                 = NULL;
	libscca_file_t *file                             = NULL;
	libscca_volume_information_t *volume_information = NULL;
	size_t utf8_string_size                          = 0;
	size_t utf16_string_size                         = 0;
	uint64_t creation_time                           = 0;
	uint32_t serial_number                           = 0;
	int number_of_volumes                            = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libscca_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libscca_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBSCCA_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libscca;
	}
	if( libscca_file_get_number_of_volumes(
	     file,
	     &number_of_volumes,
	     NULL ) != 1 )
	{
		goto on_error_libscca;
	}
	if( number_of_volumes > 0 )
	{
		if( libscca_file_get_volume_information(
		     file,
		     0,
		     &volume_information,
		     NULL ) != 1 )
		{
			goto on_error_libscca;
		}
		if( libscca_volume_information_get_creation_time(
		     volume_information,
		     &creation_time,
		     NULL ) != 1 )
		{
			goto on_error_libscca_volume_information;
		}
		if( libscca_volume_information_get_serial_number(
		     volume_information,
		     &serial_number,
		     NULL ) != 1 )
		{
			goto on_error_libscca_volume_information;
		}
		if( libscca_volume_information_get_utf8_device_path_size(
		     volume_information,
		     &utf8_string_size,
		     NULL ) != 1 )
		{
			goto on_error_libscca_volume_information;
		}
		if( libscca_volume_information_get_utf8_device_path(
		     volume_information,
		     utf8_string,
		     512,
		     NULL ) != 1 )
		{
			goto on_error_libscca_volume_information;
		}
		if( libscca_volume_information_get_utf16_device_path_size(
		     volume_information,
		     &utf16_string_size,
		     NULL ) != 1 )
		{
			goto on_error_libscca_volume_information;
		}
		if( libscca_volume_information_get_utf16_device_path(
		     volume_information,
		     utf16_string,
		     256,
		     NULL ) != 1 )
		{
			goto on_error_libscca_volume_information;
		}
on_error_libscca_volume_information:
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	libscca_file_close(
	 file,
	 NULL );

on_error_libscca:
	libscca_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
