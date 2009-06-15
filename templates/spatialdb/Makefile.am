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

SUBDIRS = tests

subpkgpythondir = $(pythondir)/spatialdata/spatialdb/contrib
subpkgpyexecdir = $(pyexecdir)/spatialdata/spatialdb/contrib


# LIBRARY --------------------------------------------------------------
lib_LTLIBRARIES = libspatialdbcontrib.la

libspatialdbcontrib_la_SOURCES = \
	UniformVelModel.cc

noinst_HEADERS = \
	UniformVelModel.hh

libspatialdbcontrib_la_LDFLAGS = $(AM_LDFLAGS)

libspatialdbcontrib_la_LIBADD = \
	-lspatialdata \
	-lproj
if NO_UNDEFINED
libspatialdbcontrib_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

AM_CPPFLAGS = $(PYTHON_EGG_CPPFLAGS) -I$(PYTHON_INCDIR) 

INCLUDES = 

# MODULE ---------------------------------------------------------------

subpkgpyexec_LTLIBRARIES = _spatialdbcontribmodule.la

subpkgpyexec_PYTHON = \
	spatialdbcontrib.py \
	__init__.py

swig_sources = \
	spatialdbcontrib.i \
	UniformVelModel.i

swig_generated = \
	spatialdbcontrib_wrap.cxx \
	spatialdbcontrib.py

_spatialdbcontribmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__spatialdbcontribmodule_la_SOURCES = $(swig_sources) $(swig_generated)

_spatialdbcontribmodule_la_LIBADD = libspatialdbcontrib.la
if NO_UNDEFINED
_spatialdbcontribmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(NUMPY_INCDIR) -I$(PYTHON_INCDIR)

$(srcdir)/spatialdbcontrib_wrap.cxx $(srcdir)/spatialdbcontrib.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $(SWIG_FLAGS) $<


MAINTAINERCLEANFILES = $(swig_generated)



# PYTHON ---------------------------------------------------------------

nobase_subpkgpyexec_PYTHON = \
	__init__.py \
	UniformVelModel.py


# End of file 
