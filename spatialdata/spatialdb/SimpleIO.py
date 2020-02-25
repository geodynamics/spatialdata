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

# @file spatialdata/spatialdb/SimpleIO.py
#
# @brief Python I/O manager for simple spatial database (SimpleDB).
#
# Factory: simpledb_io

from pyre.components.Component import Component


def validateFilename(value):
    """
    Validate filename.
    """
    if 0 == len(value):
        raise ValueError("Filename for spatial database not specified.")
    return value


class SimpleIO(Component):
    """
    Python I/O manager for simple database (SimpleDB).

    Factory: simpledb_io

    INVENTORY

    Properties
      - *filename* Name of spatial database file.

    Facilities
      - None
    """

    import pyre.inventory

    filename = pyre.inventory.str("filename", default="", validator=validateFilename)
    filename.meta['tip'] = "Name of database file."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="simpleio"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="simpledb_io")
        self._createModuleObj()

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        raise NotImplementedError("_createModuleObj() not implemented.")
        return

    def _validateData(self, data):
        """
        Check consistency of database data.
        """
        (numLocs, spaceDim) = data['points'].shape
        cs = data['coordsys']
        if spaceDim != cs.getSpaceDim():
            raise ValueError("Simple database '%s' space-dim (%d) does not agree with spatial "
                             "dimension of coordinate system (%d)." %
                             (self.filename, spaceDim, cs.getSpaceDim()))


# FACTORIES ////////////////////////////////////////////////////////////

def simpledb_io():
    """
    Factory associated with SimpleIO.
    """
    return SimpleIO()


# End of file
