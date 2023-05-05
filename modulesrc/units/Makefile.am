# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
#
# ----------------------------------------------------------------------
#

subpackage = units
include $(top_srcdir)/subpackage.am
include $(top_srcdir)/modulesrc/module.am

subpkgpython_LTLIBRARIES = _units.la
subpkgpython_PYTHON = units.py

swig_sources = \
	units.i \
	Nondimensional.i

swig_generated = \
	units_wrap.cxx \
	units.py

_units_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__units_la_SOURCES = $(swig_sources) $(swig_generated)

_units_la_LIBADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)

if ENABLE_SWIG
$(srcdir)/units_wrap.cxx $(srcdir)/units.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $<
else
$(srcdir)/units_wrap.cxx $(srcdir)/units.py:
	$(error Missing SWIG generated files. Make sure SWIG is installed and reconfigure with --enable-swig)
endif


MAINTAINERCLEANFILES = \
	$(srcdir)/units_wrap.cxx \
	$(srcdir)/units.py


# End of file
