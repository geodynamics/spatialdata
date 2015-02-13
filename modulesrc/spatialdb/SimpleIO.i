// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/spatialdb/SimpleIO.i
 *
 * @brief SWIG interface to C++ SimpleIO object.
 */

namespace spatialdata {
  namespace spatialdb {
    class SimpleDBData; // forward declaration

    class SimpleIO
    { // class SimpleIO

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor.
      SimpleIO(void);
  
      /// Default destructor.
      virtual
      ~SimpleIO(void);

      /** Set filename for database.
       *
       * @param filename Filename of database
       */
      void filename(const char* filename);

      /** Get filename for database.
       *
       * @returns Filename of database
       */
      const char* filename(void) const;

      /** Read the database.
       *
       * @param pData Database data
       * @param ppCS Pointer to coordinate system
       */
      virtual
      void read(SimpleDBData* pData,
		spatialdata::geocoords::CoordSys** ppCS) = 0;

      /** Write the database.
       *
       * @param data Database data
       * @param pCS Pointer to coordinate system
       */
      virtual
      void write(const SimpleDBData& data,
		 const spatialdata::geocoords::CoordSys* pCS) = 0;

    }; // class SimpleIO

  } // namespace spatialdb
} // namespace spatialdata


// End of file 
