/*
 * File information functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libscca_debug.h"
#include "libscca_definitions.h"
#include "libscca_file_information.h"
#include "libscca_io_handle.h"
#include "libscca_libbfio.h"
#include "libscca_libcerror.h"
#include "libscca_libcnotify.h"
#include "libscca_libfdata.h"
#include "libscca_libfdatetime.h"

#include "scca_file_information.h"

/* Creates file information
 * Make sure the value file_information is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libscca_file_information_initialize(
     libscca_file_information_t **file_information,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_information_initialize";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( *file_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file information value already set.",
		 function );

		return( -1 );
	}
	*file_information = memory_allocate_structure(
	                     libscca_file_information_t );

	if( *file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file information.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_information,
	     0,
	     sizeof( libscca_file_information_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_information != NULL )
	{
		memory_free(
		 *file_information );

		*file_information = NULL;
	}
	return( -1 );
}

/* Frees file information
 * Returns 1 if successful or -1 on error
 */
int libscca_file_information_free(
     libscca_file_information_t **file_information,
     libcerror_error_t **error )
{
	static char *function = "libscca_file_information_free";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( *file_information != NULL )
	{
		memory_free(
		 *file_information );

		*file_information = NULL;
	}
	return( 1 );
}

/* Reads the file information
 * Returns 1 if successful or -1 on error
 */
