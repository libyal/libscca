/*
 * Support functions
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

#if !defined( _LIBSCCA_SUPPORT_H )
#define _LIBSCCA_SUPPORT_H

#include <common.h>
#include <types.h>

#include "libscca_extern.h"
#include "libscca_libbfio.h"
#include "libscca_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBSCCA )

LIBSCCA_EXTERN \
const char *libscca_get_version(
             void );

LIBSCCA_EXTERN \
int libscca_get_access_flags_read(
     void );

LIBSCCA_EXTERN \
int libscca_get_codepage(
     int *codepage,
     libcerror_error_t **error );

LIBSCCA_EXTERN \
int libscca_set_codepage(
     int codepage,
     libcerror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBSCCA ) */

LIBSCCA_EXTERN \
int libscca_check_file_signature(
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBSCCA_EXTERN \
int libscca_check_file_signature_wide(
     const wchar_t *filename,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBSCCA_EXTERN \
int libscca_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBSCCA_SUPPORT_H ) */

