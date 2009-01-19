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

subpackage = geocoords
include $(top_srcdir)/subpackage.am

subpkgpyexec_LTLIBRARIES = _geocoordsmodule.la
subpkgpyexec_PYTHON = geocoords.py

swig_sources = \
	geocoords.i \
	CoordSys.i \
	CSCart.i \
	CSGeo.i \
	CSGeoProj.i \
	CSGeoLocalCart.i \
	Projector.i \
	Converter.i

swig_generated = \
	geocoords_wrap.cxx \
	geocoords.py

_geocoordsmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__geocoordsmodule_la_SOURCES = $(swig_sources) $(swig_generated)

_geocoordsmodule_la_LIBADD = \
	$(top_builddir)/libsrc/libspatialdata.la
if NO_UNDEFINED
_geocoordsmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(NUMPY_INCDIR) -I$(PYTHON_INCDIR)

$(srcdir)/geocoords_wrap.cxx $(srcdir)/geocoords.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $<


MAINTAINERCLEANFILES = \
	$(srcdir)/geocoords_wrap.cxx \
	$(srcdir)/geocoords.py


# End of file 
