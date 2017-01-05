/*
 * Library volume_information type test program
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

#include "../libscca/libscca_volume_information.h"

#if defined( __GNUC__ )

/* Tests the libscca_volume_information_initialize function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_initialize(
     void )
{
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	int result                                       = 0;

#if defined( HAVE_SCCA_TEST_MEMORY )
	int number_of_malloc_fail_tests                  = 1;
	int number_of_memset_fail_tests                  = 1;
	int test_number                                  = 0;
#endif

	/* Test regular cases
	 */
	result = libscca_volume_information_initialize(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SCCA_TEST_ASSERT_IS_NOT_NULL(
         "volume_information",
         volume_information );

        SCCA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SCCA_TEST_ASSERT_IS_NULL(
         "volume_information",
         volume_information );

        SCCA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libscca_volume_information_initialize(
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

	volume_information = (libscca_volume_information_t *) 0x12345678UL;

	result = libscca_volume_information_initialize(
	          &volume_information,
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

	volume_information = NULL;

#if defined( HAVE_SCCA_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libscca_volume_information_initialize with malloc failing
		 */
		scca_test_malloc_attempts_before_fail = test_number;

		result = libscca_volume_information_initialize(
		          &volume_information,
		          &error );

		if( scca_test_malloc_attempts_before_fail != -1 )
		{
			scca_test_malloc_attempts_before_fail = -1;

			if( volume_information != NULL )
			{
				libscca_volume_information_free(
				 &volume_information,
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
			 "volume_information",
			 volume_information );

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
		/* Test libscca_volume_information_initialize with memset failing
		 */
		scca_test_memset_attempts_before_fail = test_number;

		result = libscca_volume_information_initialize(
		          &volume_information,
		          &error );

		if( scca_test_memset_attempts_before_fail != -1 )
		{
			scca_test_memset_attempts_before_fail = -1;

			if( volume_information != NULL )
			{
				libscca_volume_information_free(
				 &volume_information,
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
			 "volume_information",
			 volume_information );

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
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

/* Tests the libscca_volume_information_free function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libscca_volume_information_free(
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

#if defined( __GNUC__ )

/* Tests the libscca_volume_information_get_creation_time function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_get_creation_time(
     void )
{
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	uint64_t creation_time                           = 0;
	int creation_time_is_set                         = 0;
	int result                                       = 0;

	/* Initialize test
	 */
	result = libscca_volume_information_initialize(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libscca_volume_information_get_creation_time(
	          volume_information,
	          &creation_time,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	creation_time_is_set = result;

	/* Test error cases
	 */
	result = libscca_volume_information_get_creation_time(
	          NULL,
	          &creation_time,
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

	if( creation_time_is_set != 0 )
	{
		result = libscca_volume_information_get_creation_time(
		          volume_information,
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
	}
	/* Clean up
	 */
	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

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
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_volume_information_get_serial_number function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_get_serial_number(
     void )
{
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	uint32_t serial_number                           = 0;
	int result                                       = 0;
	int serial_number_is_set                         = 0;

	/* Initialize test
	 */
	result = libscca_volume_information_initialize(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libscca_volume_information_get_serial_number(
	          volume_information,
	          &serial_number,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	serial_number_is_set = result;

	/* Test error cases
	 */
	result = libscca_volume_information_get_serial_number(
	          NULL,
	          &serial_number,
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

	if( serial_number_is_set != 0 )
	{
		result = libscca_volume_information_get_serial_number(
		          volume_information,
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
	}
	/* Clean up
	 */
	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

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
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_volume_information_get_utf8_device_path_size function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_get_utf8_device_path_size(
     void )
{
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	size_t utf8_device_path_size                     = 0;
	int result                                       = 0;
	int utf8_device_path_size_is_set                 = 0;

	/* Initialize test
	 */
	result = libscca_volume_information_initialize(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libscca_volume_information_get_utf8_device_path_size(
	          volume_information,
	          &utf8_device_path_size,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_device_path_size_is_set = result;

	/* Test error cases
	 */
	result = libscca_volume_information_get_utf8_device_path_size(
	          NULL,
	          &utf8_device_path_size,
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

	if( utf8_device_path_size_is_set != 0 )
	{
		result = libscca_volume_information_get_utf8_device_path_size(
		          volume_information,
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
	}
	/* Clean up
	 */
	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

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
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_volume_information_get_utf8_device_path function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_get_utf8_device_path(
     void )
{
	uint8_t utf8_device_path[ 512 ];

	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	int result                                       = 0;
	int utf8_device_path_is_set                      = 0;

	/* Initialize test
	 */
	result = libscca_volume_information_initialize(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libscca_volume_information_get_utf8_device_path(
	          volume_information,
	          utf8_device_path,
	          512,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_device_path_is_set = result;

	/* Test error cases
	 */
	result = libscca_volume_information_get_utf8_device_path(
	          NULL,
	          utf8_device_path,
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

	if( utf8_device_path_is_set != 0 )
	{
		result = libscca_volume_information_get_utf8_device_path(
		          volume_information,
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

		result = libscca_volume_information_get_utf8_device_path(
		          volume_information,
		          utf8_device_path,
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

		result = libscca_volume_information_get_utf8_device_path(
		          volume_information,
		          utf8_device_path,
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
	}
	/* Clean up
	 */
	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

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
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_volume_information_get_utf16_device_path_size function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_get_utf16_device_path_size(
     void )
{
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	size_t utf16_device_path_size                    = 0;
	int result                                       = 0;
	int utf16_device_path_size_is_set                = 0;

	/* Initialize test
	 */
	result = libscca_volume_information_initialize(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libscca_volume_information_get_utf16_device_path_size(
	          volume_information,
	          &utf16_device_path_size,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_device_path_size_is_set = result;

	/* Test error cases
	 */
	result = libscca_volume_information_get_utf16_device_path_size(
	          NULL,
	          &utf16_device_path_size,
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

	if( utf16_device_path_size_is_set != 0 )
	{
		result = libscca_volume_information_get_utf16_device_path_size(
		          volume_information,
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
	}
	/* Clean up
	 */
	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

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
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libscca_volume_information_get_utf16_device_path function
 * Returns 1 if successful or 0 if not
 */
int scca_test_volume_information_get_utf16_device_path(
     void )
{
	uint16_t utf16_device_path[ 512 ];

	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	int result                                       = 0;
	int utf16_device_path_is_set                     = 0;

	/* Initialize test
	 */
	result = libscca_volume_information_initialize(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NOT_NULL(
	 "volume_information",
	 volume_information );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libscca_volume_information_get_utf16_device_path(
	          volume_information,
	          utf16_device_path,
	          512,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_device_path_is_set = result;

	/* Test error cases
	 */
	result = libscca_volume_information_get_utf16_device_path(
	          NULL,
	          utf16_device_path,
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

	if( utf16_device_path_is_set != 0 )
	{
		result = libscca_volume_information_get_utf16_device_path(
		          volume_information,
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

		result = libscca_volume_information_get_utf16_device_path(
		          volume_information,
		          utf16_device_path,
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

		result = libscca_volume_information_get_utf16_device_path(
		          volume_information,
		          utf16_device_path,
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
	}
	/* Clean up
	 */
	result = libscca_volume_information_free(
	          &volume_information,
	          &error );

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "volume_information",
	 volume_information );

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
	if( volume_information != NULL )
	{
		libscca_volume_information_free(
		 &volume_information,
		 NULL );
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
	 "libscca_volume_information_initialize",
	 scca_test_volume_information_initialize );

#endif /* defined( __GNUC__ ) */

	SCCA_TEST_RUN(
	 "libscca_volume_information_free",
	 scca_test_volume_information_free );

#if defined( __GNUC__ ) && defined( TODO )

	SCCA_TEST_RUN(
	 "libscca_volume_information_get_creation_time",
	 scca_test_volume_information_get_creation_time );

	SCCA_TEST_RUN(
	 "libscca_volume_information_get_serial_number",
	 scca_test_volume_information_get_serial_number );

	SCCA_TEST_RUN(
	 "libscca_volume_information_get_utf8_device_path_size",
	 scca_test_volume_information_get_utf8_device_path_size );

	SCCA_TEST_RUN(
	 "libscca_volume_information_get_utf8_device_path",
	 scca_test_volume_information_get_utf8_device_path );

	SCCA_TEST_RUN(
	 "libscca_volume_information_get_utf16_device_path_size",
	 scca_test_volume_information_get_utf16_device_path_size );

	SCCA_TEST_RUN(
	 "libscca_volume_information_get_utf16_device_path",
	 scca_test_volume_information_get_utf16_device_path );

#endif /* defined( __GNUC__ ) && defined( TODO ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

