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
 * @file libsrc/utils/SpatialdataVersion.hh
 *
 * @brief C++ object for Spatialdata version information.
 */

#if !defined(spatialdata_utils_spatialdataversion_hh)
#define spatialdata_utils_spatialdataversion_hh

// Include directives ---------------------------------------------------
#include "utilsfwd.hh" // forward declarations

// Version ----------------------------------------------------------
/** @brief C++ object for getting version info.
 */
class spatialdata::utils::SpatialdataVersion
{ // SpatialdataVersion
  friend class TestSpatialdataVersion; // unit testing

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
  bool isRelease(void);

  /** Get version number.
   *
   * @returns Version number.
   */
  static
  const char* version(void);

  /** Get GIT revision.
   *
   * @returns GIT revision.
   */
  static
  const char* gitRevision(void);

  /** Get GIT hash.
   *
   * @returns GIT hash.
   */
  static
  const char* gitHash(void);

  /** Get date of GIT revision.
   *
   * @returns Date of GIT revision.
   */
  static
  const char* gitDate(void);

  /** Get GIT branch.
   *
   * @returns GIT branch.
   */
  static
  const char* gitBranch(void);
  
  /** Get Proj.4 version number.
   *
   * @returns Version number.
   */
  static
  const char* projVersion(void);

// PRIVATE METHODS //////////////////////////////////////////////////////
private :

  SpatialdataVersion(const SpatialdataVersion&); ///< Not implemented
  const SpatialdataVersion& operator=(const SpatialdataVersion&); ///< Not implemented

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :

  static const bool _isRelease; ///< Is source code from a release?
  static const char* _version; ///< Version number.
  static const char* _gitRevision; ///< GIT revision.
  static const char* _gitDate; ///< Date of GIT revision.
  static const char* _gitHash; ///< GIT hash.
  static const char* _gitBranch; ///< GIT branch.

  static const char* _projVersion; ///< Proj.4 version number.

}; // SpatialdataVersion

#endif // spatialdata_utils_spatialdataversion_hh


// End of file 
