// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#if !defined(spatialdata_spatialdb_simpledbtestdata_hh)
#define spatialdata_spatialdb_simpledbtestdata_hh

namespace spatialdata {
  namespace spatialdb {
     class SimpleDBTestData;
  } // spatialdb
} // spatialdata

class spatialdata::spatialdb::SimpleDBTestData
{

// PUBLIC METHODS ///////////////////////////////////////////////////////
public :
  
  /// Constructor
  SimpleDBTestData(void);

  /// Destructor
  ~SimpleDBTestData(void);

// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:
  
  /// @name Database information
  //@{
  int numLocs; ///< Number of locations in database
  int spaceDim; ///< Spatial dimension for coordinates of locations
  int numVals; ///< Number of values per location in database
  int dataDim; ///< Spatial dimension of data in database
  double* dbCoords; ///< Database locations
  double* dbData; ///< Database data
  char** names; ///< Names of values in database
  char** units; ///< Units of values in database
  //@}

  /// @name Query information
  //@{
  int numQueries; ///< Number of queries
  double* queryNearest; ///< Data for nearest neighbor queries
  double* queryLinear; ///< Data for linear interpolation queries
  int* errFlags; ///< Expected return values for queries
  //@}

};

#endif // spatialdata_spatialdb_simpledbtestdata_hh


// End of file
