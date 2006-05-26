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

SUBDIRS = \
	libsrc

if ENABLE_PYTHIA
  SUBDIRS += modulesrc spatialdata
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

# version
# $Id$

# End of file 
