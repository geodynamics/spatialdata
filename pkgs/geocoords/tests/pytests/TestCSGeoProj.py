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

import unittest

class TestCSGeoProj(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.Projector import Projector
    proj = Projector()
    proj.falseEasting = -100.0
    proj.falseNorthing = 30.0
    proj.scaleFactor = 0.9995

    from spatialdata.geocoords.CSGeoProj import CSGeoProj
    cs = CSGeoProj()
    cs.ellipsoid = "clrk66"
    cs.datumHoriz = "NAD27"
    cs.datumVert = "mean sea level"
    cs.units = "km"
    cs.projector = proj
    
    return

# version
__id__ = "$Id$"

# End of file 
