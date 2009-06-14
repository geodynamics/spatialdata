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

ACLOCAL_AMFLAGS = -I ./m4


# LIBRARY --------------------------------------------------------------
lib_LTLIBRARIES = libspatialdatacontrib.la

libspatialdatacontrib_la_SOURCES = \
	UniformVelModel.cc

libspatialdatacontrib_la_LDFLAGS = $(AM_LDFLAGS)

libspatialdatacontrib_la_LIBADD = \
	-lspatialdata \
	-lproj
if NO_UNDEFINED
libspatialdatacontrib_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

AM_CPPFLAGS = $(PYTHON_EGG_CPPFLAGS) -I$(PYTHON_INCDIR) 

INCLUDES = 

# MODULE ---------------------------------------------------------------

pkgpyexec_LTLIBRARIES = _spatialdatacontribmodule.la

pkgpyexec_PYTHON = spatialdatacontrib.py

swig_sources = \
	spatialdatacontrib.i \
	UniformVelModel.i

swig_generated = \
	spatialdatacontrib_wrap.cxx \
	spatialdatacontrib.py

_spatialdatacontribmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__spatialdatacontribmodule_la_SOURCES = $(swig_sources) $(swig_generated)

_spatialdatacontribmodule_la_LIBADD = libspatialdatacontrib.la
if NO_UNDEFINED
_spatialdatacontribmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(NUMPY_INCDIR) -I$(PYTHON_INCDIR)

$(srcdir)/spatialdatacontrib_wrap.cxx $(srcdir)/spatialdatacontrib.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $(CPPFLAGS) $<


MAINTAINERCLEANFILES = $(swig_generated)



# PYTHON ---------------------------------------------------------------

nobase_pkgpyexec_PYTHON = \
	__init__.py \
	UniformVelModel.py


# End of file 
