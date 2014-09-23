m4_define([loftili_MAJOR_VERSION], [0])
m4_define([loftili_MINOR_VERSION], [1])
m4_define([loftili_REVISION], [1])
m4_define([loftili_PKG_VERSION], [loftili_MAJOR_VERSION.loftili_MINOR_VERSION.loftili_REVISION])

AC_INIT(
[loftili], 
[loftili_PKG_VERSION], 
[bugs@loftili.com], 
[], 
[http://loftili.com])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_COPYRIGHT([
Loftili is an open source audio player built for the raspberry pi. 
Licensed under the MIT license. 
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

AC_CHECK_LIB([microhttpd], [MHD_start_daemon], [], [AC_MSG_ERROR([
libmicrohttpd not installed
source: http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/libmicrohttpd-0.9.37.tar.gz
])])
AC_CHECK_HEADERS([ao/ao.h],[],[AC_MSG_ERROR([Missing a required header, please install libao])])
AC_CHECK_LIB([ao], [ao_initialize], [], [AC_MSG_ERROR([
libao is not installed
source: 
])])
AC_CHECK_LIB([mpg123], [mpg123_init], [], [AC_MSG_ERROR([
libmpg123 is not installed
source: http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/mpg123-1.20.1.tar.bz2
])])
AC_CHECK_LIB([curl], [curl_global_init], [], [AC_MSG_ERROR([
libcurl is not installed
source: http://curl.askapache.com/download/curl-7.37.1.tar.gz
])])


AC_MSG_CHECKING([for an available audio device through libao])
AC_TRY_RUN([
#include <ao/ao.h>
#include <iostream>
int main() {
  ao_initialize();
  int driver_id = ao_default_driver_id();
  ao_shutdown();
  return driver_id >= 0 ? 0 : 1;
}], [AC_MSG_RESULT([ok])], [AC_MSG_ERROR([
Libao was not able to find a default audio driver. Please read the
documentation for libao online at http://www.xiph.org/ao/. A copy
of the library can be downloaded from our ftp server.
source: http://ftp.sizethreestudios.com/artifacts/loftili/libs/libao-1.2.0.tar.gz
])])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
