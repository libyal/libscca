/*
 * The file metrics array definitions of a Windows Prefetch File (PF)
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

#if !defined( _SCCA_METRICS_ARRAY_H )
#define _SCCA_METRICS_ARRAY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct scca_file_metrics_array_entry_v17 scca_file_metrics_array_entry_v17_t;

struct scca_file_metrics_array_entry_v17
{
	/* The start time
	 * Consists of 4 bytes
	 */
	uint8_t start_time[ 4 ];

	/* The duration time
	 * Consists of 4 bytes
	 */
	uint8_t duration[ 4 ];

	/* The filename strings offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_string_offset[ 4 ];

	/* The filename string number of characters
	 * Consists of 4 bytes
	 */
	uint8_t filename_string_numbers_of_characters[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];
};

typedef struct scca_file_metrics_array_entry_v23 scca_file_metrics_array_entry_v23_t;

struct scca_file_metrics_array_entry_v23
{
	/* The start time
	 * Consists of 4 bytes
	 */
	uint8_t start_time[ 4 ];

	/* The duration time
	 * Consists of 4 bytes
	 */
	uint8_t duration[ 4 ];

	/* The average duration time
	 * Consists of 4 bytes
	 */
	uint8_t average_duration[ 4 ];

	/* The filename string offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_string_offset[ 4 ];

	/* The filename string number of characters
	 * Consists of 4 bytes
	 */
	uint8_t filename_string_numbers_of_characters[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* The NTFS file reference
	 * Consists of 8 bytes
	 */
	uint8_t file_reference[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _SCCA_METRICS_ARRAY_H ) */

