// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include <portinfo>

extern "C" {
#include "cspatialdb.h"
}

#include "spatialdata/spatialdb/SpatialDB.h" /* USES SpatialDB */

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL

// ----------------------------------------------------------------------
// Call SpatialDB:Query().
extern "C"
void spatialdb_query(void* db, 
		     double** pVals,
		     const int numVals,
		     const double* x,
		     const double* y,
		     const double* z)
{ // spatialdb_query
  spatialdata::spatialdb::SpatialDB* pDB = 
    (spatialdata::spatialdb::SpatialDB*) db;
  FIREWALL(0 != pDB);
  FIREWALL(0 != x);
  FIREWALL(0 != y);
  FIREWALL(0 != z);
  pDB->Query(pVals, numVals, *x, *y, *z);
} // spatialdb_query

// version
// $Id: cspatialdb.cc,v 1.1 2005/05/25 18:42:57 baagaard Exp $

// End of file
