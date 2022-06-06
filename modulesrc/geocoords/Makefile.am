# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2022 University of California, Davis
#
# See LICENSE.md for license information.
#
# ----------------------------------------------------------------------
#

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
