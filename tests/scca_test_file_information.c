/*
 * Library file_information type testing program
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

#include "../libscca/libscca_file_information.h"

#if defined( __GNUC__ )

/* Tests the libscca_file_information_initialize function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_information_initialize(
     void )
{
	libcerror_error_t *error                     = NULL;
	libscca_file_information_t *file_information = NULL;
	int result                                   = 0;

	/* Test file_information initialization
	 */
	result = libscca_file_information_initialize(
	          &file_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SCCA_TEST_ASSERT_IS_NOT_NULL(
         "file_information",
         file_information );

        SCCA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libscca_file_information_free(
	          &file_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SCCA_TEST_ASSERT_IS_NULL(
         "file_information",
         file_information );

        SCCA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libscca_file_information_initialize(
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

	file_information = (libscca_file_information_t *) 0x12345678UL;

	result = libscca_file_information_initialize(
	          &file_information,
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

	file_information = NULL;

#if defined( HAVE_SCCA_TEST_MEMORY )

	/* Test libscca_file_information_initialize with malloc failing
	 */
	scca_test_malloc_attempts_before_fail = 0;

	result = libscca_file_information_initialize(
	          &file_information,
	          &error );

	if( scca_test_malloc_attempts_before_fail != -1 )
	{
		scca_test_malloc_attempts_before_fail = -1;

		if( file_information != NULL )
		{
			libscca_file_information_free(
			 &file_information,
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
		 "file_information",
		 file_information );

		SCCA_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libscca_file_information_initialize with memset failing
	 */
	scca_test_memset_attempts_before_fail = 0;

	result = libscca_file_information_initialize(
	          &file_information,
	          &error );

	if( scca_test_memset_attempts_before_fail != -1 )
	{
		scca_test_memset_attempts_before_fail = -1;

		if( file_information != NULL )
		{
			libscca_file_information_free(
			 &file_information,
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
		 "file_information",
		 file_information );

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
	if( file_information != NULL )
	{
		libscca_file_information_free(
		 &file_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_file_information_free function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_information_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libscca_file_information_free(
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

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ )

	SCCA_TEST_RUN(
	 "libscca_file_information_initialize",
	 scca_test_file_information_initialize );

	SCCA_TEST_RUN(
	 "libscca_file_information_free",
	 scca_test_file_information_free );

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

