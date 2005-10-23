# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ----------------------------------------------------------------------
#

PROJECT = spatialdata/geocoords/tests/libtests
PACKAGE = data

default all:

datfiles: \
	TestConverter \
	TestCSGeoLocalCart \
	TestCSGeoProj \
	TestProjector \

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

# ----------------------------------------------------------------------

# version
# $Id: Make.mm,v 1.1 2005/05/25 17:30:44 baagaard Exp $

# End of file 
