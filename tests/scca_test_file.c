/*
 * Library file type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "scca_test_getopt.h"
#include "scca_test_libcerror.h"
#include "scca_test_libclocale.h"
#include "scca_test_libscca.h"
#include "scca_test_libuna.h"
#include "scca_test_macros.h"
#include "scca_test_memory.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make scca_test_file generate verbose output
#define SCCA_TEST_FILE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int scca_test_file_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "scca_test_file_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int scca_test_file_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "scca_test_file_get_wide_source";
	size_t source_length    = 0;
	size_t wide_source_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int scca_test_file_open_source(
     libscca_file_t **file,
     const system_character_t *source,
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
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libscca_file_open_wide(
	          *file,
	          source,
	          LIBSCCA_OPEN_READ,
	          error );
#else
	result = libscca_file_open(
	          *file,
	          source,
	          LIBSCCA_OPEN_READ,
	          error );
#endif
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

	SCCA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SCCA_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	file = NULL;

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
	result = scca_test_file_get_narrow_source(
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
	result = scca_test_file_get_wide_source(
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
	libcerror_error_t *error  = NULL;
	uint32_t format_version   = 0;
	int format_version_is_set = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_format_version(
	          file,
	          &format_version,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	format_version_is_set = result;

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

	if( format_version_is_set != 0 )
	{
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
	}
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
	libcerror_error_t *error                 = NULL;
	size_t utf8_executable_filename_size     = 0;
	int result                               = 0;
	int utf8_executable_filename_size_is_set = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf8_executable_filename_size(
	          file,
	          &utf8_executable_filename_size,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_executable_filename_size_is_set = result;

	/* Test error cases
	 */
	result = libscca_file_get_utf8_executable_filename_size(
	          NULL,
	          &utf8_executable_filename_size,
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

	if( utf8_executable_filename_size_is_set != 0 )
	{
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
	}
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
	uint8_t utf8_executable_filename[ 512 ];

	libcerror_error_t *error            = NULL;
	int result                          = 0;
	int utf8_executable_filename_is_set = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf8_executable_filename(
	          file,
	          utf8_executable_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_executable_filename_is_set = result;

	/* Test error cases
	 */
	result = libscca_file_get_utf8_executable_filename(
	          NULL,
	          utf8_executable_filename,
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

	if( utf8_executable_filename_is_set != 0 )
	{
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
		          utf8_executable_filename,
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
		          utf8_executable_filename,
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
	libcerror_error_t *error                  = NULL;
	size_t utf16_executable_filename_size     = 0;
	int result                                = 0;
	int utf16_executable_filename_size_is_set = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf16_executable_filename_size(
	          file,
	          &utf16_executable_filename_size,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_executable_filename_size_is_set = result;

	/* Test error cases
	 */
	result = libscca_file_get_utf16_executable_filename_size(
	          NULL,
	          &utf16_executable_filename_size,
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

	if( utf16_executable_filename_size_is_set != 0 )
	{
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
	}
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
	uint16_t utf16_executable_filename[ 512 ];

	libcerror_error_t *error             = NULL;
	int result                           = 0;
	int utf16_executable_filename_is_set = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_utf16_executable_filename(
	          file,
	          utf16_executable_filename,
	          512,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_executable_filename_is_set = result;

	/* Test error cases
	 */
	result = libscca_file_get_utf16_executable_filename(
	          NULL,
	          utf16_executable_filename,
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

	if( utf16_executable_filename_is_set != 0 )
	{
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
		          utf16_executable_filename,
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
		          utf16_executable_filename,
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
	int prefetch_hash_is_set = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_prefetch_hash(
	          file,
	          &prefetch_hash,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	prefetch_hash_is_set = result;

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

	if( prefetch_hash_is_set != 0 )
	{
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_last_run_time functions
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_last_run_time(
     libscca_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint64_t last_run_time   = 0;
	int result               = 0;

	result = libscca_file_get_last_run_time(
	          file,
	          0,
	          &last_run_time,
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
	          &last_run_time,
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
	          &last_run_time,
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
	int run_count_is_set     = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_run_count(
	          file,
	          &run_count,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	run_count_is_set = result;

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

	if( run_count_is_set != 0 )
	{
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
	}
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
	libcerror_error_t *error                  = NULL;
	int number_of_file_metrics_entries        = 0;
	int number_of_file_metrics_entries_is_set = 0;
	int result                                = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_number_of_file_metrics_entries(
	          file,
	          &number_of_file_metrics_entries,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_file_metrics_entries_is_set = result;

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

	if( number_of_file_metrics_entries_is_set != 0 )
	{
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libscca_file_get_number_of_filenames function
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_number_of_filenames(
     libscca_file_t *file )
{
	libcerror_error_t *error       = NULL;
	int number_of_filenames        = 0;
	int number_of_filenames_is_set = 0;
	int result                     = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_number_of_filenames(
	          file,
	          &number_of_filenames,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_filenames_is_set = result;

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

	if( number_of_filenames_is_set != 0 )
	{
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
	}
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
	libcerror_error_t *error     = NULL;
	int number_of_volumes        = 0;
	int number_of_volumes_is_set = 0;
	int result                   = 0;

	/* Test regular cases
	 */
	result = libscca_file_get_number_of_volumes(
	          file,
	          &number_of_volumes,
	          &error );

	SCCA_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	SCCA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_volumes_is_set = result;

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

	if( number_of_volumes_is_set != 0 )
	{
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the scca_test_file_get_volume_information functions
 * Returns 1 if successful or 0 if not
 */
int scca_test_file_get_volume_information(
     libscca_file_t *file )
{
	libcerror_error_t *error                         = NULL;
	libscca_volume_information_t *volume_information = NULL;
	int number_of_volumes                            = 0;
	int result                                       = 0;

	/* Initialize test
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

	if( number_of_volumes == 0 )
	{
		return( 1 );
	}
	/* Test get volume information
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
	libcerror_error_t *error   = NULL;
	libscca_file_t *file       = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

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

#if defined( LIBSCCA_HAVE_BFIO )

		/* TODO add test for libscca_file_open_file_io_handle */

#endif /* defined( LIBSCCA_HAVE_BFIO ) */

		SCCA_TEST_RUN(
		 "libscca_file_close",
		 scca_test_file_close );

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_open_close",
		 scca_test_file_open_close,
		 source );

		/* Initialize test
		 */
		result = scca_test_file_open_source(
		          &file,
		          source,
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

#if defined( __GNUC__ )

		/* TODO: add tests for libscca_file_open_read */

#endif /* defined( __GNUC__ ) */

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

		/* TODO: add tests for libscca_file_get_file_metrics_entry */

		SCCA_TEST_RUN_WITH_ARGS(
		 "libscca_file_get_number_of_filenames",
		 scca_test_file_get_number_of_filenames,
		 file );

		/* TODO: add tests for libscca_file_get_utf8_filename_size */

		/* TODO: add tests for libscca_file_get_utf8_filename */

		/* TODO: add tests for libscca_file_get_utf16_filename_size */

		/* TODO: add tests for libscca_file_get_utf16_filename */

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
		scca_test_file_close_source(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

