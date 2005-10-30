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

subpackage = geocoords
include $(top_srcdir)/pkgs/subpackage.am

SUBDIRS = data

lib_LTLIBRARIES = libspatialdatageocoords.la

libspatialdatageocoords_la_SOURCES = \
	Converter.cc \
	CoordSys.cc \
	CSCart.cc \
	CSGeo.cc \
	CSGeoLocalCart.cc \
	CSGeoProj.cc \
	Geoid.cc \
	Projector.cc

libspatialdatageocoords_la_LDFLAGS =

INCLUDES +=

CPPFLAGS += -DDATADIR="$(subpkgdatadir)"

libspatialdatageocoords_la_LIBADD = \
	-lproj

subpkginclude_HEADERS = \
	Converter.h \
	CoordSys.h \
	CoordSys.icc \
	CSCart.h \
	CSCart.icc \
	CSGeo.h \
	CSGeo.icc \
	CSGeoLocalCart.h \
	CSGeoLocalCart.icc \
	CSGeoProj.h \
	Geoid.h \
	Projector.h \
	Projector.icc \
	proj4fwd.h

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# version
# $Id$

# End of file 
