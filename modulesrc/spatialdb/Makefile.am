# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

subpackage = spatialdb
include $(top_srcdir)/subpackage.am
include $(top_srcdir)/modulesrc/module.am

subpkgpython_LTLIBRARIES = _spatialdb.la

subpkgpython_PYTHON = spatialdb.py

swig_sources = \
	spatialdb.i \
	SpatialDBObj.i \
	SimpleDB.i \
	SimpleDBData.i \
	SimpleIO.i \
	SimpleIOAscii.i \
	UniformDB.i \
	AnalyticDB.i \
	SimpleGridDB.i \
	CompositeDB.i \
	SCECCVMH.i \
	GravityField.i \
	TimeHistory.i \
	TimeHistoryIO.i

swigincludedir = $(pkgdatadir)/swig/$(subpackage)
swiginclude_HEADERS = \
	SpatialDBObj.i

swig_generated = \
	spatialdb_wrap.cxx \
	spatialdb.py

_spatialdb_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__spatialdb_la_SOURCES = $(swig_sources) $(swig_generated)

_spatialdb_la_LIBADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)

if ENABLE_SWIG
$(srcdir)/spatialdb_wrap.cxx $(srcdir)/spatialdb.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $<
else
$(srcdir)/spatialdb_wrap.cxx $(srcdir)/spatialdb.py:
	$(error Missing SWIG generated files. Make sure SWIG is installed and reconfigure with --enable-swig)
endif


MAINTAINERCLEANFILES = $(swig_generated)


# End of file
