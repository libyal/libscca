/*
 * The file header definition of a Windows Prefetch File (PF)
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

#if !defined( _SCCA_FILE_HEADER_H )
#define _SCCA_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct scca_file_header scca_file_header_t;

struct scca_file_header
{
	/* Format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* Signature
	 * Consists of 4 bytes
	 * "SCCA"
	 */
	uint8_t signature[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The file size
	 * Consists of 4 bytes
	 */
	uint8_t file_size[ 4 ];

	/* The executable filename
	 * Consists of 60 bytes
	 */
	uint8_t executable_filename[ 60 ];

	/* The prefetch hash
	 * Consists of 4 bytes
	 */
	uint8_t prefetch_hash[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];
};

typedef struct scca_mam_file_header scca_mam_file_header_t;

struct scca_mam_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * "MAM\x04"
	 */
	uint8_t signature[ 4 ];

	/* Uncompressed data size
	 * Consists of 4 bytes
	 */
	uint8_t uncompressed_data_size[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _SCCA_FILE_HEADER_H ) */

