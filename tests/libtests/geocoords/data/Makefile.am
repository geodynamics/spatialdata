# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

noinst_HEADERS = \
	TestConverter.dat \
	TestCSGeoLocalCart.dat \
	TestCSGeoProj.dat \
	TestGeoid.dat \
	TestProjector.dat

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/libtests/geocoords/data

datfiles: \
	TestConverter \
	TestCSGeoLocalCart \
	TestCSGeoProj \
	TestProjector

TestConverter:
	ConvertDataApp.py \
		--data=converter \
		--dumper.className=spatialdata::geocoords::TestConverter \
		--dumper.filename=TestConverter.dat

TestCSGeoLocalCart:
	ConvertDataApp.py \
		--data=csgeolocalcart \
		--dumper.className=spatialdata::geocoords::TestCSGeoLocalCart \
		--dumper.filename=TestCSGeoLocalCart.dat

TestCSGeoProj:
	ConvertDataApp.py \
		--data=csgeoproj \
		--dumper.className=spatialdata::geocoords::TestCSGeoProj \
		--dumper.filename=TestCSGeoProj.dat

TestProjector:
	ConvertDataApp.py \
		--data=projector \
		--dumper.className=spatialdata::geocoords::TestProjector \
		--dumper.filename=TestProjector.dat


# version
# $Id$

# End of file 
