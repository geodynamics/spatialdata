#!/bin/bash
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

if (( $# != 1 )); then
  echo "usage: generate.sh simpledbquery|simpledb|all"
  exit 1
fi

# //////////////////////////////////////////////////////////////////////
if [ $1 == "simpledbquery" ] || [ $1 == "all" ]; then

  python SimpleDBQueryData3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBQueryData3D \
    --data.parent=SimpleDBQueryData

fi

# //////////////////////////////////////////////////////////////////////
if [ $1 == "simpledb" ] || [ $1 == "all" ]; then

  # Point --------------------------------------------------------------

  python SimpleDBTestDataPoint3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBTestDataPoint3D \
    --data.parent=SimpleDBTestData

  python SimpleDBTestDataLine3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBTestDataLine3D \
    --data.parent=SimpleDBTestData

  python SimpleDBTestDataArea3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBTestDataArea3D \
    --data.parent=SimpleDBTestData

  python SimpleDBTestDataVolume3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBTestDataVolume3D \
    --data.parent=SimpleDBTestData

fi


# End of file 
