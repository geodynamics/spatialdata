#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2014 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#
## @file tests/libtests/data/SimpleDBQueryData.py
## @brief Python data generator abstract base class for SimpleDB tests.

from pyre.components.Component import Component

# SimpleDBQueryData class
class SimpleDBQueryData(Component):
  """Python data generator abstract base class for SimpleDB tests."""

  def initialize(self):
    return

  def __init__(self, name='simpledbquerydata'):
    """Constructor."""
    Component.__init__(self, name, facility='query_data')
    return

  def dump(self, dumper):
    """Dump data to file."""
    dumper.open(self.name)

    numLocs = self._numLocs
    numVals = self._numVals

    if not len(self._names) == numVals:
      ERROR
    if not len(self._data) == numLocs*(3+numVals):
      ERROR

    dumper.writeVal("int", "NUMLOCS", numLocs, "%d")
    dumper.writeVal("int", "NUMVALS", numVals, "%d")
    dumper.writeArray("double", "COORDS", self._data, "%18.10e,", 3)
    dumper.writeArray("double", "DATA", self._data, "%18.10e,", numVals)
    dumper.writeArray("int", "ERRFLAGS", self._errFlags, "%2d,", 1)
    dumper.writeArray("char*", "NAMES", self._names, "  \"%s\",", 1)
    dumper.writeArray("char*", "UNITS", self._units, "  \"%s\",", 1)
    dumper.writeVal("spatialdata::spatialdb::SimpleDB::TopoEnum", "TOPOLOGY",
                    self._topology, "%s")

    numQueries = self._numQueries
    if not len(self._qldata) == numQueries*(3+numVals):
      ERROR
    if not len(self._qndata) == numQueries*(3+numVals):
      ERROR
      
    dumper.writeVal("int", "NUMQUERIES", numQueries, "%d")
    dumper.writeArray("double", "QUERYLINEAR", self._qldata, "%16.8e,",
                      3+numVals)
    dumper.writeArray("double", "QUERYNEAREST", self._qndata, "%16.8e,",
                      3+numVals)

    dumper.close()
    return


# End of file 
