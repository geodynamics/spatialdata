# SimpleDB

In most cases we set the default type of spatial database to `SimpleDB`.
It is very flexible and can represent spatial variations from uniform properties with a single point to arbitrarily complex with irregularly spaced points.
This spatial database does not associate any topology with the points.
Although multiple values can be specified at each point with more than one value included in a search query, the interpolation of each value will be done independently.

A `SimpleDB` can specify spatial variations over zero, one, two, and three dimensions.
Zero dimensional (data dimension is 0) variations correspond to uniform values.
One-dimensional spatial variations (data dimension is 1) correspond to piece-wise linear variations, which need not coincide with coordinate axes.
Likewise, two-dimensional spatial variations (data dimension is 2) correspond to variations on a planar surface (which need not coincide with the coordinate axes).
Three-dimensional spatial variations (data dimension is 3) correspond to variations over a volume.
In one, two, or three dimensions, queries can use a ``nearest value'' search or linear interpolation.

`SimpleDB` uses a simple ASCII file to specify the variation of values in space.
The file format is described in {ref}`sec-file-formats-SimpleIOAscii`.

:::{admonition} Pyre User Interface
See [SimpleDB component](../components/spatialdb/SimpleDB.db) and [SimpleIOAscii component](../components/spatialdb/SimpleIOAscii.db).
:::

## Examples

We create a piece-wise linear variation in density along the y coordinate axis using 4 irregularly spaced points from 0.0 to -100.0.
You can create a `SimpleDB` data file manually in a text editor or generate the file using a Python script.
In most cases, using a Python script is easier because you do not have to worry about the format of the file.

::::{tab-set}

:::{tab-item} SimpleDB file

```{code-block} c++
#SPATIAL.ascii 1
SimpleDB {
  // Number of fields specified in the spatial database.  
  num-values =      1
  value-names =  density
  value-units =  kg/m**3

  // Number of locations where values are specified.
  num-locs =      4

  // Topology of the locations
  // 0: 1 point
  // 1: points on a line
  // 2: points on a surface
  // 3: points in a volume
  data-dim =    1

  // Spatial dimension
  space-dim =    2

  // Coordinate system for the points
  cs-data = cartesian {
    to-meters = 1
    space-dim = 2
  }
}
  0.000000e+00  0.000000e+00  2.500000e+03
  0.000000e+00 -1.000000e+01  2.550000e+03
  0.000000e+00 -4.000000e+01  2.800000e+03
  0.000000e+00 -1.000000e+02  3.000000e+03
```

:::

:::{tab-item} Python

```{code-block} python
import numpy

from spatialdata.spatialdb.SimpleIOAscii import createWriter
from spatialdata.geocoords.CSCart import CSCart

# Create a 2D Cartesian coordinate system.
cs = CSCart()
cs.spaceDim = 2
cs._configure()

# Create the coordinates of the points defining the spatial variation.
# Because the variation is along the y-direction, we use x=0.0 for simplicity.
points = numpy.array([
    [0.0, 0.0],
    [0.0, -10.0]
    [0.0, -40.0],
    [0.0, -100.0],
    ])
density = numpy.array([2500.0, 2550.0, 2800.0, 3000.0])

# Create a dictionary containing the data to write to the `SimpleDB` data file.
data = {
    "points": points,
    "coordsys": cs,
    "data_dim": 1,
    "values": [{
        "name": "density",
        "units": "kg/m**3",
        "data": density,
    }]
}

# Create the writer object and write the data file.
writer = createWriter("density.spatialdb")
writer.write(data)
```

:::

::::