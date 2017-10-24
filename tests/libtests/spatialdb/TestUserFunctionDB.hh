// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestUserFunctionDB.hh
 *
 * @brief C++ TestUserFunctionDB object
 *
 * C++ unit testing for UserFunctionDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testuserfunctiondb_hh)
#define spatialdata_spatialdb_testuserfunctiondb_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/spatialdbfwd.hh"

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestUserFunctionDB;
    class UserFunctionDBTestData; // USES UserFunctionDBTestData
  } // spatialdb
} // spatialdata

/// C++ unit testing for UserFunctionDB
class spatialdata::spatialdb::TestUserFunctionDB : public CppUnit::TestFixture
{ // class TestUserFunctionDB

    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE( TestUserFunctionDB );

    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testLabel );
    CPPUNIT_TEST( testAddValue );
    CPPUNIT_TEST( testCoordsys );
    CPPUNIT_TEST( testOpenClose );
    CPPUNIT_TEST( testQueryVals );
    CPPUNIT_TEST( testQuery );

    CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

    /// Setup testing data.
    void setUp(void);
    
    /// Tear down testing data.
    void tearDown(void);
    
    /// Test constructor
    void testConstructor(void);
    
    /// Test label()
    void testLabel(void);
    
    /// Test addValue()
    void testAddValue(void);
    
    /// Test coordsys()
    void testCoordsys(void);
    
    /// Test open() and close()
    void testOpenClose(void);
    
    /// Test queryVals().
    void testQueryVals(void);
    
    /// Test query().
    void testQuery(void);
    
  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Populate database with data.
   *
   * @param db Database
   * @param data Data for database
   */
  void _setupDB(UserFunctionDB* const db);

  /** Test query method by doing query and checking values returned.
   * 
   * @param db Database to query
   * @param names Names of values in database
   * @param queryData Query locations and expected values
   * @param flagsE Array of expected return values
   * @param numQueries Number of queries
   * @param spaceDim Number of coordinates per location
   * @param numVals Number of values in database
   */
  void _checkQuery(UserFunctionDB& db,
		   char** const names,
		   const double* queryData,
		   const int* flagsE,
		   const int numQueries,
		   const int spaceDim,
		   const int numVals);

protected :
  // PROTECTED MEMBERS //////////////////////////////////////////////////

  UserFunctionDBTestData* _data; ///< Test data.

}; // class TestUserFunctionDB


class spatialdata::spatialdb::TestUserFunctionDB_Data {

    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /// Constructor
    TestUserFunctionDB_Data(void);

    /// Destructor
    ~TestUserFunctionDB_Data(void);

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    int numVals; ///< Number of values in spatial database.
    const char* const* values; ///< Names of values in spatial database.
    spatialdata::spatialdb::UserFunction::UserData* functions; ///< User function values for spatial database.
    spatialdata::geocoords::CoordSys* cs; ///< Coordinate system.


    
    int spaceDim; ///< S.
    const char* meshFilename; ///< Name of file with ASCII mesh.
    const char* materialLabel; ///< Label defining cells associated with material.
    int materialId; ///< Material id.
    const char* boundaryLabel; ///< Group defining domain boundary.

    spatialdata::units::Nondimensional* normalizer; ///< Scales for nondimensionalization.

    PylithReal t; ///< Time for solution in simulation.
    PylithReal dt; ///< Time step in simulation.
    PylithReal tshift; ///< Time shift for LHS Jacobian.

    int numSolnFields; ///< Number of solution fields.
    pylith::topology::Field::Discretization* solnDiscretizations; ///< Discretizations for solution fields.
    const char* solnDBFilename; ///< Name of file with data for solution.
    const char* pertDBFilename; ///< Name of file with data for perturbation.

    int numAuxFields; ///< Number of auxiliary fields.
    const char** auxFields; ///< Names of auxiliary fields.
    pylith::topology::Field::Discretization* auxDiscretizations; ///< Discretizations for auxiliary fields.
    const char* auxDBFilename; ///< Name of file with data for auxFieldsDB.

    bool isExplicit; ///< True for explicit time stepping.
    
}; // TestUserFunctionDB_Data


#endif // spatialdata_spatialdb_testuserfunctiondb_hh


// End of file 
