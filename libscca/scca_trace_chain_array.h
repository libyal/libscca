/*
 * The trace chain array definitions of a Windows Prefetch File (PF)
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

#if !defined( _SCCA_TRACE_CHAIN_ARRAY_H )
#define _SCCA_TRACE_CHAIN_ARRAY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct scca_trace_chain_array_entry_v17 scca_trace_chain_array_entry_v17_t;

struct scca_trace_chain_array_entry_v17
{
	/* The next array entry index
	 * Consists of 4 bytes
	 */
	uint8_t next_array_entry_index[ 4 ];

	/* The total block load count
	 * Consists of 4 bytes
	 */
	uint8_t total_block_load_count[ 4 ];

	/* Unknown
	 * Consists of 1 byte
	 */
	uint8_t unknown1;

	/* Unknown
	 * Consists of 1 byte
	 */
	uint8_t unknown2;

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown3[ 2 ];
};

typedef struct scca_trace_chain_array_entry_v30 scca_trace_chain_array_entry_v30_t;

struct scca_trace_chain_array_entry_v30
{
	/* The total block load count
	 * Consists of 4 bytes
	 */
	uint8_t total_block_load_count[ 4 ];

	/* Unknown
	 * Consists of 1 byte
	 */
	uint8_t unknown1;

	/* Unknown
	 * Consists of 1 byte
	 */
	uint8_t unknown2;

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown3[ 2 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _SCCA_TRACE_CHAIN_ARRAY_H ) */

