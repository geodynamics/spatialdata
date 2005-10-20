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
#include "coordsysgeo.h"  // CoordSysGeo bindings
#include "coordsyslocal.h"  // CoordSysLocal bindings
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
  
  // CoordSysGeo
  {pyspatialdata_geocoords_CppCoordSysGeo__name__,
   pyspatialdata_geocoords_CppCoordSysGeo,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysGeo__doc__},
  
  {pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid__name__,
   pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid__doc__},

  {pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz__name__,
   pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz__doc__},

  {pyspatialdata_geocoords_CppCoordSysGeo_datumVert__name__,
   pyspatialdata_geocoords_CppCoordSysGeo_datumVert,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysGeo_datumVert__doc__},

  {pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric__name__,
   pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric__doc__},

  {pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters__name__,
   pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters__doc__},

  // CoordSysLocal
  {pyspatialdata_geocoords_CppCoordSysLocal__name__,
   pyspatialdata_geocoords_CppCoordSysLocal,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysLocal__doc__},
  
  {pyspatialdata_geocoords_CppCoordSysLocal_localOrigin__name__,
   pyspatialdata_geocoords_CppCoordSysLocal_localOrigin,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysLocal_localOrigin__doc__},

  {pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters__name__,
   pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters,
   METH_VARARGS,
   pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters__doc__},

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
