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

/** @file pkgs/geocoords/lib/proj4fwd.h
 *
 * @brief Forward declarations for proj4 API.
 */

#if !defined(spatialdata_proj4fwd_h)
#define spatialdata_proj4fwd_h

#if !defined(PROJECTS_H)
typedef void *projPJ;
#else
typedef PJ *projPJ;
#endif

#endif // spatialdata_proj4fwd_h

