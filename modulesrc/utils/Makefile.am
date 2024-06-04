# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

subpackage = utils
include $(top_srcdir)/subpackage.am
include $(top_srcdir)/modulesrc/module.am

subpkgpython_LTLIBRARIES = _utils.la
subpkgpython_PYTHON = utils.py

swig_sources = \
	utils.i \
	SpatialdataVersion.i

swig_generated = \
	utils_wrap.cxx \
	utils.py

_utils_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__utils_la_SOURCES = $(swig_sources) $(swig_generated)

_utils_la_LIBADD = \
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
