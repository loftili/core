AC_INIT([loftili], [1.0.0])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_COPYRIGHT([
Loftili is an open source audio player built for the raspberry pi. 
Licensed under the GNU GPL v3.0 license. 
Copyright Danny Hadley 2014
])

AC_PROG_CXX
AC_PROG_LIBTOOL
AC_LANG([C++])

AC_MSG_CHECKING([if able to compile lambda expressions with c++ 11])
CPPFLAGS="$CPPFLAGS -std=c++0x"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
  auto a = [] () { };
]])], [AC_MSG_RESULT([yes])], [AC_MSG_ERROR([could not use c++ 11])])

AC_CHECK_LIB([microhttpd], [MHD_start_daemon], [], [AC_MSG_ERROR([libmicrohttpd not installed])])
AC_CHECK_LIB([ao], [ao_initialize], [], [AC_MSG_ERROR([libao not installed])])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
