// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/spatialdb/SimpleDB.i
 *
 * @brief SWIG interface to C++ SimpleDB object.
 */

namespace spatialdata {
  namespace spatialdb {
    class SimpleIO; // USES SimpleIO

    class SimpleDB : public SpatialDB
    { // class SimpleDB

    public :
      // PUBLIC ENUM ////////////////////////////////////////////////////

      /** Topology of spatial data */
      enum TopoEnum { 
	POINT=0,
	LINE=1,
	AREA=2,
	VOLUME=3
      };
      
      /** Type of query */
      enum QueryEnum {
	NEAREST=0,
	LINEAR=1
      };

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor.
      SimpleDB(void);
  
      /** Constructor with label.
       *
       * @param label Label of database
       */
      SimpleDB(const char* label);
      
      /// Default destructor.
      ~SimpleDB(void);
      
      /// Open the database and prepare for querying.
      void open(void);
      
      /// Close the database.
      void close(void);
      
      /** Set query type.
       *
       * @pre Must call Open() before QueryType()
       *
       * @param queryType Set type of query
       */
      void queryType(const SimpleDB::QueryEnum queryType);
      
      /** Set values to be returned by queries.
       *
       * @pre Must call open() before queryVals()
       *
       * @param names Names of values to be returned in queries
       * @param numVals Number of values to be returned in queries
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* names,
	 const int numVals)
	  };
      void queryVals(const char* const* names,
		     const int numVals);
      %clear(const char* const* names, const int numVals);
      
      /** Set the I/O handler.
       *
       * @param iohandler
       */
      void ioHandler(const SimpleIO* iohandler);
      
      /** Query the database.
       *
       * @pre Must call open() before query()
       *
       * @param vals Array for computed values (output from query), vals
       *   must be allocated BEFORE calling query().
       * @param numVals Number of values expected (size of pVals array)
       * @param coords Coordinates of point for query
       * @param numDims Number of dimensions for coordinates
       * @param pCSQuery Coordinate system of coordinates
       *
       * @returns 0 on success, 1 on failure (i.e., could not interpolate
       *   so values set to 0)
       */
      %apply(double* INPLACE_ARRAY1, int DIM1) {
	(double* vals,
	 const int numVals)
	  };
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* coords,
	 const int numDims)
	  };
      int query(double* vals,
		const int numVals,
		const double* coords,
		const int numDims,
		const spatialdata::geocoords::CoordSys* pCSQuery);
      %clear(double* vals, const int numVals);
      %clear(const double* coords, const int numDims);
      
    }; // class SimpleDB
    
  } // spatialdb
} // spatialdata


// End of file 
