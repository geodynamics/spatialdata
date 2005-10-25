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

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
// Call SpatialDB:Query().
extern "C"
void spatialdb_query(void* db, 
		     double** pVals,
		     const int numVals,
		     const double x,
		     const double y,
		     const double z,
		     const void* cs)
{ // spatialdb_query
  spatialdata::spatialdb::SpatialDB* pDB = 
    (spatialdata::spatialdb::SpatialDB*) db;
  const spatialdata::geocoords::CoordSys* pCS = 
    (const spatialdata::geocoords::CoordSys*) cs;
  FIREWALL(0 != pDB);
  FIREWALL(0 != pCS);
  pDB->query(pVals, numVals, x, y, z, pCS);
} // spatialdb_query

// version
// $Id: cspatialdb.cc,v 1.1 2005/05/25 18:42:57 baagaard Exp $

// End of file
