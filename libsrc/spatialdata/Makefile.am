# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

SUBDIRS = \
	geocoords \
	spatialdb \
	units \
	utils \
	muparser

lib_LTLIBRARIES = libspatialdata.la

libspatialdata_la_SOURCES = \
	geocoords/Converter.cc \
	geocoords/CoordSys.cc \
	geocoords/CSCart.cc \
	geocoords/CSGeo.cc \
	geocoords/CSGeoLocal.cc \
	geocoords/CSPicklerAscii.cc \
	spatialdb/AnalyticDB.cc \
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
	utils/SpatialdataVersion.cc \
	muparser/muParser.cpp \
	muparser/muParserBase.cpp \
	muparser/muParserBytecode.cpp \
	muparser/muParserCallback.cpp \
	muparser/muParserError.cpp \
	muparser/muParserInt.cpp \
	muparser/muParserTokenReader.cpp


libspatialdata_la_LDFLAGS = $(AM_LDFLAGS) $(PYTHON_LDFLAGS) $(PYTHON_LA_LDFLAGS)
libspatialdata_la_LIBADD = \
	-lproj \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)

AM_CPPFLAGS = -I$(top_srcdir)/libsrc
AM_CPPFLAGS += -DDATADIR=$(pkgdatadir)/geocoords -I$(PYTHON_INCDIR)


dist_noinstall = \
	README.rst \
	LICENSE

# End of file
