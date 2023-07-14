/*
 * String functions
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

#if !defined( _PYSCCA_STRING_H )
#define _PYSCCA_STRING_H

#include <common.h>
#include <types.h>

#include "pyscca_libcerror.h"
#include "pyscca_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3

PyObject *pyscca_string_new_from_utf8_rfc2279(
           const uint8_t *utf8_string,
           size_t utf8_string_size );

int pyscca_string_copy_to_utf8_rfc2279(
     PyObject *string_object,
     uint8_t **utf8_string,
     size_t *utf8_string_size,
     libcerror_error_t **error );

#endif /* PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3 */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYSCCA_STRING_H ) */

