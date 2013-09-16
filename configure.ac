# -*- autoconf -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

AC_PREREQ(2.59)
AC_INIT([spatialdata], [1.9.2], [baagaard@usgs.gov])
AC_CONFIG_HEADER([portinfo])
AC_CONFIG_AUX_DIR([./aux-config])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign])

# ----------------------------------------------------------------------
# SWIG
AC_ARG_ENABLE([swig],
    [AC_HELP_STRING([--enable-swig],
        [enable generating modules with SWIG) @<:@default=no@:>@])],
	[if test "$enableval" = yes ; then enable_swig=yes; else enable_swig=no; fi],
	[enable_swig=no])
AM_CONDITIONAL([ENABLE_SWIG], [test "$enable_swig" = yes])

# TESTING w/cppunit
AC_ARG_ENABLE([testing],
	[  --enable-testing        Enable unit testing with cppunit (requires cppunit) [[default=no]]],
	[if test "$enableval" = yes ; then enable_testing=yes; else enable_testing=no; fi],
	[enable_testing=no])

# PYTHIA w/pythia
enable_pythia=yes
AC_ARG_ENABLE([pythia],
	[  --enable-pythia        Enable use of Pythia (requires pythia) [[default=yes]]],
	[if test "$enableval" = yes ; then enable_pythia=yes; else enable_pythia=no; fi],
	[enable_pythia=no])

# DOCUMENTATION w/doxygen
AC_ARG_ENABLE([documentation],
	[  --enable-documentation  Enable building html documentation (requires doxygen) [[default=no]]],
	[if test "$enableval" = yes ; then enable_documentation=yes; else enable_documentation=no; fi],
	[enable_documentation=no])

# TESTING w/SCEC CVM-H
AC_ARG_ENABLE([scec-cvm-h],
	[  --enable-scec-cvm-h=DIR    Enable unit testing with SCEC CVM-H (requires cppunit and SCEC CVM-H data files) [[default=no]]],
	[],
	[enable_scec_cvm_h=no])

# ----------------------------------------------------------------------
AC_PROG_CXX
AC_PROG_CC

AC_PROG_LIBTOOL
if test "$allow_undefined_flag" = unsupported; then
    # See issue119.
    AM_LDFLAGS="-no-undefined $AM_LDFLAGS"
fi
AM_CONDITIONAL([NO_UNDEFINED], [test "$allow_undefined_flag" = unsupported])
AC_SUBST(AM_LDFLAGS)

# ----------------------------------------------------------------------
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
  CIT_CPPUNIT_HEADER
  CIT_CPPUNIT_LIB
  if test "$enable_scec_cvm_h" != "no" ; then
    AC_SUBST([SCECCVMH_DATADIR], ["$enable_scec_cvm_h"])
    AC_CHECK_FILE([$enable_scec_cvm_h/topo.vo], [], [
      AC_MSG_ERROR([SCEC CVM-H data file topo.vo not found])])
    AC_CHECK_FILE([$enable_scec_cvm_h/moho.vo], [], [
      AC_MSG_ERROR([SCEC CVM-H data file moho.vo not found])])
    AC_CHECK_FILE([$enable_scec_cvm_h/base.vo], [], [
      AC_MSG_ERROR([SCEC CVM-H data file base.vo not found])])
    AC_CHECK_FILE([$enable_scec_cvm_h/LA_HR.vo], [], [
      AC_MSG_ERROR([SCEC CVM-H data file LA_HR.vo not found])])
    AC_CHECK_FILE([$enable_scec_cvm_h/LA_LR.vo], [], [
      AC_MSG_ERROR([SCEC CVM-H data file LA_LR.vo not found])])
    AC_CHECK_FILE([$enable_scec_cvm_h/CM.vo], [], [
      AC_MSG_ERROR([SCEC CVM-H data file CM.vo not found])])
    AC_DEFINE_UNQUOTED([SCECCVMH_DATADIR], ["$enable_scec_cvm_h"],
               [Define to test SCEC CVM-H.])
  fi
fi
AM_CONDITIONAL([ENABLE_SCEC_CVM_H], [test "$enable_scec_cvm_h" != no])

# PYTHIA
AM_CONDITIONAL([ENABLE_PYTHIA], [test "$enable_pythia" = yes])
if test "$enable_pythia" = "yes" ; then
  AC_LANG(C++)

  # Check for Python modules and packages.
  AM_PATH_PYTHON([2.3])
  AC_ARG_VAR(PYTHON, [Python interpreter])
  AC_ARG_VAR(PYTHONPATH, [Python module search path])
  CIT_PYTHON_SYSCONFIG
  CIT_CHECK_PYTHON_HEADER
  CIT_CHECK_PYTHON_SHARED

  # PYTHIA/PYRE
  CIT_PYTHON_MODULE([pyre],[0.8.1])
  CIT_PYTHON_MODULE([journal],[0.8.1])

  # NUMPY
  CIT_NUMPY_PYTHON_MODULE
  CIT_NUMPY_INCDIR

  # SWIG
  if test "$enable_swig" = "yes" ; then
    AC_PROG_SWIG(1.3.33)
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
	libsrc/units/Makefile
	libsrc/utils/Makefile
	modulesrc/Makefile
	modulesrc/include/Makefile
	modulesrc/geocoords/Makefile
	modulesrc/spatialdb/Makefile
	modulesrc/units/Makefile
	spatialdata/Makefile
	tests/Makefile
	tests/libtests/Makefile
	tests/libtests/geocoords/Makefile
	tests/libtests/geocoords/data/Makefile
	tests/libtests/spatialdb/Makefile
	tests/libtests/spatialdb/data/Makefile
	tests/libtests/units/Makefile
	tests/libtests/utils/Makefile
	tests/libtests/utils/data/Makefile
	tests/pytests/Makefile
	tests/pytests/geocoords/Makefile
	tests/pytests/spatialdb/Makefile
	tests/pytests/spatialdb/data/Makefile
	tests/pytests/units/Makefile
	tests/pytests/utils/Makefile
	applications/Makefile
	templates/Makefile
	doc/Makefile])

AC_OUTPUT


# End of file 
