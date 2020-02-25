# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

SUBDIRS = \
	geocoords \
	spatialdb \
	units \
	utils \
	testing

lib_LTLIBRARIES = libspatialdata.la

libspatialdata_la_SOURCES = \
	geocoords/Converter.cc \
	geocoords/CoordSys.cc \
	geocoords/CSCart.cc \
	geocoords/CSGeo.cc \
	geocoords/CSPicklerAscii.cc \
	spatialdb/CompositeDB.cc \
	spatialdb/GocadVoxet.cc \
	spatialdb/GravityField.cc \
	spatialdb/SCECCVMH.cc \
	spatialdb/SimpleGridDB.cc \
	spatialdb/SimpleDB.cc \
	spatialdb/SpatialDB.cc \
	spatialdb/SimpleDBData.cc \
	spatialdb/SimpleDBQuery.cc \
	spatialdb/SimpleIO.cc \
	spatialdb/SimpleIOAscii.cc \
	spatialdb/SimpleGridAscii.cc \
	spatialdb/TimeHistory.cc \
	spatialdb/TimeHistoryIO.cc \
	spatialdb/UniformDB.cc \
	spatialdb/UserFunctionDB.cc \
	spatialdb/cspatialdb.cc	\
	units/Nondimensional.cc \
	units/Parser.cc \
	utils/LineParser.cc \
	utils/PointsStream.cc \
	utils/SpatialdataVersion.cc

libspatialdata_la_LDFLAGS = $(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)
libspatialdata_la_LIBADD = \
	-lproj \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)

AM_CPPFLAGS = -I$(top_srcdir)/libsrc
AM_CPPFLAGS += -DDATADIR=$(pkgdatadir)/geocoords $(PYTHON_EGG_CPPFLAGS) -I$(PYTHON_INCDIR)


if ENABLE_TESTING
libspatialdata_la_SOURCES += \
	testing/TestDriver.cc

libspatialdata_la_LIBADD += -lcppunit
endif


# End of file
