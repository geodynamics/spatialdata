# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

subpackage = geocoords
include $(top_srcdir)/subpackage.am
include $(top_srcdir)/modulesrc/module.am

subpkgpython_LTLIBRARIES = _geocoords.la
subpkgpython_PYTHON = geocoords.py

swig_sources = \
	geocoords.i \
	CoordSys.i \
	CSCart.i \
	CSGeo.i \
	CSGeoLocal.i \
	Converter.i

swig_generated = \
	geocoords_wrap.cxx \
	geocoords.py

_geocoords_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__geocoords_la_SOURCES = $(swig_sources) $(swig_generated)

_geocoords_la_LIBADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)

if ENABLE_SWIG
$(srcdir)/geocoords_wrap.cxx $(srcdir)/geocoords.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $<
else
$(srcdir)/geocoords_wrap.cxx $(srcdir)/geocoords.py:
	$(error Missing SWIG generated files. Make sure SWIG is installed and reconfigure with --enable-swig)
endif


MAINTAINERCLEANFILES = \
	$(srcdir)/geocoords_wrap.cxx \
	$(srcdir)/geocoords.py


# End of file
