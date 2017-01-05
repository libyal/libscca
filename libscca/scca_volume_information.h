/*
 * The volume information definitions of a Windows Prefetch File (PF)
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

#if !defined( _SCCA_VOLUME_INFORMATION_H )
#define _SCCA_VOLUME_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct scca_volume_information_v17 scca_volume_information_v17_t;

struct scca_volume_information_v17
{
	/* The (volume) device path offset
	 * Consists of 4 bytes
	 */
	uint8_t device_path_offset[ 4 ];

	/* The (volume) device path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t device_path_number_of_characters[ 4 ];

	/* The (volume) creation time
	 * Consists of 8 bytes
	 */
	uint8_t creation_time[ 8 ];

	/* The (volume) serial number
	 * Consists of 4 bytes
	 */
	uint8_t serial_number[ 4 ];

	/* The file references offset
	 * Consists of 4 bytes
	 */
	uint8_t file_references_offset[ 4 ];

	/* The file references size
	 * Consists of 4 bytes
	 */
	uint8_t file_references_size[ 4 ];

	/* The directory strings array offset
	 * Consists of 4 bytes
	 */
	uint8_t directory_strings_array_offset[ 4 ];

	/* The number of directory strings
	 * Consists of 4 bytes
	 */
	uint8_t number_of_directory_strings[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];
};

typedef struct scca_volume_information_v23 scca_volume_information_v23_t;

struct scca_volume_information_v23
{
	/* The (volume) device path offset
	 * Consists of 4 bytes
	 */
	uint8_t device_path_offset[ 4 ];

	/* The (volume) device path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t device_path_number_of_characters[ 4 ];

	/* The (volume) creation time
	 * Consists of 8 bytes
	 */
	uint8_t creation_time[ 8 ];

	/* The (volume) serial number
	 * Consists of 4 bytes
	 */
	uint8_t serial_number[ 4 ];

	/* The file references offset
	 * Consists of 4 bytes
	 */
	uint8_t file_references_offset[ 4 ];

	/* The file references size
	 * Consists of 4 bytes
	 */
	uint8_t file_references_size[ 4 ];

	/* The directory strings array offset
	 * Consists of 4 bytes
	 */
	uint8_t directory_strings_array_offset[ 4 ];

	/* The number of directory strings
	 * Consists of 4 bytes
	 */
	uint8_t number_of_directory_strings[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 28 bytes
	 */
	uint8_t unknown2[ 28 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 28 bytes
	 */
	uint8_t unknown4[ 28 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];
};

typedef struct scca_volume_information_v30 scca_volume_information_v30_t;

struct scca_volume_information_v30
{
	/* The (volume) device path offset
	 * Consists of 4 bytes
	 */
	uint8_t device_path_offset[ 4 ];

	/* The (volume) device path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t device_path_number_of_characters[ 4 ];

	/* The (volume) creation time
	 * Consists of 8 bytes
	 */
	uint8_t creation_time[ 8 ];

	/* The (volume) serial number
	 * Consists of 4 bytes
	 */
	uint8_t serial_number[ 4 ];

	/* The file references offset
	 * Consists of 4 bytes
	 */
	uint8_t file_references_offset[ 4 ];

	/* The file references size
	 * Consists of 4 bytes
	 */
	uint8_t file_references_size[ 4 ];

	/* The directory strings array offset
	 * Consists of 4 bytes
	 */
	uint8_t directory_strings_array_offset[ 4 ];

	/* The number of directory strings
	 * Consists of 4 bytes
	 */
	uint8_t number_of_directory_strings[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 24 bytes
	 */
	uint8_t unknown2[ 24 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 24 bytes
	 */
	uint8_t unknown4[ 24 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _SCCA_VOLUME_INFORMATION_H ) */

