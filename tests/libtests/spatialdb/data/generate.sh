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

  python SimpleDBDataPoint3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBDataPoint3D \
    --data.parent=SimpleDBData

  python SimpleDBDataLine3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBDataLine3D \
    --data.parent=SimpleDBData

  python SimpleDBDataArea3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBDataArea3D \
    --data.parent=SimpleDBData

  python SimpleDBDataVolume3D.py \
    --data.namespace=spatialdata,spatialdb \
    --data.object=SimpleDBDataVolume3D \
    --data.parent=SimpleDBData

fi


# End of file 
