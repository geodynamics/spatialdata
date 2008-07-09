# -*- autoconf -*-
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# <LicenseText>
#
# ----------------------------------------------------------------------
#

AC_PREREQ(2.59)
AC_INIT([yourname], [0.0.1], [youremail@here])
AC_CONFIG_HEADER([portinfo])
AC_CONFIG_AUX_DIR([./aux-config])
AM_INIT_AUTOMAKE([foreign])

# ----------------------------------------------------------------------
# TESTING w/cppunit
AC_ARG_ENABLE([testing],
	[  --enable-testing        Enable unit testing with cppunit (requires cppunit) [[default=no]]],
	[enable_testing=yes],
	[enable_testing=no])

# ----------------------------------------------------------------------
# C/C++/libtool/install
AC_PROG_CXX
AC_PROG_CC
AC_DISABLE_STATIC

AC_PROG_LIBTOOL
if test "$allow_undefined_flag" = unsupported; then
    # See issue119.
    AM_LDFLAGS="-no-undefined $AM_LDFLAGS"
fi
AM_CONDITIONAL([NO_UNDEFINED], [test "$allow_undefined_flag" = unsupported])
AC_SUBST(AM_LDFLAGS)

AC_PROG_INSTALL

# PYTHON
AM_PATH_PYTHON([2.3])
CIT_PYTHON_SYSCONFIG

# Check for Python modules and packages.
#CIT_PYTHON_EGG_SETUP

# PYREX/PYREXEMBED
AC_CHECK_PROG([have_pyrex],
  [pyrexc],
  [yes],
  [no])
if test "$have_pyrex" = "no"; then
  AC_MSG_ERROR([Pyrex not found in current path.])
fi
AC_CHECK_PROG([have_pyrexembed],
  [pyrexembed],
  [yes],
  [no])
if test "$have_pyrexembed" = "no"; then
  AC_MSG_ERROR([Pyrexembed not found in current path.])
fi
AC_ARG_VAR(PYXFLAGS, [Pyrex flags])

# CPPUNIT
if test "$enable_testing" = "yes" ; then
  AC_LANG(C++)
  AC_CHECK_HEADER([cppunit/TestRunner.h], [], [
    AC_MSG_ERROR([CppUnit header not found; try CPPFLAGS="-I<CppUnit include dir>"])
  ])
  AC_MSG_CHECKING([for CppUnit::TestRunner in -lcppunit])
  AC_REQUIRE_CPP
  AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([[#include <cppunit/TestRunner.h>]],
	             [[CppUnit::TestRunner runner;]])],
    [AC_MSG_RESULT(yes)],
    [AC_MSG_RESULT(no)
     AC_MSG_ERROR([CppUnit library not found; try LDFLAGS="-L<CppUnit lib dir>"])
  ])
fi

# SPATIALDATA
AC_LANG(C++)
AC_CHECK_HEADER([spatialdata/spatialdb/SpatialDB.hh], [], [
  AC_MSG_ERROR([SpatialDB header not found; try CPPFLAGS="-I<Spatialdata include dir>"])
])
AC_MSG_CHECKING([for spatialdb::SimpleDB in -lspatialdata])
AC_REQUIRE_CPP
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([[#include <spatialdata/spatialdb/SpatialDB.hh>]
                    [#include <spatialdata/spatialdb/SimpleDB.hh>]],
                   [[spatialdata::spatialdb::SimpleDB db;]])],
  [AC_MSG_RESULT(yes)],
  [AC_MSG_RESULT(no)
   AC_MSG_ERROR([Spatialdata library not found; try LDFLAGS="-L<Spatialdata lib dir>"])
])

# ENDIANNESS
AC_C_BIGENDIAN

# ----------------------------------------------------------------------
AC_CONFIG_FILES([Makefile])

AC_OUTPUT


# End of file
