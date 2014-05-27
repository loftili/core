AC_INIT([rasbeat], [1.0.0])
AM_INIT_AUTOMAKE([foreign])

AC_COPYRIGHT([
Rasbeat is an open source audio player built for the raspberry pi. 
Licensed under the GNU GPL v3.0 license. 
Copyright Danny Hadley 2014
])

AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_LANG([C++])

AC_CHECK_LIB([microhttpd], [MHD_start_daemon], [], [AC_MSG_ERROR([libmicrohttpd not installed])])
LDFLAGS="$LIBMICROHTTPD_LIBS $LD_FLAGS"

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
