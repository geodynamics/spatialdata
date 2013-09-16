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

#if !defined(spatialdata_spatialdb_simpledbquerydata_hh)
#define spatialdata_spatialdb_simpledbquerydata_hh

namespace spatialdata {
  namespace spatialdb {
     class SimpleDBQueryData;
  } // spatialdata
} // spatialdb

class spatialdata::spatialdb::SimpleDBQueryData
{

// PUBLIC METHODS ///////////////////////////////////////////////////////
public :
  
  /// Constructor
  SimpleDBQueryData(void);

  /// Destructor
  ~SimpleDBQueryData(void);

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
  int numPts; ///< Number of points for locations
  double* coords; ///< Coordinates of query locations
  double dist2; ///< Expected value for distance squared
  double area; ///< Expected value for area
  double* areaDir; ///< Expected value for area direction
  double volume; ///< Expected value for volume
  //@}


};

#endif // spatialdata_spatialdb_simpledbquerydata_hh

// End of file
