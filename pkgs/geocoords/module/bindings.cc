// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
//
// ----------------------------------------------------------------------
//

#include <portinfo>
#include <Python.h>

#include "misc.h" // misc methods

#include "converter.h"  // Converter bindings
#include "coordsys.h"  // CoordSys bindings
#include "cscart.h"  // CSCart bindings
#include "csgeo.h"  // CSGeo bindings
#include "csgeolocalcart.h"  // CSGeoLocalCart bindings
#include "csgeoproj.h"  // CSGeoProj bindings
#include "projector.h"  // Projector bindings

// the method table
struct PyMethodDef pyspatialdata_geocoords_methods[] = {

  // Converter
  {pyspatialdata_geocoords_CppConverter_convert__name__,
   pyspatialdata_geocoords_CppConverter_convert,
   METH_VARARGS,
   pyspatialdata_geocoords_CppConverter_convert__doc__},
  
  // CoordSys
  {pyspatialdata_geocoords_CppCoordSys_initialize__name__,
   pyspatialdata_geocoords_CppCoordSys_initialize,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSys_initialize__doc__},
  
  // CSCart
  {pyspatialdata_geocoords_CppCSCart__name__,
   pyspatialdata_geocoords_CppCSCart,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSCart__doc__},
  
  {pyspatialdata_geocoords_CppCSCart_toMeters__name__,
   pyspatialdata_geocoords_CppCSCart_toMeters,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSCart_toMeters__doc__},

  // CSGeo
  {pyspatialdata_geocoords_CppCSGeo__name__,
   pyspatialdata_geocoords_CppCSGeo,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeo__doc__},
  
  {pyspatialdata_geocoords_CppCSGeo_ellipsoid__name__,
   pyspatialdata_geocoords_CppCSGeo_ellipsoid,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeo_ellipsoid__doc__},

  {pyspatialdata_geocoords_CppCSGeo_datumHoriz__name__,
   pyspatialdata_geocoords_CppCSGeo_datumHoriz,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeo_datumHoriz__doc__},

  {pyspatialdata_geocoords_CppCSGeo_datumVert__name__,
   pyspatialdata_geocoords_CppCSGeo_datumVert,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeo_datumVert__doc__},

  {pyspatialdata_geocoords_CppCSGeo_isGeocentric__name__,
   pyspatialdata_geocoords_CppCSGeo_isGeocentric,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeo_isGeocentric__doc__},

  {pyspatialdata_geocoords_CppCSGeo_toMeters__name__,
   pyspatialdata_geocoords_CppCSGeo_toMeters,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeo_toMeters__doc__},

  // CSGeoLocalCart
  {pyspatialdata_geocoords_CppCSGeoLocalCart__name__,
   pyspatialdata_geocoords_CppCSGeoLocalCart,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeoLocalCart__doc__},
  
  {pyspatialdata_geocoords_CppCSGeoLocalCart_origin__name__,
   pyspatialdata_geocoords_CppCSGeoLocalCart_origin,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeoLocalCart_origin__doc__},

  // CSGeoProj
  {pyspatialdata_geocoords_CppCSGeoProj__name__,
   pyspatialdata_geocoords_CppCSGeoProj,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeoProj__doc__},
  
  {pyspatialdata_geocoords_CppCSGeoProj_projector__name__,
   pyspatialdata_geocoords_CppCSGeoProj_projector,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCSGeoProj_projector__doc__},

  // Projector
  {pyspatialdata_geocoords_CppProjector__name__,
   pyspatialdata_geocoords_CppProjector,
   METH_VARARGS,
   pyspatialdata_geocoords_CppProjector__doc__},
  
  {pyspatialdata_geocoords_CppProjector_projection__name__,
   pyspatialdata_geocoords_CppProjector_projection,
   METH_VARARGS,
   pyspatialdata_geocoords_CppProjector_projection__doc__},

  {pyspatialdata_geocoords_CppProjector_units__name__,
   pyspatialdata_geocoords_CppProjector_units,
   METH_VARARGS,
   pyspatialdata_geocoords_CppProjector_units__doc__},

  {pyspatialdata_geocoords_CppProjector_projOptions__name__,
   pyspatialdata_geocoords_CppProjector_projOptions,
   METH_VARARGS,
   pyspatialdata_geocoords_CppProjector_projOptions__doc__},

  {pyspatialdata_geocoords_CppProjector_initialize__name__,
   pyspatialdata_geocoords_CppProjector_initialize,
   METH_VARARGS,
   pyspatialdata_geocoords_CppProjector_initialize__doc__},

  {pyspatialdata_geocoords_CppProjector_project__name__,
   pyspatialdata_geocoords_CppProjector_project,
   METH_VARARGS,
   pyspatialdata_geocoords_CppProjector_project__doc__},

  {pyspatialdata_geocoords_CppProjector_invproject__name__,
   pyspatialdata_geocoords_CppProjector_invproject,
   METH_VARARGS,
   pyspatialdata_geocoords_CppProjector_invproject__doc__},

  // misc
  {pyspatialdata_geocoords_copyright__name__,
   pyspatialdata_geocoords_copyright,
   METH_VARARGS,
   pyspatialdata_geocoords_copyright__doc__},

  // Sentinel
  {0, 0}

}; // pyspatialdata_geocoords_methods

// version
// $Id: bindings.cc,v 1.2 2005/06/02 21:35:36 baagaard Exp $

// End of file
