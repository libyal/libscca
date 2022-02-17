/*
 * Common input functions for the sccatools
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "sccainput.h"
#include "sccatools_libcerror.h"
#include "sccatools_libscca.h"

/* Determines the codepage from a string
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int sccainput_determine_ascii_codepage(
     const system_character_t *string,
     int *ascii_codepage,
     libcerror_error_t **error )
{
	static char *function = "sccainput_determine_ascii_codepage";
	size_t string_length  = 0;
	int result            = 0;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( ascii_codepage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( string_length == 5 )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "ascii" ),
		     5 ) == 0 )
		{
			*ascii_codepage = LIBSCCA_CODEPAGE_ASCII;
			result          = 1;
		}
	}
#if defined( HAVE_ISO_CODEPAGES )
	if( ( string_length == 10 )
	 || ( string_length == 11 ) )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "iso" ),
		     3 ) == 0 )
		{
			if( ( string[ 3 ] != '-' )
			 && ( string[ 3 ] != '_' ) )
			{
			}
			else if( system_string_compare(
				  &( string[ 4 ] ),
				  _SYSTEM_STRING( "8859" ),
				  4 ) == 0 )
			{
				if( ( string[ 8 ] != '-' )
				 && ( string[ 8 ] != '_' ) )
				{
				}
				else if( string_length == 10 )
				{
					if( system_string_compare(
					     &( string[ 9 ] ),
					     _SYSTEM_STRING( "1" ),
					     1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_1;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "2" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_2;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "3" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_3;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "4" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_4;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "5" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_5;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "6" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_6;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "7" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_7;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "8" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_8;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "9" ),
						  1 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_9;
						result          = 1;
					}
				}
				else if( string_length == 11 )
				{
					if( system_string_compare(
					     &( string[ 9 ] ),
					     _SYSTEM_STRING( "10" ),
					     2 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_10;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "11" ),
						  2 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_11;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "13" ),
						  2 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_13;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "14" ),
						  2 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_14;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "15" ),
						  2 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_15;
						result          = 1;
					}
					else if( system_string_compare(
						  &( string[ 9 ] ),
						  _SYSTEM_STRING( "16" ),
						  2 ) == 0 )
					{
						*ascii_codepage = LIBSCCA_CODEPAGE_ISO_8859_16;
						result          = 1;
					}
				}
			}
		}
	}
#endif
	if( ( string_length == 11 )
	 || ( string_length == 12 ) )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "windows" ),
		     7 ) == 0 )
		{
			if( ( string[ 7 ] != '-' )
			 && ( string[ 7 ] != '_' ) )
			{
			}
			else if( string_length == 11 )
			{
				if( system_string_compare(
				     &( string[ 8 ] ),
				     _SYSTEM_STRING( "874" ),
				     3 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_874;
					result          = 1;
				}
				else if( system_string_compare(
				          &( string[ 8 ] ),
				          _SYSTEM_STRING( "932" ),
				          3 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_932;
					result          = 1;
				}
				else if( system_string_compare(
				          &( string[ 8 ] ),
				          _SYSTEM_STRING( "936" ),
				          3 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_936;
					result          = 1;
				}
			}
			else if( string_length == 12 )
			{
				if( system_string_compare(
				     &( string[ 8 ] ),
				     _SYSTEM_STRING( "1250" ),
				     4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1250;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1251" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1251;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1252" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1252;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1253" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1253;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1253" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1253;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1254" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1254;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1255" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1255;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1256" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1256;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1257" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1257;
					result          = 1;
				}
				else if( system_string_compare(
					  &( string[ 8 ] ),
					  _SYSTEM_STRING( "1258" ),
					  4 ) == 0 )
				{
					*ascii_codepage = LIBSCCA_CODEPAGE_WINDOWS_1258;
					result          = 1;
				}
			}
		}
	}
	return( result );
}

