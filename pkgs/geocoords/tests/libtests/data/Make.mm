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
	TestCoordSysLocal \
	TestProjector \

TestConverter:
	ConvertDataApp.py \
		--data=converter \
		--dumper.className=spatialdata::geocoords::TestConverter \
		--dumper.filename=TestConverter.dat

TestCoordSysLocal:
	ConvertDataApp.py \
		--data=coordsyslocal \
		--dumper.className=spatialdata::geocoords::TestCoordSysLocal \
		--dumper.filename=TestCoordSysLocal.dat

TestProjector:
	ConvertDataApp.py \
		--data=projector \
		--dumper.className=spatialdata::geocoords::TestProjector \
		--dumper.filename=TestProjector.dat

# ----------------------------------------------------------------------

# version
# $Id: Make.mm,v 1.1 2005/05/25 17:30:44 baagaard Exp $

# End of file 
