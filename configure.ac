m4_define([loftili_MAJOR_VERSION], [0])
m4_define([loftili_MINOR_VERSION], [0])
m4_define([loftili_REVISION], [1])
m4_define([loftili_PKG_VERSION], [loftili_MAJOR_VERSION.loftili_MINOR_VERSION.loftili_REVISION])

AC_INIT([loftili], [loftili_PKG_VERSION], [danny@lofti.li])
AC_DEFINE([LOFTILI_PKG_VERSION], ["loftili_PKG_VERSION"])
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

AC_CHECK_LIB([microhttpd], [MHD_start_daemon], [], [AC_MSG_ERROR([
libmicrohttpd not installed
source: http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/libmicrohttpd-0.9.37.tar.gz
])])
AC_CHECK_HEADERS([portaudio.h],[],[AC_MSG_ERROR([Missing a required header, please install portaudio])])
AC_CHECK_LIB([portaudio], [Pa_GetVersionText], [], [AC_MSG_ERROR([
portaudio is not installed
source: http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/pa_stable_v19_20140130.tgz
])])
AC_CHECK_LIB([mpg123], [mpg123_init], [], [AC_MSG_ERROR([
libmpg123 is not installed
source: http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/mpg123-1.20.1.tar.bz2
])])

AC_MSG_CHECKING([for an available audio device through portaudio])
AC_TRY_RUN([
#include <portaudio.h>
#include <iostream>
int main() {
  int success = Pa_Initialize();
  int device_count =  Pa_GetDeviceCount();
  return device_count > 0 ? 0 : 1;
}], [AC_MSG_RESULT([ok])], [AC_MSG_ERROR([
Unable to find an audio device to use with portaudio...
Try installing libasound2 or alsa lib.
Alsa - http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/alsa-lib-1.0.27.2.tar.bz2
You will need to re-compile and install port audio.
])])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
