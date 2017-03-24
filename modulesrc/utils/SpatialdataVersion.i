// -*- C++ -*-
//
// ======================================================================
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

/**
 * @file modulesrc/utils/SpatialdataVersion.i
 *
 * @brief C++ object for Spatialdata version information.
 */

namespace spatialdata {
  namespace utils {

    class SpatialdataVersion
    { // SpatialdataVersion

      // PUBLIC MEMBERS ///////////////////////////////////////////////////////
    public :

      /// Default constructor.
      SpatialdataVersion(void);
      
      /// Default destrictor.
      ~SpatialdataVersion(void);
      
      /** Is source from a release?
       *
       * @returns True if source code comes from a release?
       */
      static
      bool isRelease(void) const;
      
      /** Get version number.
       *
       * @returns Version number.
       */
      static
      const char* version(void) const;
      
      /** Get GIT revision.
       *
       * @returns GIT revision.
       */
      static
      const char* gitRevision(void) const;
      
      /** Get GIT hash.
       *
       * @returns GIT hash.
       */
      static
      const char* gitHash(void) const;
      
      /** Get date of GIT revision.
       *
       * @returns Date of GIT revision.
       */
      static
      const char* gitDate(void) const;
      
      /** Get GIT branch.
       *
       * @returns GIT branch.
       */
      static
      const char* gitBranch(void) const;
      
      /** Get Proj.4 version number.
       *
       * @returns Version number.
       */
      static
      const char* projVersion(void);
      
    }; // SpatialdataVersion
    
  } // utils
} // spatialdata

// End of file 
