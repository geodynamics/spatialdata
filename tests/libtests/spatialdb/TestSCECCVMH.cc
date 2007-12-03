// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSCECCVMH.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SCECCVMH.hh" // USES SCECCVMH

#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include <math.h> // USES fabs()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSCECCVMH );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestSCECCVMH::testConstructor(void)
{ // testConstructor
  SCECCVMH db;
} // testConstructor

// ----------------------------------------------------------------------
// Test Label().
void
spatialdata::spatialdb::TestSCECCVMH::testLabel(void)
{ // testLabel
  SCECCVMH db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test dataDir().
void
spatialdata::spatialdb::TestSCECCVMH::testDataDir(void)
{ // testDataDir
  SCECCVMH db;

  const char* dir = "/path/to/data/dir";

  db.dataDir(dir);

  CPPUNIT_ASSERT_EQUAL(std::string(dir), std::string(db._dataDir));
} // testDataDir

// ----------------------------------------------------------------------
// Test queryVals().
void
spatialdata::spatialdb::TestSCECCVMH::testQueryVals(void)
{ // testQueryVals
  SCECCVMH db;

  { // all values
    const int querySize = 7;
    const char* queryNames[] = { 
      "moho-depth",
      "topo-elev",
      "vp-tag",
      "Basement-Depth",
      "vP",
      "DenSity",
      "VS"
    };
    const int queryVals[] = { 
      SCECCVMH::QUERY_MOHODEPTH,
      SCECCVMH::QUERY_TOPOELEV,
      SCECCVMH::QUERY_VPTAG,
      SCECCVMH::QUERY_BASEDEPTH,
      SCECCVMH::QUERY_VP,
      SCECCVMH::QUERY_DENSITY,
      SCECCVMH::QUERY_VS
    };

    db.queryVals(queryNames, querySize);
    CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
    for (int i=0; i < querySize; ++i)
      CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryVals[i]);
  } // all values

  { // subset of values
    const int querySize = 3;
    const char* queryNames[] = { 
      "Basement-Depth",
      "vp-tag",
      "VS"
    };
    const int queryVals[] = { 
      SCECCVMH::QUERY_BASEDEPTH,
      SCECCVMH::QUERY_VPTAG,
      SCECCVMH::QUERY_VS
    };

    db.queryVals(queryNames, querySize);
    CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
    for (int i=0; i < querySize; ++i)
      CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryVals[i]);
  } // subset of values
} // testQueryVals

