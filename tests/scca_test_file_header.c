/*
 * Library file_header type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "scca_test_libcerror.h"
#include "scca_test_libscca.h"
#include "scca_test_macros.h"
#include "scca_test_memory.h"
#include "scca_test_unused.h"

#include "../libscca/libscca_file_header.h"

uint8_t scca_test_file_header_data1[ 84 ] = {
	0x1e, 0x00, 0x00, 0x00, 0x53, 0x43, 0x43, 0x41, 0x11, 0x00, 0x00, 0x00, 0xd8, 0x73, 0x03, 0x00,
	0x44, 0x00, 0x4f, 0x00, 0x57, 0x00, 0x4e, 0x00, 0x4c, 0x00, 0x4f, 0x00, 0x41, 0x00, 0x44, 0x00,
	0x45, 0x00, 0x52, 0x00, 0x2e, 0x00, 0x45, 0x00, 0x58, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xba, 0x91, 0xe9, 0xca,
	0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT )

/* Tests the libscca_file_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_header_initialize(
     void )
{
	libcerror_error_t *error           = NULL;
	libscca_file_header_t *file_header = NULL;
	int result                         = 0;

#if defined( HAVE_SCCA_TEST_MEMORY )
	int number_of_malloc_fail_tests    = 1;
	int number_of_memset_fail_tests    = 1;
	int test_number                    = 0;
#endif

	/* Test regular cases
	 */
	result = libscca_file_header_initialize(
	          &file_header,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_file_header_free(
	          &file_header,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_file_header_initialize(
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

	file_header = (libscca_file_header_t *) 0x12345678UL;

	result = libscca_file_header_initialize(
	          &file_header,
	          &error );

	file_header = NULL;

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
		/* Test libscca_file_header_initialize with malloc failing
		 */
		scca_test_malloc_attempts_before_fail = test_number;

		result = libscca_file_header_initialize(
		          &file_header,
		          &error );

		if( scca_test_malloc_attempts_before_fail != -1 )
		{
			scca_test_malloc_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libscca_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
		/* Test libscca_file_header_initialize with memset failing
		 */
		scca_test_memset_attempts_before_fail = test_number;

		result = libscca_file_header_initialize(
		          &file_header,
		          &error );

		if( scca_test_memset_attempts_before_fail != -1 )
		{
			scca_test_memset_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libscca_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
	if( file_header != NULL )
	{
		libscca_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_file_header_free function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libscca_file_header_free(
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

/* Tests the libscca_file_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_header_read_data(
     void )
{
	libcerror_error_t *error           = NULL;
	libscca_file_header_t *file_header = NULL;
	int result                         = 0;

	/* Initialize test
	 */
	result = libscca_file_header_initialize(
	          &file_header,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libscca_file_header_read_data(
	          file_header,
	          scca_test_file_header_data1,
	          84,
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
	result = libscca_file_header_read_data(
	          NULL,
	          scca_test_file_header_data1,
	          84,
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

	result = libscca_file_header_read_data(
	          file_header,
	          NULL,
	          84,
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

	result = libscca_file_header_read_data(
	          file_header,
	          scca_test_file_header_data1,
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

	/* Clean up
	 */
	result = libscca_file_header_free(
	          &file_header,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

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
	if( file_header != NULL )
	{
		libscca_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc SCCA_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] SCCA_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc SCCA_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] SCCA_TEST_ATTRIBUTE_UNUSED )
#endif
{
	SCCA_TEST_UNREFERENCED_PARAMETER( argc )
	SCCA_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT )

	SCCA_TEST_RUN(
	 "libscca_file_header_initialize",
	 scca_test_file_header_initialize );

	SCCA_TEST_RUN(
	 "libscca_file_header_free",
	 scca_test_file_header_free );

	SCCA_TEST_RUN(
	 "libscca_file_header_read_data",
	 scca_test_file_header_read_data );

	/* TODO add tests for libscca_file_header_read_data_stream */

#endif /* defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

