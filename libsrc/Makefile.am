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
	utils/LineParser.cc \
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
	spatialdb/GocadVoxet.cc \
	spatialdb/GravityField.cc \
	spatialdb/SCECCVMH.cc \
	spatialdb/SimpleDB.cc \
	spatialdb/SpatialDB.cc \
	spatialdb/SimpleDBQuery.cc \
	spatialdb/SimpleIO.cc \
	spatialdb/SimpleIOAscii.cc \
	spatialdb/UniformDB.cc \
	spatialdb/cspatialdb.cc	

libspatialdata_la_LDFLAGS = $(AM_LDFLAGS)

CPPFLAGS += -DDATADIR="$(pkgdatadir)/geocoords"

INCLUDES = -I$(top_builddir)/include

libspatialdata_la_LIBADD = \
	-lproj


# End of file 
