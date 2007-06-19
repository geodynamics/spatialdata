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
	[  --enable-pythia        Enable use of Pythia (requires pythia) [[default=no]]],
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
AC_PROG_LIBTOOL
AM_PATH_PYTHON([2.3])

# ----------------------------------------------------------------------
# PYTHON
CIT_PYTHON_INCDIR

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

# PYTHIA
AM_CONDITIONAL([ENABLE_PYTHIA], [test "$enable_pythia" = yes])
if test "$enable_pythia" = "yes" ; then
  AC_LANG(C++)

  # Check for Python modules and packages.
  CIT_PYTHON_EGG_SETUP

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

# ENDIANNESS
AC_C_BIGENDIAN

# ----------------------------------------------------------------------
AC_CONFIG_FILES([Makefile
	libsrc/Makefile
	libsrc/geocoords/Makefile
	libsrc/geocoords/data/Makefile
	libsrc/spatialdb/Makefile
	libsrc/utils/Makefile
	modulesrc/Makefile
	modulesrc/geocoords/Makefile
	modulesrc/spatialdb/Makefile
	modulesrc/utils/Makefile
	spatialdata/Makefile
	tests/Makefile
	tests/libtests/Makefile
	tests/libtests/geocoords/Makefile
	tests/libtests/geocoords/data/Makefile
	tests/libtests/spatialdb/Makefile
	tests/libtests/spatialdb/data/Makefile
	tests/libtests/utils/Makefile
	tests/libtests/utils/data/Makefile
	tests/pytests/Makefile
	tests/pytests/geocoords/Makefile
	tests/pytests/spatialdb/Makefile
	tests/pytests/spatialdb/data/Makefile
	tests/pytests/utils/Makefile
	applications/Makefile
	doc/Makefile])

AC_OUTPUT


# End of file 
