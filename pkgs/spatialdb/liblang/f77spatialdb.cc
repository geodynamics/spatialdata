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
#include "f77spatialdb.h"

extern "C" {
#include "cspatialdb.h"
}

#include "spatialdata/spatialdb/SpatialDB.h" /* USES SpatialDB */

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL

// ----------------------------------------------------------------------
// Call SpatialDB:Query().
extern "C"
void spatialdb_query_f(void* db, 
		       double* pVals,
		       const int* numVals,
		       const double* x,
		       const double* y,
		       const double* z,
		       const void* cs)
{ // spatialdb_query_f
  spatialdata::spatialdb::SpatialDB* pDB = 
    (spatialdata::spatialdb::SpatialDB*) db;
  const spatialdata::geocoords::CoordSys* pCS = 
    (const spatialdata::geocoords::CoordSys*) cs;
  FIREWALL(0 != pDB);
  FIREWALL(0 != pCS);
  FIREWALL(0 != x);
  FIREWALL(0 != y);
  FIREWALL(0 != z);
  pDB->query(&pVals, *numVals, *x, *y, *z, pCS);
} // spatialdb_query_f

// version
// $Id: f77spatialdb.cc,v 1.1 2005/05/25 18:42:58 baagaard Exp $

// End of file