#if defined(SCECCVMH_DATADIR)
// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestSCECCVMH::testQuery(void)
{ // testQuery
  SCECCVMH db;
  db.dataDir(SCECCVMH_DATADIR);

  spatialdata::geocoords::CSGeo cs;
  cs.ellipsoid("clrk66");
  cs.datumHoriz("NAD27");
  cs.datumVert("mean sea level");
  cs.initialize();

  const int numLocs = 14;
  const int spaceDim = 3;
  const double lonlatelev[] = {
    -118.560000,  32.550000,  -2450.00,
    -118.513208,  33.884888,  -1400.00,
    -118.520000,  34.120000,  -1400.00,
    -116.400000,  32.340000,  -1000.00,
    -118.337765,  34.095691,  -1770.00,
    -118.337765,  34.095691, -17700.00,
    -117.989344,  34.034148,  -3000.00,

    -125.000000,  35.000000,  -40000.0, // outside domain
    -125.000000,  35.000000,  -35000.0,
    -125.000000,  35.000000,  -28300.0,
    -125.000000,  35.000000,  -15000.0,
    -125.000000,  35.000000,  -4000.0,
    -125.000000,  35.000000,  0.0,

    -117.989344,  34.034148,  5000.00, // above domain
  };
  const double tolerance = 1.0e-06;

  db.open();
  { // all values
    const int querySize = 7;
    const char* queryNames[] = { 
      "moho-depth",
      "topo-elev",
      "vp-tag",
      "Basement-Depth",
      "vP",
      "DenSity",
      "VS"
    };
    const double values[] = {
      -27991.001953, -1115.499268,  2.0, -1326.415405,  5560.209473,  3133.403158,  3333.334131,
      //-27991.00,   -1115.50,      2.00,   -1326.42, 5540.545410,   3126.848633,   3323.004705,
      -27165.316406,   -56.893856,  2.0, -1431.710449,  4384.126953,  2741.375651,  2584.759474,
      -31178.105469,   489.975189,  2.0,    26.471289,  4142.553223,  2660.851074,  2398.752778,
      -34526.414062,   801.209961,  2.0,   631.073059,  5226.578125,  3022.192708,  3148.777736,
      -27857.322266,   106.671280,  3.0, -2361.386963,  4181.372070,  2673.790690,  2432.217302,
      -27857.322266,   106.671280,  0.0, -2361.386963,  6351.574219,  3397.191406,  3707.466394,
      -28512.111328,    93.515053,  2.0, -2860.919189,  4932.721191,  2924.240397,  2968.477965,

      -99999.0, -99999.0, -99999.0, -99999.0, 7800.0, 3880.0, 4459.294240,
      -99999.0, -99999.0, -99999.0, -99999.0, 7800.0, 3880.0, 4459.294240,
      -99999.0, -99999.0, -99999.0, -99999.0, 7532.0, 3790.666667, 4282.106907,
      -99999.0, -99999.0, -99999.0, -99999.0, 7000.0, 3613.333333, 3998.100000,
      -99999.0, -99999.0, -99999.0, -99999.0, 5924.4444444, 3254.814814, 3514.068087,
      -99999.0, -99999.0, -99999.0, -99999.0, 5000.0, 2946.666667, 3011.300000,

      -28512.111328,    93.515053,  -99999.0, -2860.919189, -99999.0, -99999.0, -99999.0,
    };
    const int flags[] = {
      0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1,
      1,
    };

    db.queryVals(queryNames, querySize);

    double data[querySize];

    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
      CPPUNIT_ASSERT_EQUAL(flags[iLoc], err);

      for (int iVal=0; iVal < querySize; ++iVal) {
	const double dataE = values[iLoc*querySize+iVal];
	if (fabs(dataE) > tolerance)
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, data[iVal]/dataE, tolerance);
	else
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(dataE, data[iVal], tolerance);
      } // for
    } // for
  } // all values

  { // subset values
    const int querySize = 2;
    const char* queryNames[] = { 
      "DenSity",
      "vp-tag",
    };
    const double values[] = {
      3133.403158,   2.0,
      2741.375651,   2.0,
      2660.851074,   2.0,
      3022.192708,   2.0,
      2673.790690,   3.0,
      3397.191406,   0.0,
      2924.240397,   2.0,
      3880.000000, -99999.00,    
      3880.000000, -99999.00,    
      3790.666667, -99999.00,    
      3613.333333, -99999.00,    
      3254.814814, -99999.00,    
      2946.666667, -99999.00,    
      -99999.0, -99999.00,    
    };
    const int flags[] = {
      0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1,
      1,
    };

    db.queryVals(queryNames, querySize);

    double data[querySize];

    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
      CPPUNIT_ASSERT_EQUAL(flags[iLoc], err);
      
      for (int iVal=0; iVal < querySize; ++iVal) {
	const double dataE = values[iLoc*querySize+iVal];
	if (fabs(dataE) > tolerance)
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, data[iVal]/dataE, tolerance);
	else
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(dataE, data[iVal], tolerance);
      } // for
    } // for
  } // all values

  { // subset values
    const int querySize = 1;
    const char* queryNames[] = { 
      "vs",
    };
    const double values[] = {
      3333.334131,
      2584.759474,
      2398.752778,
      3148.777736,
      2432.217302,
      3707.466394,
      2968.477965,
      4459.29424, 
      4459.29424, 
      4282.106907, 
      3998.100000, 
      3514.068087, 
      3011.300000, 
      -99999.0, 
    };
    const int flags[] = {
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0,
      1,
    };

    db.queryVals(queryNames, querySize);

    double data[querySize];

    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
      CPPUNIT_ASSERT_EQUAL(flags[iLoc], err);
      
      for (int iVal=0; iVal < querySize; ++iVal) {
	const double dataE = values[iLoc*querySize+iVal];
	if (fabs(dataE) > tolerance)
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, data[iVal]/dataE, tolerance);
	else
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(dataE, data[iVal], tolerance);
      } // for
    } // for
  } // all values

  db.close();
} // testQuery
#endif

// ----------------------------------------------------------------------
// Test calcDensity()
void
spatialdata::spatialdb::TestSCECCVMH::testCalcDensity(void)
{ // testCalcDensity
  const int size = 10;
  const double vp[] = {
    -99999.00,
    5540.545410,
    4384.126953,
    4142.553223,
    5226.578125,
    4181.372070,
    6351.574219,
    4932.721191,
    1480.0,
    1860.0,
  };
  const double densityE[] = {
    -99999.00,
    3126.848633,
    2741.375488,
    2660.851074,
    3022.192871,
    2673.790527,
    3397.191406,
    2924.240234,
    1000.0,
    2000.0,
  };

  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i) {
    const double density = SCECCVMH::_calcDensity(vp[i]);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,
				 density/densityE[i], tolerance);
  } // for
} // testCalcDensity

// ----------------------------------------------------------------------
// Test calcVs()
void
spatialdata::spatialdb::TestSCECCVMH::testCalcVs(void)
{ // testCalcVs
  const int size = 10;
  const double vp[] = {
    -99999.00,
    5540.545410,
    4384.126953,
    4142.553223,
    5226.578125,
    4181.372070,
    6351.574219,
    4932.721191,
    1480.0,
    1860.0,
  };
  const double vsE[] = {
    -99999.00,
    3323.004705,
    2584.759846,
    2398.752778,
    3148.777937,
    2432.217302,
    3707.466393753004,
    2968.477865,
    0.0,
    431.0344827586207,
  };

  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i) {
    const double vs = SCECCVMH::_calcVs(vp[i]);
    if (fabs(vsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,
				   vs/vsE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(vsE[i], vs, tolerance);
  } // for
} // testCalcVs


// End of file 
