// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2013 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#if !defined(spatialdata_spatialdb_simplegriddbtestdata_hh)
#define spatialdata_spatialdb_simplegriddbtestdata_hh

namespace spatialdata {
  namespace spatialdb {
     class SimpleGridDBTestData;
  } // spatialdb
} // spatialdata

class spatialdata::spatialdb::SimpleGridDBTestData
{

// PUBLIC METHODS ///////////////////////////////////////////////////////
public :
  
  /// Constructor
  SimpleGridDBTestData(void);

  /// Destructor
  ~SimpleGridDBTestData(void);

// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:
  
  /// @name Database information
  //@{
  int numX; ///< Number of locations in x dimension.
  int numY; ///< Number of locations in x dimension.
  int numZ; ///< Number of locations in x dimension.
  int spaceDim; ///< Spatial dimension for coordinates of locations
  int numVals; ///< Number of values per location in database
  int dataDim; ///< Spatial dimension of data in database
  double* dbX; ///< Coordinates along x dimension.
  double* dbY; ///< Coordinates along x dimension.
  double* dbZ; ///< Coordinates along x dimension.
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

  /// @io I/O information
  //@{
  char* filename; ///< Filename of matching spatial database.
  //@}

};

#endif // spatialdata_spatialdb_simplegriddbtestdata_hh


// End of file
