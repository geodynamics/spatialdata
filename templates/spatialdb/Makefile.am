# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

# This files uses autoconf patterns in variables names so that the GNU
# build system can automatically construct the dependencies and build
# the library using the appropriate flags.

# m4 macros for GNU build system
ACLOCAL_AMFLAGS = -I ./m4

SUBDIRS = tests

# Define path where python and module will be installed
subpkgpythondir = $(pythondir)/spatialdata/spatialdb/contrib
subpkgpyexecdir = $(pyexecdir)/spatialdata/spatialdb/contrib


# C++ LIBRARY ----------------------------------------------------------
# The resulting library will be libspatialcontrib.MACHINE_DEPENDENT_SUFFIX
lib_LTLIBRARIES = libspatialdbcontrib.la

# Source files for library
libspatialdbcontrib_la_SOURCES = \
	UniformVelModel.cc

# C++ Header files
noinst_HEADERS = \
	UniformVelModel.hh

# Set link flags to automake link flags
libspatialdbcontrib_la_LDFLAGS = $(AM_LDFLAGS)

# Link to spatialdata and proj libraries
libspatialdbcontrib_la_LIBADD = \
	-lspatialdata \
	-lproj
if NO_UNDEFINED
# Add linking to Python libraries if linker doesn't allow undefined symbols
libspatialdbcontrib_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

# Preprocessor flags
AM_CPPFLAGS = $(PYTHON_EGG_CPPFLAGS) -I$(PYTHON_INCDIR) 

INCLUDES = 

# SWIG PYTHON MODULE ---------------------------------------------------
# The name of the module will be _spatialdbcontribmodule.MACHINE_DEPENDENT_SUFFIX
subpkgpyexec_LTLIBRARIES = _spatialdbcontribmodule.la

# SWIG generated Python file and user-generated module initialization file.
subpkgpyexec_PYTHON = \
	spatialdbcontrib.py \
	__init__.py

# SWIG source files
swig_sources = \
	spatialdbcontrib.i \
	UniformVelModel.i

# SWIG generated files
swig_generated = \
	spatialdbcontrib_wrap.cxx \
	spatialdbcontrib.py

# Special link lags for creating Python module
_spatialdbcontribmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

# Module sources
dist__spatialdbcontribmodule_la_SOURCES = $(swig_sources) $(swig_generated)

# Link module w/spatialdbcontrib library
_spatialdbcontribmodule_la_LIBADD = libspatialdbcontrib.la
if NO_UNDEFINED
_spatialdbcontribmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

# Module uses numpy and Python header files
INCLUDES += -I$(NUMPY_INCDIR) -I$(PYTHON_INCDIR)

# Command to invoke SWIG
$(srcdir)/spatialdbcontrib_wrap.cxx $(srcdir)/spatialdbcontrib.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $(SWIG_FLAGS) $<

# Remove SWIG generated files for make clean-maintainer.
MAINTAINERCLEANFILES = $(swig_generated)



# PYTHON ---------------------------------------------------------------

nobase_subpkgpyexec_PYTHON = \
	__init__.py \
	UniformVelModel.py


# End of file 
