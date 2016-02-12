m4_define([loftili_MAJOR_VERSION], [1])
m4_define([loftili_MINOR_VERSION], [1])
m4_define([loftili_REVISION], [2])
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
Loftili is an application platform built to provide cloud-based control
to home audio systems. This application is the core library designed to run
on lightweight systems and consume information from the API.
Licensed under the MIT license. 
Copyright Danny Hadley 2014
])

AC_PROG_CC(gcc)
AC_PROG_CXX(g++)
AC_PROG_LIBTOOL
AC_LANG([C++])

AC_ARG_WITH(logfile,
  [  --with-logfile      Specify the log file path to use],
  AC_DEFINE_UNQUOTED([LOFTILI_LOG_PATH], ["$withval"], [the log path used during runtime]),
  AC_DEFINE([LOFTILI_LOG_PATH], ["loftili.log"], [the log path used during runtime])
  )

AC_ARG_WITH(logid,
  [  --with-logid      Specify the spdlog id to use],
  AC_DEFINE_UNQUOTED([LOFTILI_SPDLOG_ID], ["$withval"], [the id used during runtime]),
  AC_DEFINE([LOFTILI_SPDLOG_ID], ["loftili"], [the id used during runtime])
  )

AC_MSG_CHECKING([if able to compile lambda expressions with c++ 11])
CPPFLAGS="$CPPFLAGS -std=c++11"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
  auto a = [] () { };
]])], [AC_MSG_RESULT([yes])], [AC_MSG_ERROR([could not use c++ 11])])

CURRENT_DIR=$(pwd)
AC_CHECK_FILE([$CURRENT_DIR/vendor/rapidjson/include/rapidjson/rapidjson.h], [], [
  AC_MSG_ERROR([make sure you have rapidjson downloaded])])

AC_CHECK_FILE([$CURRENT_DIR/vendor/spdlog/include/spdlog/spdlog.h], [], [
  AC_MSG_ERROR([make sure you have spdlog downloaded])])

AC_CHECK_LIB([ssl], [SSL_library_init], [
  HAVE_SSL=1
  LIBS="-lssl $LIBS"
  AC_DEFINE([HAVE_SSL], [1], [ssl comment])], [
  AC_DEFINE([HAVE_SSL], [0], [ssl comment])])

AC_CHECK_LIB([ao], [ao_initialize], [
  HAVE_LIBAO=1
  LIBS="-lao $LIBS"
  AC_DEFINE([HAVE_LIBAO], [1], [libao is used for audio playback])], [
  AC_DEFINE([HAVE_LIBAO], [0], [libao is used for audio playback])])

AC_CHECK_LIB([mpg123], [mpg123_init], [
  HAVE_MPG123=1
  LIBS="-lmpg123 $LIBS"
  AC_DEFINE([HAVE_MPG123], [1], [mpg123])], [
  HAVE_MPG123=0
  AC_DEFINE([HAVE_MPG123], [0], [mpg123])])

AC_CHECK_HEADER([openssl/rand.h], [AC_MSG_RESULT([found])], [
CPPFLAGS="$CPPFLAGS -I/usr/local/opt/openssl/include"
])

AC_MSG_CHECKING([checking full audio capability])
AC_TRY_RUN([
#include <ao/ao.h>
#include <iostream>
int main() {
  ao_initialize();
  int driver_id = ao_default_driver_id();
  ao_shutdown();
  return driver_id >= 0 && HAVE_MPG123 ? 0 : 1;
}], [
  HAVE_AUDIO=1
  AC_DEFINE([HAVE_AUDIO], [1], [support for audio on this defice])
  AC_MSG_RESULT([ok])], [
  HAVE_AUDIO=0
  AC_DEFINE([HAVE_AUDIO], [0], [support for audio on this defice])
  AC_MSG_RESULT([not found.])])

if test "x$HAVE_AUDIO" == "x1"
then
  audio_str="yes"
else
  audio_str="no"
fi

AC_MSG_RESULT([
xxx   xxx   xxx
xxx   xxx   xxx
      xxx      
xxx   xxx   xxx
xxx   xxx   xxx
xxx   xxxxxxxxx
xxx   xxxxxxxxx

- system check result:
audio support ... : $audio_str
video support ... : no
])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
