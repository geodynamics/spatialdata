#!/usr/bin/env python
#
# ======================================================================
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
# ======================================================================
#
## @file geocoords/tests/libtests/data/ConvertData.py
## @brief Python data generator for coordinate conversion tests.

from pyre.components.Component import Component

# ConvertDataclass
class ConvertData(Component):
  """Python data generator for coordinate conversion tests."""

  def calculate(self):
    """Initialize."""
    raise NotImplementedError, "Method 'calculate' not implemented."
    return

  def dump(self, dumper):
    """Dump data to file.
    @li \b dumper Object used to dump data to file
    """
    raise NotImplementedError, "Method 'dump' not implemented."
    return

  def __init__(self, name='convertdata'):
    """Constructor."""
    Component.__init__(self, name, facility='convertdata')
    self._fileSrc = None
    self._fileDest = None
    self._command = None
    return

  def _convert(self, src):
    """Convert coordinates."""

    # write file
    fileSrc = open(self._fileSrc, "w")
    for coords in src:
      if len(coords) == 2:
        fileSrc.write("%.7f %.7f\n" % (coords[0], coords[1]))
      elif len(coords) == 3:
        fileSrc.write("%.7f %.7f %.7f\n" % (coords[0], coords[1], coords[2]))
    fileSrc.close()

    # call command to convert
    import popen2
    command = "%s < %s > %s" % (self._command, self._fileSrc, self._fileDest)
    p = popen2.Popen3("%s" % command)
    p.wait()

    # read data
    fileDest = open(self._fileDest, "r")
    line = fileDest.readline()
    dest = []
    while line:
      fields = line.split()
      if len(fields) == 2:
        dest.append([float(fields[0]), float(fields[1])])
      elif len(fields) == 3:
        dest.append([float(fields[0]), float(fields[1]), float(fields[2])])
      line = fileDest.readline()
    fileDest.close()
    
    p = popen2.Popen3("rm %s %s" % (self._fileSrc, self._fileDest))
    p.wait()

    return dest

# version
__id__ = "$Id: ConvertData.py,v 1.1 2005/05/25 17:30:21 baagaard Exp $"

# End of file 
