dnl Function to detect if libscca dependencies are available
AC_DEFUN([AX_LIBSCCA_CHECK_LOCAL],
 [dnl Check for internationalization functions in libscca/libscca_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

