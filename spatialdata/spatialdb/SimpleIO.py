# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

# @file spatialdata/spatialdb/SimpleIO.py
#
# @brief Python I/O manager for simple spatial database (SimpleDB).
#
# Factory: simpledb_io

from pythia.pyre.components.Component import Component


def validateFilename(value):
    """
    Validate filename.
    """
    if 0 == len(value):
        raise ValueError("Filename for spatial database not specified.")
    try:
        fin = open(value, "r")
    except IOError:
        raise IOError("Spatial database file '{}' not found.".format(value))
    return value


class SimpleIO(Component):
    """
    Abstract base class for writing a simple spatial database (SimpleDB).
    """
    DOC_CONFIG = {
        "cfg": """
            [dbio]
            filename = mat_elastic.spatialdb
            """,
    }

    import pythia.pyre.inventory

    filename = pythia.pyre.inventory.str("filename", default="", validator=validateFilename)
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
