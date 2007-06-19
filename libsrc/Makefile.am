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

SUBDIRS = \
	geocoords \
	spatialdb \
	utils

lib_LTLIBRARIES = libspatialdata.la

libspatialdata_la_SOURCES = \
	utils/PointsStream.cc \
	geocoords/Converter.cc \
	geocoords/CoordSys.cc \
	geocoords/CSCart.cc \
	geocoords/CSGeo.cc \
	geocoords/CSGeoLocalCart.cc \
	geocoords/CSGeoProj.cc \
	geocoords/CSPicklerAscii.cc \
	geocoords/Geoid.cc \
	geocoords/Projector.cc \
	spatialdb/SimpleDB.cc \
	spatialdb/SpatialDB.cc \
	spatialdb/SimpleDBQuery.cc \
	spatialdb/SimpleIO.cc \
	spatialdb/SimpleIOAscii.cc \
	spatialdb/cspatialdb.cc	

libspatialdata_la_LDFLAGS = -no-undefined

CPPFLAGS += -DDATADIR="$(pkgdatadir)/geocoords"

INCLUDES = -I$(top_builddir)/include

libspatialdata_la_LIBADD = \
	-lproj \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)


# End of file 
