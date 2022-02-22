(sec-file-formats-SimpleIOAscii)=
# SimpleDB ASCII Format

`SimpleDB` spatial database files contain a header describing the set of points and then the data with each line listing the coordinates of a point followed by the values of the fields for that point.

```{code-block} c++
// This spatial database specifies the distribution of slip on the
// fault surface. In this case we prescribe a piecewise linear, 
// depth dependent distribution of slip. The slip is 2.0 m 
// right-lateral with 0.25 m of reverse slip at the surface with
// a linear taper from 2.0 m to 0.0 m from -2 km to -4 km.
//
// Comments can appear almost anywhere in these files and are
// delimited with two slashes (//) just like in C++. All text and 
// whitespace after the delimiter on a given line is ignored.
//
// The next line is the magic header for spatial database files 
// in ASCII format.
#SPATIAL.ascii 1
SimpleDB { // start specifying the database parameters
  num-values = 3 // number of values in the database

  // Specify the names and the order of the values as they appear 
  // in the data. The names of the values must correspond to the 
  // names PyLith requests in querying the database.
  value-names =  left-lateral-slip  reverse-slip  fault-opening

  // Specify the units of the values in Python syntax (e.g., kg/m**3).
  value-units =  m  m  m
  num-locs = 3 // Number of locations where values are given
  data-dim = 1 // Locations of data points form a line
  space-dim = 3 // Spatial dimension in which data resides

  // Specify the coordinate system associated with the 
  // coordinates of the locations where data is given
  cs-data = cartesian { // Use a Cartesian coordinate system
    to-meters = 1.0e+3 // Coordinates are in km

    // Specify the spatial dimension of the coordinate system
    // This value must match the one associated with the database
    space-dim = 3

  } // cs-data // end of coordinate system specification

} // end of SimpleDB parameters
// The locations and values are listed after the parameters.
// Columns are coordinates of the points (1 column for each 
// spatial dimension) followed by the data values in the order 
// specified by the value-names field.
0.0  0.0  0.0    -2.00  0.25  0.00
0.0  0.0 -2.0    -2.00  0.00  0.00
0.0  0.0 -4.0     0.00  0.00  0.00
```
