/*
 * The file information definitions of a Windows Prefetch File (PF)
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

#if !defined( _SCCA_FILE_INFORMATION_H )
#define _SCCA_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct scca_file_information_v17 scca_file_information_v17_t;

struct scca_file_information_v17
{
	/* The offset of the metrics array
	 * Consists of 4 bytes
	 */
	uint8_t metrics_array_offset[ 4 ];

	/* The number of file metrics array entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_file_metrics_entries[ 4 ];

	/* The offset of the trace chain array
	 * Consists of 4 bytes
	 */
	uint8_t trace_chain_array_offset[ 4 ];

	/* The number of trace chain array entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_trace_chain_array_entries[ 4 ];

	/* The filename strings offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_strings_offset[ 4 ];

	/* The filename strings size
	 * Consists of 4 bytes
	 */
	uint8_t filename_strings_size[ 4 ];

	/* The volumes information offset
	 * Consists of 4 bytes
	 */
	uint8_t volumes_information_offset[ 4 ];

	/* The number of volumes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_volumes[ 4 ];

	/* The volumes information size
	 * Consists of 4 bytes
	 */
	uint8_t volumes_information_size[ 4 ];

	/* The last run date and time
	 * Consists of 8 bytes
	 * Contain a FILETIME
	 */
	uint8_t last_run_time[ 8 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown4[ 16 ];

	/* The run count
	 * Consists of 4 bytes
	 */
	uint8_t run_count[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];
};

typedef struct scca_file_information_v23 scca_file_information_v23_t;

struct scca_file_information_v23
{
	/* The offset of the metrics array
	 * Consists of 4 bytes
	 */
	uint8_t metrics_array_offset[ 4 ];

	/* The number of file metrics array entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_file_metrics_entries[ 4 ];

	/* The offset of the trace chain array
	 * Consists of 4 bytes
	 */
	uint8_t trace_chain_array_offset[ 4 ];

	/* The number of trace chain array entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_trace_chain_array_entries[ 4 ];

	/* The filename strings offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_strings_offset[ 4 ];

	/* The filename strings size
	 * Consists of 4 bytes
	 */
	uint8_t filename_strings_size[ 4 ];

	/* The volumes information offset
	 * Consists of 4 bytes
	 */
	uint8_t volumes_information_offset[ 4 ];

	/* The number of volumes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_volumes[ 4 ];

	/* The volumes information size
	 * Consists of 4 bytes
	 */
	uint8_t volumes_information_size[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown3c[ 8 ];

	/* The last run date and time
	 * Consists of 8 bytes
	 * Contain a FILETIME
	 */
	uint8_t last_run_time[ 8 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown4[ 16 ];

	/* The run count
	 * Consists of 4 bytes
	 */
	uint8_t run_count[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 80 bytes
	 */
	uint8_t unknown6[ 80 ];
};

typedef struct scca_file_information_v26 scca_file_information_v26_t;

struct scca_file_information_v26
{
	/* The offset of the metrics array
	 * Consists of 4 bytes
	 */
	uint8_t metrics_array_offset[ 4 ];

	/* The number of file metrics array entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_file_metrics_entries[ 4 ];

	/* The offset of the trace chain array
	 * Consists of 4 bytes
	 */
	uint8_t trace_chain_array_offset[ 4 ];

	/* The number of trace chain array entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_trace_chain_array_entries[ 4 ];

	/* The filename strings offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_strings_offset[ 4 ];

	/* The filename strings size
	 * Consists of 4 bytes
	 */
	uint8_t filename_strings_size[ 4 ];

	/* The volumes information offset
	 * Consists of 4 bytes
	 */
	uint8_t volumes_information_offset[ 4 ];

	/* The number of volumes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_volumes[ 4 ];

	/* The volumes information size
	 * Consists of 4 bytes
	 */
	uint8_t volumes_information_size[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown3c[ 8 ];

	/* The last run date and time
	 * Consists of 64 bytes
	 * Contains an array of FILETIME
	 */
	uint8_t last_run_time[ 64 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown4[ 16 ];

	/* The run count
	 * Consists of 4 bytes
	 */
	uint8_t run_count[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5b[ 4 ];

	/* Unknown
	 * Consists of 88 bytes
	 */
	uint8_t unknown6[ 88 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _SCCA_FILE_INFORMATION_H ) */

