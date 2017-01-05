/*
 * The internal type definitions
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

#if !defined( _LIBSCCA_INTERNAL_TYPES_H )
#define _LIBSCCA_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBSCCA for local use of libscca
 * The definitions in <libscca/types.h> are copied here
 * for local use of libscca
 */
#if defined( HAVE_LOCAL_LIBSCCA )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libscca_file {}			libscca_file_t;
typedef struct libscca_file_metrics {}		libscca_file_metrics_t;
typedef struct libscca_volume_information {}	libscca_volume_information_t;

#else
typedef intptr_t libscca_file_t;
typedef intptr_t libscca_file_metrics_t;
typedef intptr_t libscca_volume_information_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBSCCA ) */

#endif /* !defined( _LIBSCCA_INTERNAL_TYPES_H ) */

