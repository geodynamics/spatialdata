c -*- Fortran -*-
c
c ======================================================================
c
c                           Brad T. Aagaard
c                        U.S. Geological Survey
c
c {LicenseText}
c
c ======================================================================
c

      function f77test_query(db, cs)
      implicit none

      integer f77test_query
      integer db
      integer cs

      integer numVals
      parameter(numVals=2)
      integer iVal

      real*8 tolerance
      parameter(tolerance=1.0E-06)

      real*8 loc(3)
      data loc/1.0, 2.0, 3.0/

      real*8 vals(numVals)
      data vals/6.3, 4.7/

      real*8 valsQ(numVals)

      integer err
      real*8 error

      err = 0
      call spatialdb_query_f(db, valsQ, numVals, loc(1), loc(2), 
     *     loc(3), cs)
      do iVal=1,numVals
         error = 1.0-valsQ(iVal)/vals(1+numVals-iVal)
         if (error .gt. tolerance) then
            err = 1
            goto 10
         endif
      enddo
 10   f77test_query = err
      return
      end

c version
c $Id: f77testspatialdb.f,v 1.1 2005/05/25 18:43:02 baagaard Exp $

c End of file 