int libscca_file_information_read(
     libscca_file_information_t *file_information,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     libscca_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	uint8_t *file_information_data = NULL;
	static char *function          = "libscca_file_information_read";
	size_t read_size               = 0;
	ssize_t read_count             = 0;
	int last_run_time_index        = 0;
	int number_of_last_run_times   = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit           = 0;
	uint32_t value_32bit           = 0;
	int result                     = 0;
#endif

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( io_handle->format_version != 17 )
	 && ( io_handle->format_version != 23 )
	 && ( io_handle->format_version != 26 )
	 && ( io_handle->format_version != 30 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported format version.",
		 function );

		return( -1 );
	}
	if( io_handle->format_version == 17 )
	{
		read_size = sizeof( scca_file_information_v17_t );
	}
	else if( io_handle->format_version == 23 )
	{
		read_size = sizeof( scca_file_information_v23_t );
	}
	else if( ( io_handle->format_version == 26 )
	      || ( io_handle->format_version == 30 ) )
	{
		read_size = sizeof( scca_file_information_v26_t );
	}
	file_information_data = (uint8_t *) memory_allocate(
	                                     sizeof( uint8_t ) * read_size );

	if( file_information_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file information data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              file_information_data,
	              read_size,
	              0,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file information data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file information data:\n",
		 function );
		libcnotify_print_data(
		 file_information_data,
		 read_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->metrics_array_offset,
	 file_information->metrics_array_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->number_of_file_metrics_entries,
	 file_information->number_of_file_metrics_entries );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->trace_chain_array_offset,
	 file_information->trace_chain_array_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->number_of_trace_chain_array_entries,
	 file_information->number_of_trace_chain_array_entries );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->filename_strings_offset,
	 file_information->filename_strings_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->filename_strings_size,
	 file_information->filename_strings_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->volumes_information_offset,
	 file_information->volumes_information_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->number_of_volumes,
	 file_information->number_of_volumes );

	byte_stream_copy_to_uint32_little_endian(
	 ( (scca_file_information_v17_t *) file_information_data )->volumes_information_size,
	 file_information->volumes_information_size );

	if( io_handle->format_version < 26 )
	{
		number_of_last_run_times = 1;
	}
	else
	{
		number_of_last_run_times = 8;
	}
	for( last_run_time_index = 0;
	     last_run_time_index < number_of_last_run_times;
	     last_run_time_index++ )
	{
		if( io_handle->format_version == 17 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 &( ( (scca_file_information_v17_t *) file_information_data )->last_run_time[ last_run_time_index * 8 ] ),
			 file_information->last_run_time[ last_run_time_index ] );
		}
		else if( io_handle->format_version == 23 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 &( ( (scca_file_information_v23_t *) file_information_data )->last_run_time[ last_run_time_index * 8 ] ),
			 file_information->last_run_time[ last_run_time_index ] );
		}
		else if( ( io_handle->format_version == 26 )
		      || ( io_handle->format_version == 30 ) )
		{
			byte_stream_copy_to_uint64_little_endian(
			 &( ( (scca_file_information_v26_t *) file_information_data )->last_run_time[ last_run_time_index * 8 ] ),
			 file_information->last_run_time[ last_run_time_index ] );
		}
	}
	if( io_handle->format_version == 17 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_information_v17_t *) file_information_data )->run_count,
		 file_information->run_count );
	}
	else if( io_handle->format_version == 23 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_information_v23_t *) file_information_data )->run_count,
		 file_information->run_count );
	}
	else if( ( io_handle->format_version == 26 )
	      || ( io_handle->format_version == 30 ) )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (scca_file_information_v26_t *) file_information_data )->run_count,
		 file_information->run_count );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: metrics array offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->metrics_array_offset );

		libcnotify_printf(
		 "%s: number of file metrics entries\t\t: %" PRIu32 "\n",
		 function,
		 file_information->number_of_file_metrics_entries );

		libcnotify_printf(
		 "%s: trace chain array offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->trace_chain_array_offset );

		libcnotify_printf(
		 "%s: number of trace chain array entries\t: %" PRIu32 "\n",
		 function,
		 file_information->number_of_trace_chain_array_entries );

		libcnotify_printf(
		 "%s: filename strings offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->filename_strings_offset );

		libcnotify_printf(
		 "%s: filename strings size\t\t\t: %" PRIu32 "\n",
		 function,
		 file_information->filename_strings_size );

		libcnotify_printf(
		 "%s: volumes information offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->volumes_information_offset );

		libcnotify_printf(
		 "%s: number of volumes\t\t\t: %" PRIu32 "\n",
		 function,
		 file_information->number_of_volumes );

		libcnotify_printf(
		 "%s: volumes information size\t\t\t: %" PRIu32 "\n",
		 function,
		 file_information->volumes_information_size );

		if( io_handle->format_version == 23 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_information_v23_t *) file_information_data )->unknown3c,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown3c\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
		for( last_run_time_index = 0;
		     last_run_time_index < number_of_last_run_times;
		     last_run_time_index++ )
		{
			if( io_handle->format_version == 17 )
			{
				result = libscca_debug_print_filetime_value(
					  function,
					  "last run time: %d\t\t\t\t",
				          &( ( (scca_file_information_v17_t *) file_information_data )->last_run_time[ last_run_time_index * 8 ] ),
					  8,
					  LIBFDATETIME_ENDIAN_LITTLE,
				          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					  error );
			}
			else if( io_handle->format_version == 23 )
			{
				result = libscca_debug_print_filetime_value(
					  function,
					  "last run time: %d\t\t\t\t",
				          &( ( (scca_file_information_v23_t *) file_information_data )->last_run_time[ last_run_time_index * 8 ] ),
					  8,
					  LIBFDATETIME_ENDIAN_LITTLE,
				          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					  error );
			}
			else if( ( io_handle->format_version == 26 )
			      || ( io_handle->format_version == 30 ) )
			{
				result = libscca_debug_print_filetime_value(
					  function,
					  "last run time: %d\t\t\t\t",
				          &( ( (scca_file_information_v26_t *) file_information_data )->last_run_time[ last_run_time_index * 8 ] ),
					  8,
					  LIBFDATETIME_ENDIAN_LITTLE,
				          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					  error );
			}
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print filetime value.",
				 function );

				goto on_error;
			}
		}
		libcnotify_printf(
		 "%s: unknown4:\n",
		 function );

		if( io_handle->format_version == 17 )
		{
			libcnotify_print_data(
			 ( (scca_file_information_v17_t *) file_information_data )->unknown4,
			 16,
			 0 );
		}
		else if( io_handle->format_version == 23 )
		{
			libcnotify_print_data(
			 ( (scca_file_information_v23_t *) file_information_data )->unknown4,
			 16,
			 0 );
		}
		else if( ( io_handle->format_version == 26 )
		      || ( io_handle->format_version == 30 ) )
		{
			libcnotify_print_data(
			 ( (scca_file_information_v26_t *) file_information_data )->unknown4,
			 16,
			 0 );
		}
		libcnotify_printf(
		 "%s: run count\t\t\t\t: %" PRIu32 "\n",
		 function,
		 file_information->run_count );

		if( io_handle->format_version == 17 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_information_v17_t *) file_information_data )->unknown5,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown5\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "\n" );
		}
		else if( io_handle->format_version == 23 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_information_v23_t *) file_information_data )->unknown5,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown5\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: unknown6:\n",
			 function );
			libcnotify_print_data(
			 ( (scca_file_information_v23_t *) file_information_data )->unknown6,
			 80,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
		else if( ( io_handle->format_version == 26 )
		      || ( io_handle->format_version == 30 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_information_v26_t *) file_information_data )->unknown5a,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown5a\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (scca_file_information_v26_t *) file_information_data )->unknown5b,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown5b\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: unknown6:\n",
			 function );
			libcnotify_print_data(
			 ( (scca_file_information_v26_t *) file_information_data )->unknown6,
			 88,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif
	memory_free(
	 file_information_data );

	return( 1 );

on_error:
	if( file_information_data != NULL )
	{
		memory_free(
		 file_information_data );
	}
	return( -1 );
}

