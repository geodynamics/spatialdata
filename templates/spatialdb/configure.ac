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
AC_INIT([spatialdbcontrib], [0.0.1], [cig-short@geodynamics.org])
AC_CONFIG_HEADER([portinfo])
AC_CONFIG_AUX_DIR([./aux-config])
#AC_CONFIG_MACRO_DIR([./m4])
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

# SWIG
CIT_NUMPY_PYTHON_MODULE
CIT_NUMPY_INCDIR
AC_PROG_SWIG(1.3.33)

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
if test "x$SPATIALDATA_SWIG_DIR" != "x" ; then
  AC_CHECK_FILE([$SPATIALDATA_SWIG_DIR/spatialdb/SpatialDBObj.i], [], [
    AC_MSG_ERROR([Spatialdata SpatialDBObj.i SWIG interface file not found])])
  AC_SUBST([SWIG_FLAGS], ["-I$SPATIALDATA_SWIG_DIR $SWIG_FLAGS"])
else
  AC_CHECK_FILE([spatialdata/SpatialDBObj.i], [], [
    AC_MSG_ERROR([Spatialdata SpatialDBObj.i SWIG interface file not found; Try setting SPATIALDATA_SWIG_DIR=<directory containing spatialdb/SpatialDBObj.i>])])
fi


# ENDIANNESS
AC_C_BIGENDIAN

# ----------------------------------------------------------------------
AC_CONFIG_FILES([Makefile
	         tests/Makefile])

AC_OUTPUT


# End of file
