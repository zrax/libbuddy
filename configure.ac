dnl vim: set sw=4 sts=4 ts=4 noet ft=config foldmethod=marker foldmarker={{{,}}} :
dnl {{{ Basic setup
AC_PREREQ(2.59)
AC_INIT([src/buddy.h])
AC_CONFIG_AUX_DIR(config)

VERSION_MAJOR=0
VERSION_MINOR=1
VERSION_MICRO=0
VERSION_FULL="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_MICRO"
VERSION="$VERSION_FULL"
VERSION_LIB_CURRENT=`expr 100 '*' $VERSION_MAJOR + $VERSION_MINOR`
VERSION_LIB_REVISION="$VERSION_MICRO"

AC_SUBST([VERSION_MAJOR])
AC_SUBST([VERSION_MINOR])
AC_SUBST([VERSION_MICRO])
AC_SUBST([VERSION_FULL])
AC_SUBST([VERSION_LIB_CURRENT])
AC_SUBST([VERSION_LIB_REVISION])

AM_INIT_AUTOMAKE(libbuddy, [$VERSION_FULL])
AC_LANG([C])
dnl }}}

dnl {{{ Basic toolchain stuff
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_PROG_RANLIB
AC_STDC_HEADERS
AC_PROG_MAKE_SET
dnl }}}

dnl {{{ CFLAGS
AC_DEFUN([CHECK_CFLAG], [
                  save_CFLAGS=$CFLAGS
                  CFLAGS="$CFLAGS $LSYS_CFLAGS $1 -Werror"
                  AC_COMPILE_IFELSE([
#include <stdio.h>
int main(int argc, char **argv)
{
        char *s = "test";
        printf("%s.\n", s);
        return 0;
}
                  ],
                  [cflag_success=yes],
                  [cflag_success=no])
                  CFLAGS="$save_CFLAGS"
                  if test "x$cflag_success" = "xyes" ; then
                          LSYS_CFLAGS="$LSYS_CFLAGS $1"
                          cflags_message="${cflags_message} $1"
                  fi
                  ])
AC_MSG_CHECKING([for appropiate compiler flags])
CHECK_CFLAG([-Wall])
CHECK_CFLAG([-Wextra])
CHECK_CFLAG([-Winit-self])
CHECK_CFLAG([-Wredundant-decls])
CHECK_CFLAG([-Winline])
CHECK_CFLAG([-Wunused-function])
# CHECK_CFLAG([-Wunreachable-code])
CHECK_CFLAG([-Wshadow])
AC_MSG_RESULT([${cflags_message}])
AC_SUBST([LSYS_CFLAGS])
PKG_CHECK_MODULES(libusb, [libusb >= 0.1])
dnl }}}

dnl {{{ pkg-config
dnl PKG_PROG_PKG_CONFIG([0.9.0])
LIBBUDDY_PC_CFLAGS=
LIBBUDDY_PC_LIBS="-lusb -lbuddy"
LIBBUDDY_PC_VERSION="${VERSION_FULL}"
LIBBUDDY_PC_SLOT="${VERSION_MAJOR}.${VERSION_MINOR}"
AC_SUBST([LIBBUDDY_PC_CFLAGS])
AC_SUBST([LIBBUDDY_PC_LIBS])
AC_SUBST([LIBBUDDY_PC_VERSION])
AC_SUBST([LIBBUDDY_PC_SLOT])
dnl }}}

dnl {{{ doxygen
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN([$PACKAGE_NAME],[doxygen.cfg],[doc])
dnl }}}

dnl {{{ output
AC_CONFIG_HEADER(config.h)
AC_OUTPUT(
		  Makefile
		  src/Makefile
		  pkg-config/Makefile
		  )
dnl }}}
