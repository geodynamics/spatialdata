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

/** @file modulesrc/spatialdb/SimpleGridAscii.i
 *
 * @brief SWIG interface to C++ SimpleGridAscii object.
 */

namespace spatialdata {
  namespace spatialdb {

    class spatialdata::spatialdb::SimpleGridAscii
    { // SimpleGridAscii
      
    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      // Using default constructor.
      
      // Using default destructor.
      
      // Using default copy constructor
      
      /** Read the database.
       *
       * @param db Spatial database.
       */
      static
      void read(SimpleGridDB* db);
      
      /** Write the database.
       *
       * @param db Spatial database.
       */
      static
      void write(const SimpleGridDB& db);

    }; // class SimpleGridAscii

  } // spatialdb
} // spatialdata
  

// End of file 
