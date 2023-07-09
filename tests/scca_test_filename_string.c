/*
 * Library filename_string type testing program
 *
 * Copyright (C) 2011-2023, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libscca/libscca_filename_string.h"

#if defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT )

/* Tests the libscca_filename_string_initialize function
 * Returns 1 if successful or 0 if not
 */
int scca_test_filename_string_initialize(
     void )
{
	libcerror_error_t *error                     = NULL;
	libscca_filename_string_t *filename_string = NULL;
	int result                                   = 0;

	/* Test filename_string initialization
	 */
	result = libscca_filename_string_initialize(
	          &filename_string,
	          0,
	          NULL,
	          0,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "filename_string",
	 filename_string );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libscca_filename_string_free(
	          &filename_string,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "filename_string",
	 filename_string );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libscca_filename_string_initialize(
	          NULL,
	          0,
	          NULL,
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

	filename_string = (libscca_filename_string_t *) 0x12345678UL;

	result = libscca_filename_string_initialize(
	          &filename_string,
	          0,
	          NULL,
	          0,
	          &error );

	filename_string = NULL;

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

	/* Test libscca_filename_string_initialize with malloc failing
	 */
	scca_test_malloc_attempts_before_fail = 0;

	result = libscca_filename_string_initialize(
	          &filename_string,
	          0,
	          NULL,
	          0,
	          &error );

	if( scca_test_malloc_attempts_before_fail != -1 )
	{
		scca_test_malloc_attempts_before_fail = -1;

		if( filename_string != NULL )
		{
			libscca_filename_string_free(
			 &filename_string,
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
		 "filename_string",
		 filename_string );

		SCCA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libscca_filename_string_initialize with memset failing
	 */
	scca_test_memset_attempts_before_fail = 0;

	result = libscca_filename_string_initialize(
	          &filename_string,
	          0,
	          NULL,
	          0,
	          &error );

	if( scca_test_memset_attempts_before_fail != -1 )
	{
		scca_test_memset_attempts_before_fail = -1;

		if( filename_string != NULL )
		{
			libscca_filename_string_free(
			 &filename_string,
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
		 "filename_string",
		 filename_string );

		SCCA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_SCCA_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( filename_string != NULL )
	{
		libscca_filename_string_free(
		 &filename_string,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_filename_string_free function
 * Returns 1 if successful or 0 if not
 */
int scca_test_filename_string_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libscca_filename_string_free(
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
	 "libscca_filename_string_initialize",
	 scca_test_filename_string_initialize );

	SCCA_TEST_RUN(
	 "libscca_filename_string_free",
	 scca_test_filename_string_free );

#endif /* defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBSCCA_DLL_IMPORT ) */
}

