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

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	libsrc \
	templates

if ENABLE_PYTHIA
  SUBDIRS += modulesrc spatialdata applications
endif

if ENABLE_DOCUMENTATION
  SUBDIRS += doc
endif

if ENABLE_TESTING
  SUBDIRS += tests
endif

DISTCHECK_CONFIGURE_FLAGS = \
	--enable-testing \
	--enable-pythia \
	--enable-documentation \
	CPPFLAGS="-I${PROJ4_INCDIR} -I${CPPUNIT_INCDIR} -I${PYTHIA_INCDIR} -I${CIG_INCDIR}" \
	LDFLAGS="-L${PROJ4_LIBDIR} -L${CPPUNIT_LIBDIR} -L${CIG_LIBDIR}"

EXTRA_DIST = \
	CHANGES


# End of file 
