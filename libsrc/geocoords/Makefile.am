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
include $(top_srcdir)/subpackage.am

SUBDIRS = data

subpkginclude_HEADERS = \
	Converter.hh \
	CoordSys.hh \
	CoordSys.icc \
	CSCart.hh \
	CSCart.icc \
	CSGeo.hh \
	CSGeo.icc \
	CSGeoLocalCart.hh \
	CSGeoLocalCart.icc \
	CSGeoProj.hh \
	CSGeoProj.icc \
	CSPicklerAscii.hh \
	Geoid.hh \
	Geoid.icc \
	Projector.hh \
	Projector.icc \
	proj4fwd.h

noinst_HEADERS =

# export
clean-local: clean-subpkgincludeHEADERS
BUILT_SOURCES = export-subpkgincludeHEADERS
CLEANFILES = export-subpkgincludeHEADERS

# End of file 
