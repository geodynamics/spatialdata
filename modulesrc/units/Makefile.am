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

subpackage = units
include $(top_srcdir)/subpackage.am

subpkgpyexec_LTLIBRARIES = _unitsmodule.la
subpkgpyexec_PYTHON = units.py

swig_sources = \
	units.i \
	Nondimensional.i

swig_generated = \
	units_wrap.cxx \
	units.py

_unitsmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__unitsmodule_la_SOURCES = $(swig_sources) $(swig_generated)

_unitsmodule_la_LIBADD = \
	$(top_builddir)/libsrc/libspatialdata.la
if NO_UNDEFINED
_unitsmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(PYTHON_INCDIR)

if ENABLE_SWIG
$(srcdir)/units_wrap.cxx $(srcdir)/units.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $<
endif


MAINTAINERCLEANFILES = \
	$(srcdir)/units_wrap.cxx \
	$(srcdir)/units.py


# End of file 
