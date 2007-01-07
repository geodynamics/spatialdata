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

#if !defined(spatialdata_spatialdb_simpledbdata_hh)
#define spatialdata_spatialdb_simpledbdata_hh

namespace spatialdata {
  namespace spatialdb {
     class SimpleDBData;
  } // spatialdb
} // spatialdata

class spatialdata::spatialdb::SimpleDBData
{

// PUBLIC METHODS ///////////////////////////////////////////////////////
public :
  
  /// Constructor
  SimpleDBData(void);

  /// Destructor
  ~SimpleDBData(void);

// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:
  
  /// @name Database information
  //@{
  int numLocs; ///< Number of locations in database
  int spaceDim; ///< Spatial dimension for coordinates of locations
  int numVals; ///< Number of values per location in database
  int dataDim; ///< Spatial dimension of data in database
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

#endif // spatialdata_spatialdb_simpledbdata_hh


// End of file
