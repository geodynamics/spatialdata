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

subpackage = utils
include $(top_srcdir)/subpackage.am
include $(top_srcdir)/modulesrc/module.am

subpkgpyexec_LTLIBRARIES = _utilsmodule.la
subpkgpyexec_PYTHON = utils.py

swig_sources = \
	utils.i \
	SpatialdataVersion.i

swig_generated = \
	utils_wrap.cxx \
	utils.py

_utilsmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__utilsmodule_la_SOURCES = $(swig_sources) $(swig_generated)

_utilsmodule_la_LIBADD = \
	$(top_builddir)/libsrc/spatialdata/libspatialdata.la \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)

if ENABLE_SWIG
$(srcdir)/utils_wrap.cxx $(srcdir)/utils.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $<
else
$(srcdir)/utils_wrap.cxx $(srcdir)/utils.py:
	$(error Missing SWIG generated files. Make sure SWIG is installed and reconfigure with --enable-swig)
endif


MAINTAINERCLEANFILES = \
	$(srcdir)/utils_wrap.cxx \
	$(srcdir)/utils.py


# End of file 
