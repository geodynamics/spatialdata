#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#
## @file tests/libtests/data/TestSimpleDBQuery.py
## @brief Python application to generate data for SimpleDBQuery tests.

from Numeric import *
from LinearAlgebra import *

from pyre.applications.Script import Script

# TestSimpleDBQuery class
class TestSimpleDBQuery(Script):
  """Python application to generate data for SimpleDBQuery tests."""

  def main(self, *args, **kwds):
    """Run the application."""
    self._transformCoords()
    self._dump()

  def __init__(self):
    """Constructor."""
    Script.__init__(self, 'testsimpledbquery')
    self._numLocs = 5
    self._numVals = 2
    self._data = [  0.0, 0.0, 0.0, 1.1, 5.5,
                    1.0, 0.1, 0.3, 2.2, 6.6,
                    2.0, 0.2, 0.2, 3.3, 7.7,
                    3.0, 0.3, 0.1, 4.4, 8.8,
                    4.0, 0.4, 0.9, 4.5, 9.9 ]
    self._names = [ "One", "Two" ]
    self._topology = "spatial::SimpleDB::VOLUME"

    self._pqr = [ [0.1, 0.0, 0.0],
                  [0.4, 0.0, 0.0],
                  [0.3, 0.6, 0.0],
                  [0.3, 0.4, 0.5] ]
    return

  def _transformCoords(self):
    """Transform coordinates."""
    o = [2.0, 4.2, 3.1]
    a = [9.5, 2.8, 3.4]
    b = [5.2, 9.3, 4.8]
    c = [2.9, 8.5, 6.6]
    self._xyz = []
    for pqr in self._pqr:
      x = o[0] + a[0]*pqr[0] + b[0]*pqr[1] + c[0]*pqr[2];
      y = o[1] + a[1]*pqr[0] + b[1]*pqr[1] + c[1]*pqr[2];
      z = o[2] + a[2]*pqr[0] + b[2]*pqr[1] + c[2]*pqr[2];
      self._xyz.append([x, y, z])
    return
  
  def _dump(self):
    """Dump data to file."""
    dumper = self.inventory.dumper
    dumper.open(self.name)

    dumper.writeVal("int", "NUMLOCS", self._numLocs, "%d")
    dumper.writeVal("int", "NUMVALS", self._numVals, "%d")
    dumper.writeArray("double", "DATA", self._data, "%12.4e,", 5)
    dumper.writeArray("char*", "NAMES", self._names, "  \"%s\",", 1)
    dumper.writeVal("spatial::SimpleDB::TopoEnum", "TOPOLOGY",
                    self._topology, "%s")
    
    dumper.writeArray("double", "COORDS", ravel(self._xyz), "%20.12e,", 3)
    dumper.writeVal("int", "NUMPTS", len(self._xyz), "%d")
    dumper.writeVal("double", "DIST2", self._distSquared(), "%20.12e")
    dumper.writeVal("double", "AREA", self._area(), "%20.12e")
    dumper.writeArray("double", "AREADIR", self._areaDir(), "%20.12e,", 3)
    dumper.writeVal("double", "VOLUME", self._volume(), "%20.12e")

    dumper.close()
    return

  def _distSquared(self):
    a = self._xyz[0]
    b = self._xyz[1]
    J = array( ( [-a[0]+b[0], -a[1]+b[1], -a[2]+b[2] ] ), Float)
    dist2 = matrixmultiply(J, transpose(J))
    return dist2

  def _area(self):
    a = self._xyz[0]
    b = self._xyz[1]
    c = self._xyz[2]
    J = array(( [-a[0]+b[0], -a[1]+b[1], -a[2]+b[2]],
                [-a[0]+c[0], -a[1]+c[1], -a[2]+c[2]]), Float)
    area = 0.5*sqrt(determinant(matrixmultiply(J, transpose(J))))
    return area

  def _areaDir(self):
    a = self._xyz[0]
    b = self._xyz[1]
    c = self._xyz[2]
    u = [-a[0]+b[0], -a[1]+b[1], -a[2]+b[2]]
    v = [-a[0]+c[0], -a[1]+c[1], -a[2]+c[2]]
    area = self._area()
    dirABC = [ 0.5*(u[1]*v[2]-u[2]*v[1])/area,
               0.5*(u[2]*v[0]-u[0]*v[2])/area,
               0.5*(u[0]*v[1]-u[1]*v[0])/area]
    return dirABC

  def _volume(self):
    a = self._xyz[0]
    b = self._xyz[1]
    c = self._xyz[2]
    d = self._xyz[3]
    J = array(([-a[0]+b[0], -a[1]+b[1], -a[2]+b[2]],
               [-a[0]+c[0], -a[1]+c[1], -a[2]+c[2]],
               [-a[0]+d[0], -a[1]+d[1], -a[2]+d[2]]), Float)
    volume = determinant(J)/6.0
    return volume

  class Inventory(Script.Inventory):
    ## @class Inventory
    ## Python object for managing TestSimpleDBQuery facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b dumper Dump data to file

    import pyre.inventory
    from pythiautil.DumpCpp import DumpCpp
    dumper = pyre.inventory.facility('dumper', factory=DumpCpp)

# main
if __name__ == '__main__':
  app = TestSimpleDBQuery()
  app.run()

# version
__id__ = "$Id: TestSimpleDBQuery.py,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $"

# End of file 
