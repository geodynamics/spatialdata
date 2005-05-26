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

PROJECT = spatialdata
PACKAGE = spatialdb/tests/libtests

include local.def

PROJ_SRCS = \
	TestSimpleDBQuery.cc \
	TestSimpleDB.cc \
	TestSimpleDBPoint.cc \
	TestSimpleDBLine.cc \
	TestSimpleDBArea.cc \
	TestSimpleDBVolume.cc \
	TestSimpleIOAscii.cc \
	TestSpatialDB.cc \
	testspatial.cc \


RECURSE_DIRS = \
	data \

PROJ_BIN = $(PROJ_BINDIR)/testspatial

# ----------------------------------------------------------------------
all: $(PROJ_BIN)

$(PROJ_BIN):: $(PROJ_OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $(LCXXFLAGS) $(PROJ_OBJS)

test:
	@LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(BLD_LIBDIR) $(PROJ_BIN)

export:: export-binaries

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

EXPORT_BINS = $(PROJ_BIN)

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:43:04 baagaard Exp $

# End of file 
