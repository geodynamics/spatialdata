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
AC_INIT([spatialdata], [0.3.0], [baagaard@usgs.gov])
AC_CONFIG_HEADER([portinfo])
AC_CONFIG_AUX_DIR([./aux-config])
AM_INIT_AUTOMAKE([foreign])

# ----------------------------------------------------------------------
# PYTHON
AC_ARG_VAR(PYTHON, [Python interpreter])
AC_ARG_VAR(PYTHONPATH, [Python module search path])

# TESTING w/cppunit
AC_ARG_ENABLE([testing],
	[  --enable-testing        Enable unit testing with cppunit (requires cppunit) [[default=no]]],
	[enable_testing=yes],
	[enable_testing=no])

# PYTHIA w/pythia
AC_ARG_ENABLE([pythia],
	[  --enable-pythia        Enable use of pythia package (requires pythia) [[default=no]]],
	[enable_pythia=yes],
	[enable_pythia=no])

# DOCUMENTATION w/doxygen
AC_ARG_ENABLE([documentation],
	[  --enable-documentation  Enable buuilding html documentation (requires doxygen) [[default=no]]],
	[enable_documentation=yes],
	[enable_documentation=no])
# ----------------------------------------------------------------------

AC_PROG_CXX
AC_PROG_CC
AC_PROG_FC
AC_FC_WRAPPERS
AC_FC_LIBRARY_LDFLAGS
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AM_PATH_PYTHON([2.3])

# ----------------------------------------------------------------------
# PYTHON
AC_CACHE_CHECK([for $am_display_PYTHON include directory],
    [PYTHON_INCDIR],
    [PYTHON_INCDIR=`$PYTHON -c "from distutils import sysconfig; print sysconfig.get_python_inc()" 2>/dev/null ||
     echo "$PYTHON_PREFIX/include/python$PYTHON_VERSION"`])
AC_SUBST([PYTHON_INCDIR], [$PYTHON_INCDIR])

# PROJ4
AC_CHECK_LIB(proj, pj_init_plus, [
  AC_CHECK_HEADER([proj_api.h], [], [
    AC_MSG_ERROR([Proj4 header not found; try CPPFLAGS="-I<Proj4 include dir>"])
  ])
],[
  AC_MSG_ERROR([Proj4 library not found; try LDFLAGS="-L<Proj4 lib dir>"])
])

# CPPUNIT
AM_CONDITIONAL([ENABLE_TESTING], [test "$enable_testing" = yes])
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

# PYRE
AM_CONDITIONAL([ENABLE_PYTHIA], [test "$enable_pyre" = yes])
if test "$enable_pyre" = "yes" ; then
  AC_LANG(C++)

  # PYTHIA
  AC_CHECK_HEADER([journal/debug.h], [], [
    AC_MSG_ERROR([Journal header not found; try CPPFLAGS="-I<pythia include dir>"])
  ])
  AC_MSG_CHECKING([for journal::debug_t in -ljournal])
  AC_REQUIRE_CPP
  AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([[#include <journal/debug.h>]],
	             [[journal::debug_t d("debug");]])],
    [AC_MSG_RESULT(yes)
     export CPPFLAGS="-DHAVE_PYTHIA $CPPFLAGS"],
    [AC_MSG_RESULT(no)
     AC_MSG_ERROR([Pythia library not found; try LDFLAGS="-L<pythia lib dir>"])
  ])

  # PYTHIAUTIL
  AC_CHECK_HEADER([pythiautil/BindingsUtil.h], [], [
    AC_MSG_ERROR([BindingsUtil header not found; try CPPFLAGS="-I<pythiautil include dir>"])
  ])
  AC_MSG_CHECKING([for pythiautil::BindingsUtil::GetAttribute() -lpythiautil])
  AC_REQUIRE_CPP
  AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([[#include <pythiautil/BindingsUtil.h>]],
	             [[PyObject* pyObj;]],
	             [[pythiautil::BindingsUtil::GetAttribute(pyObj, "a", "b");]])],
    [AC_MSG_RESULT(yes)],
    [AC_MSG_RESULT(no)
     AC_MSG_ERROR([Pythiautil library not found; try LDFLAGS="-L<pythiautil lib dir>"])
  ])
fi

# DOXYGEN
AM_CONDITIONAL([ENABLE_DOCUMENTATION], [test "$enable_documentation" = yes])
if test "$enable_documentation" = "yes" ; then
  AC_CHECK_PROG([have_doxygen],
    [doxygen],
    [yes],
    [no])
  if test "$have_doxygen" = "no"; then
    AC_MSG_ERROR([Doxygen not found in current path.])
  fi
fi

# ----------------------------------------------------------------------
AC_CONFIG_FILES([Makefile
	pkgs/Makefile
	pkgs/pyre/Makefile
	pkgs/geocoords/Makefile
	pkgs/geocoords/lib/Makefile
	pkgs/geocoords/lib/data/Makefile
	pkgs/geocoords/module/Makefile
	pkgs/geocoords/pyre/Makefile
	pkgs/geocoords/tests/Makefile
	pkgs/geocoords/tests/libtests/Makefile
	pkgs/geocoords/tests/libtests/data/Makefile
	pkgs/geocoords/tests/pytests/Makefile
	pkgs/spatialdb/Makefile
	pkgs/spatialdb/lib/Makefile
	pkgs/spatialdb/liblang/Makefile
	pkgs/spatialdb/module/Makefile
	pkgs/spatialdb/pyre/Makefile
	pkgs/spatialdb/tests/Makefile
	pkgs/spatialdb/tests/libtests/Makefile
	pkgs/spatialdb/tests/libtests/data/Makefile
	pkgs/spatialdb/tests/langtests/Makefile
	pkgs/spatialdb/tests/langtests/data/Makefile
	pkgs/spatialdb/tests/pytests/Makefile
	pkgs/spatialdb/tests/pytests/data/Makefile
	doc/Makefile])

AC_OUTPUT


# version
# $Id$

# End of file 
