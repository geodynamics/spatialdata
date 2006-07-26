# -*- Makefile -*-
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

subpackage = utils
include $(top_srcdir)/subpackage.am

lib_LTLIBRARIES = libspatialdatautils.la

libspatialdatautils_la_SOURCES = \
	PointsStream.cc

libspatialdatautils_la_LDFLAGS =

subpkginclude_HEADERS = \
	PointsStream.hh \
	PointsStream.icc

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# version
# $Id$

# End of file 
