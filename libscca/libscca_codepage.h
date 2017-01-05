/*
 * Codepage functions
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

#if !defined( _LIBSCCA_INTERNAL_CODEPAGE_H )
#define _LIBSCCA_INTERNAL_CODEPAGE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBSCCA )

#include <libscca/codepage.h>

/* Define HAVE_LOCAL_LIBSCCA for local use of libscca
 * The definitions in <libscca/codepage.h> are copied here
 * for local use of libscca
 */
#else

/* The codepage definitions
 */
enum LIBSCCA_CODEPAGES
{
	LIBSCCA_CODEPAGE_ASCII		= 20127,

	LIBSCCA_CODEPAGE_ISO_8859_1	= 28591,
	LIBSCCA_CODEPAGE_ISO_8859_2	= 28592,
	LIBSCCA_CODEPAGE_ISO_8859_3	= 28593,
	LIBSCCA_CODEPAGE_ISO_8859_4	= 28594,
	LIBSCCA_CODEPAGE_ISO_8859_5	= 28595,
	LIBSCCA_CODEPAGE_ISO_8859_6	= 28596,
	LIBSCCA_CODEPAGE_ISO_8859_7	= 28597,
	LIBSCCA_CODEPAGE_ISO_8859_8	= 28598,
	LIBSCCA_CODEPAGE_ISO_8859_9	= 28599,
	LIBSCCA_CODEPAGE_ISO_8859_10	= 28600,
	LIBSCCA_CODEPAGE_ISO_8859_11	= 28601,
	LIBSCCA_CODEPAGE_ISO_8859_13	= 28603,
	LIBSCCA_CODEPAGE_ISO_8859_14	= 28604,
	LIBSCCA_CODEPAGE_ISO_8859_15	= 28605,
	LIBSCCA_CODEPAGE_ISO_8859_16	= 28606,

	LIBSCCA_CODEPAGE_KOI8_R		= 20866,
	LIBSCCA_CODEPAGE_KOI8_U		= 21866,

	LIBSCCA_CODEPAGE_WINDOWS_874	= 874,
	LIBSCCA_CODEPAGE_WINDOWS_932	= 932,
	LIBSCCA_CODEPAGE_WINDOWS_936	= 936,
	LIBSCCA_CODEPAGE_WINDOWS_949	= 949,
	LIBSCCA_CODEPAGE_WINDOWS_950	= 950,
	LIBSCCA_CODEPAGE_WINDOWS_1250	= 1250,
	LIBSCCA_CODEPAGE_WINDOWS_1251	= 1251,
	LIBSCCA_CODEPAGE_WINDOWS_1252	= 1252,
	LIBSCCA_CODEPAGE_WINDOWS_1253	= 1253,
	LIBSCCA_CODEPAGE_WINDOWS_1254	= 1254,
	LIBSCCA_CODEPAGE_WINDOWS_1255	= 1255,
	LIBSCCA_CODEPAGE_WINDOWS_1256	= 1256,
	LIBSCCA_CODEPAGE_WINDOWS_1257	= 1257,
	LIBSCCA_CODEPAGE_WINDOWS_1258	= 1258
};

#endif /* !defined( HAVE_LOCAL_LIBSCCA ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_INTERNAL_CODEPAGE_H ) */

