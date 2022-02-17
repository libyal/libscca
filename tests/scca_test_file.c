/*
 * Library file type test program
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "scca_test_functions.h"
#include "scca_test_getopt.h"
#include "scca_test_libbfio.h"
#include "scca_test_libcerror.h"
#include "scca_test_libscca.h"
#include "scca_test_macros.h"
#include "scca_test_memory.h"

#include "../libscca/libscca_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make scca_test_file generate verbose output
#define SCCA_TEST_FILE_VERBOSE
 */

#if !defined( LIBSCCA_HAVE_BFIO )

LIBSCCA_EXTERN \
int libscca_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_file_open_file_io_handle(
     libscca_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libscca_error_t **error );

#endif /* !defined( LIBSCCA_HAVE_BFIO ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int scca_test_file_open_source(
     libscca_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "scca_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libscca_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libscca_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBSCCA_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libscca_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int scca_test_file_close_source(
     libscca_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "scca_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libscca_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libscca_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libscca_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libscca_file_t *file            = NULL;
	int result                      = 0;

#if defined( HAVE_SCCA_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libscca_file_initialize(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_file_free(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_initialize(
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = (libscca_file_t *) 0x12345678UL;

	result = libscca_file_initialize(
	          &file,
	          &error );

	file = NULL;

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_SCCA_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libscca_file_initialize with malloc failing
		 */
		scca_test_malloc_attempts_before_fail = test_number;

		result = libscca_file_initialize(
		          &file,
		          &error );

		if( scca_test_malloc_attempts_before_fail != -1 )
		{
			scca_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libscca_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			SCCA_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			SCCA_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			SCCA_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libscca_file_initialize with memset failing
		 */
		scca_test_memset_attempts_before_fail = test_number;

		result = libscca_file_initialize(
		          &file,
		          &error );

		if( scca_test_memset_attempts_before_fail != -1 )
		{
			scca_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libscca_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			SCCA_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			SCCA_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			SCCA_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_SCCA_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libscca_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_file_free function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libscca_file_free(
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_open function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libscca_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = scca_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_file_initialize(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libscca_file_open(
	          file,
	          narrow_source,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_open(
	          NULL,
	          narrow_source,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_open(
	          file,
	          NULL,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_open(
	          file,
	          narrow_source,
	          -1,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libscca_file_open(
	          file,
	          narrow_source,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libscca_file_free(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libscca_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libscca_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libscca_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = scca_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_file_initialize(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libscca_file_open_wide(
	          file,
	          wide_source,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_open_wide(
	          NULL,
	          wide_source,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_open_wide(
	          file,
	          NULL,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_open_wide(
	          file,
	          wide_source,
	          -1,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libscca_file_open_wide(
	          file,
	          wide_source,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libscca_file_free(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libscca_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libscca_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libscca_file_t *file             = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_file_initialize(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libscca_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libscca_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBSCCA_OPEN_READ,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libscca_file_free(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libscca_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_file_close function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libscca_file_close(
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_open and libscca_file_close functions
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libscca_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libscca_file_initialize(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libscca_file_open_wide(
	          file,
	          source,
	          LIBSCCA_OPEN_READ,
	          &error );
#else
	result = libscca_file_open(
	          file,
	          source,
	          LIBSCCA_OPEN_READ,
	          &error );
#endif

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_file_close(
	          file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libscca_file_open_wide(
	          file,
	          source,
	          LIBSCCA_OPEN_READ,
	          &error );
#else
	result = libscca_file_open(
	          file,
	          source,
	          LIBSCCA_OPEN_READ,
	          &error );
#endif

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_file_close(
	          file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libscca_file_free(
	          &file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libscca_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_signal_abort(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_signal_abort(
	          file,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_signal_abort(
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_format_version function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_format_version(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t format_version  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_format_version(
	          file,
	          &format_version,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_format_version(
	          NULL,
	          &format_version,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_format_version(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf8_executable_filename_size function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf8_executable_filename_size(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf8_executable_filename_size(
	          file,
	          &utf8_string_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf8_executable_filename_size(
	          NULL,
	          &utf8_string_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_executable_filename_size(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf8_executable_filename function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf8_executable_filename(
     libscca_file_t *file )
{
	uint8_t utf8_string[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf8_executable_filename(
	          file,
	          utf8_string,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf8_executable_filename(
	          NULL,
	          utf8_string,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_executable_filename(
	          file,
	          NULL,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_executable_filename(
	          file,
	          utf8_string,
	          0,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_executable_filename(
	          file,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf16_executable_filename_size function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf16_executable_filename_size(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf16_executable_filename_size(
	          file,
	          &utf16_string_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf16_executable_filename_size(
	          NULL,
	          &utf16_string_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_executable_filename_size(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf16_executable_filename function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf16_executable_filename(
     libscca_file_t *file )
{
	uint16_t utf16_string[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf16_executable_filename(
	          file,
	          utf16_string,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf16_executable_filename(
	          NULL,
	          utf16_string,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_executable_filename(
	          file,
	          NULL,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_executable_filename(
	          file,
	          utf16_string,
	          0,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_executable_filename(
	          file,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_prefetch_hash function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_prefetch_hash(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t prefetch_hash   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_prefetch_hash(
	          file,
	          &prefetch_hash,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_prefetch_hash(
	          NULL,
	          &prefetch_hash,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_prefetch_hash(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_last_run_time function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_last_run_time(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint64_t filetime        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_last_run_time(
	          file,
	          0,
	          &filetime,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_last_run_time(
	          NULL,
	          0,
	          &filetime,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_last_run_time(
	          file,
	          -1,
	          &filetime,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_last_run_time(
	          file,
	          0,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_run_count function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_run_count(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t run_count       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_run_count(
	          file,
	          &run_count,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_run_count(
	          NULL,
	          &run_count,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_run_count(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_number_of_file_metrics_entries function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_number_of_file_metrics_entries(
     libscca_file_t *file )
{
	libcerror_error_t *error           = NULL;
	int number_of_file_metrics_entries = 0;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_number_of_file_metrics_entries(
	          file,
	          &number_of_file_metrics_entries,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_number_of_file_metrics_entries(
	          NULL,
	          &number_of_file_metrics_entries,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_number_of_file_metrics_entries(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_file_metrics_entry function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_file_metrics_entry(
     libscca_file_t *file )
{
	libcerror_error_t *error             = NULL;
	libscca_file_metrics_t *file_metrics = NULL;
	int result                           = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_file_metrics_entry(
	          file,
	          0,
	          &file_metrics,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file_metrics",
	 file_metrics );

	result = libscca_file_metrics_free(
	          &file_metrics,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_file_metrics_entry(
	          NULL,
	          0,
	          &file_metrics,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file_metrics",
	 file_metrics );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_file_metrics_entry(
	          file,
	          -1,
	          &file_metrics,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file_metrics",
	 file_metrics );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_file_metrics_entry(
	          file,
	          0,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file_metrics",
	 file_metrics );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_metrics != NULL )
	{
		libscca_file_metrics_free(
		 &file_metrics,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_file_get_number_of_filenames function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_number_of_filenames(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_filenames  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_number_of_filenames(
	          file,
	          &number_of_filenames,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_number_of_filenames(
	          NULL,
	          &number_of_filenames,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_number_of_filenames(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf8_filename_size function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf8_filename_size(
     libscca_file_t *file )
{
	libcerror_error_t *error  = NULL;
	size_t utf8_filename_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf8_filename_size(
	          file,
	          0,
	          &utf8_filename_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf8_filename_size(
	          NULL,
	          0,
	          &utf8_filename_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_filename_size(
	          file,
	          -1,
	          &utf8_filename_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_filename_size(
	          file,
	          0,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf8_filename function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf8_filename(
     libscca_file_t *file )
{
	uint8_t utf8_filename[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf8_filename(
	          file,
	          0,
	          utf8_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf8_filename(
	          NULL,
	          0,
	          utf8_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_filename(
	          file,
	          -1,
	          utf8_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_filename(
	          file,
	          0,
	          NULL,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_filename(
	          file,
	          0,
	          utf8_filename,
	          0,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf8_filename(
	          file,
	          0,
	          utf8_filename,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf16_filename_size function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf16_filename_size(
     libscca_file_t *file )
{
	libcerror_error_t *error   = NULL;
	size_t utf16_filename_size = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf16_filename_size(
	          file,
	          0,
	          &utf16_filename_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf16_filename_size(
	          NULL,
	          0,
	          &utf16_filename_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_filename_size(
	          file,
	          -1,
	          &utf16_filename_size,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_filename_size(
	          file,
	          0,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_utf16_filename function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_utf16_filename(
     libscca_file_t *file )
{
	uint16_t utf16_filename[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf16_filename(
	          file,
	          0,
	          utf16_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_utf16_filename(
	          NULL,
	          0,
	          utf16_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_filename(
	          file,
	          -1,
	          utf16_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_filename(
	          file,
	          0,
	          NULL,
	          512,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_filename(
	          file,
	          0,
	          utf16_filename,
	          0,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_utf16_filename(
	          file,
	          0,
	          utf16_filename,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_number_of_volumes function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_number_of_volumes(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_volumes    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_number_of_volumes(
	          file,
	          &number_of_volumes,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_number_of_volumes(
	          NULL,
	          &number_of_volumes,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_number_of_volumes(
	          file,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_volume_information function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_volume_information(
     libscca_file_t *file )
{
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	int result                                       = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_volume_information(
	          file,
	          0,
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "volume_information",
	 volume_information );

	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_get_volume_information(
	          NULL,
	          0,
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_volume_information(
	          file,
	          -1,
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libscca_file_get_volume_information(
	          file,
	          0,
	          NULL,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libscca_file_t *file             = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = scca_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( SCCA_TEST_FILE_VERBOSE )
	libscca_notify_set_verbose(
	 1 );
	libscca_notify_set_stream(
	 stderr,
	 NULL );
#endif

	SCCA_TEST_RUN(
	 "libscca_file_initialize",
	 scca_test_file_initialize );

	SCCA_TEST_RUN(
	 "libscca_file_free",
	 scca_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		SCCA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        SCCA_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        SCCA_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		SCCA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        SCCA_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libscca_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		SCCA_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		SCCA_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_open",
		 scca_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_open_wide",
		 scca_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_open_file_io_handle",
		 scca_test_file_open_file_io_handle,
		 source );

		SCCA_TEST_RUN(
		 "libscca_file_close",
		 scca_test_file_close );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_open_close",
		 scca_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = scca_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		SCCA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		SCCA_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		SCCA_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_signal_abort",
		 scca_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT )

		/* TODO: add tests for libscca_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT ) */

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_format_version",
		 scca_test_file_get_format_version,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf8_executable_filename_size",
		 scca_test_file_get_utf8_executable_filename_size,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf8_executable_filename",
		 scca_test_file_get_utf8_executable_filename,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf16_executable_filename_size",
		 scca_test_file_get_utf16_executable_filename_size,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf16_executable_filename",
		 scca_test_file_get_utf16_executable_filename,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_prefetch_hash",
		 scca_test_file_get_prefetch_hash,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_last_run_time",
		 scca_test_file_get_last_run_time,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_run_count",
		 scca_test_file_get_run_count,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_number_of_file_metrics_entries",
		 scca_test_file_get_number_of_file_metrics_entries,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_file_metrics_entry",
		 scca_test_file_get_file_metrics_entry,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_number_of_filenames",
		 scca_test_file_get_number_of_filenames,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf8_filename_size",
		 scca_test_file_get_utf8_filename_size,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf8_filename",
		 scca_test_file_get_utf8_filename,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf16_filename_size",
		 scca_test_file_get_utf16_filename_size,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_utf16_filename",
		 scca_test_file_get_utf16_filename,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_number_of_volumes",
		 scca_test_file_get_number_of_volumes,
		 file );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_volume_information",
		 scca_test_file_get_volume_information,
		 file );

		/* Clean up
		 */
		result = scca_test_file_close_source(
		          &file,
		          &error );

		SCCA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		SCCA_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		SCCA_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		SCCA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		SCCA_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        SCCA_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libscca_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

