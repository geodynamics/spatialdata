# SimpleGridDB

The `SimpleGridDB` is very similar to the `SimpleDB` but the values must be provided at locations on a logically rectangular grid aligned with the coordinate axes.
The query algorithm leverages the topology of the grid, resulting in much more efficient queries compared to a `SimpleDB`.
The points do not need to be uniformly spaced along each coordinate direction.
The point values can be specified in any order, as well as over a lower dimension than the spatial dimension.
For example, one can specify a 2D grid in 3D space provided that the 2D grid is aligned with one of the coordinate axes.

`SimpleGridDB` uses a simple ASCII file to specify the variation of values in space.
The file format is described in {ref}`sec-file-formats-SimpleGridDB`.

:::{note}
You do not need to specify the data dimension when using a `SimpleGridDB`.
The `SimpleGriDB` will determine the layout of the data from the spatial dimension and array of coordinates along each axis.
:::

:::{admonition} Pyre User Interface
See [SimpleGridDB component](../components/spatialdb/SimpleGridDB.db).
:::

## Examples

We create a spatial database with three components of a displacement field over an xy surface in a UTM zone 10n geographic projection.
We use an analytical function for the displacement field, $\vec{u}$:
\begin{align}
u_x &= 2.0 + 4.0e-3*x \\
u_y &= 0.5 + 2.0e-3*y \\
u_z &= 1.0 + 3.0e-3*x - 1.0e-3*y
\end{align}
You can create a `SimpleGridDB` data file manually in a text editor or generate the file using a Python script.
In most cases, using a Python script is easier because you do not have to worry about the format of the file.

::::{tab-set}

:::{tab-item} SimpleGridDB file

```{code-block} c++
#SPATIAL_GRID.ascii 1
SimpleGridDB {
  num-x = 6
  num-y = 4
  num-z = 1
  space-dim = 3
  num-values = 3
  value-names =  displacement_x  displacement_y  displacement_z
  value-units =  m  m  m
  cs-data = geographic {
    crs-string = EPSG:32610
    space-dim = 3
  }
}
// x-coordinates
 -3.000000e+04 -2.000000e+04 -1.000000e+04  0.000000e+00  1.000000e+04  2.000000e+04
// y-coordinates
 -2.000000e+04 -1.000000e+04  0.000000e+00  1.000000e+04
// z-coordinates
  0.000000e+00
// data
 -3.000000e+04 -2.000000e+04  0.000000e+00 -1.180000e+02 -3.950000e+01 -6.900000e+01
 -2.000000e+04 -2.000000e+04  0.000000e+00 -7.800000e+01 -3.950000e+01 -3.900000e+01
 -1.000000e+04 -2.000000e+04  0.000000e+00 -3.800000e+01 -3.950000e+01 -9.000000e+00
  0.000000e+00 -2.000000e+04  0.000000e+00  2.000000e+00 -3.950000e+01  2.100000e+01
  1.000000e+04 -2.000000e+04  0.000000e+00  4.200000e+01 -3.950000e+01  5.100000e+01
  2.000000e+04 -2.000000e+04  0.000000e+00  8.200000e+01 -3.950000e+01  8.100000e+01
 -3.000000e+04 -1.000000e+04  0.000000e+00 -1.180000e+02 -1.950000e+01 -7.900000e+01
 -2.000000e+04 -1.000000e+04  0.000000e+00 -7.800000e+01 -1.950000e+01 -4.900000e+01
 -1.000000e+04 -1.000000e+04  0.000000e+00 -3.800000e+01 -1.950000e+01 -1.900000e+01
  0.000000e+00 -1.000000e+04  0.000000e+00  2.000000e+00 -1.950000e+01  1.100000e+01
  1.000000e+04 -1.000000e+04  0.000000e+00  4.200000e+01 -1.950000e+01  4.100000e+01
  2.000000e+04 -1.000000e+04  0.000000e+00  8.200000e+01 -1.950000e+01  7.100000e+01
 -3.000000e+04  0.000000e+00  0.000000e+00 -1.180000e+02  5.000000e-01 -8.900000e+01
 -2.000000e+04  0.000000e+00  0.000000e+00 -7.800000e+01  5.000000e-01 -5.900000e+01
 -1.000000e+04  0.000000e+00  0.000000e+00 -3.800000e+01  5.000000e-01 -2.900000e+01
  0.000000e+00  0.000000e+00  0.000000e+00  2.000000e+00  5.000000e-01  1.000000e+00
  1.000000e+04  0.000000e+00  0.000000e+00  4.200000e+01  5.000000e-01  3.100000e+01
  2.000000e+04  0.000000e+00  0.000000e+00  8.200000e+01  5.000000e-01  6.100000e+01
 -3.000000e+04  1.000000e+04  0.000000e+00 -1.180000e+02  2.050000e+01 -9.900000e+01
 -2.000000e+04  1.000000e+04  0.000000e+00 -7.800000e+01  2.050000e+01 -6.900000e+01
 -1.000000e+04  1.000000e+04  0.000000e+00 -3.800000e+01  2.050000e+01 -3.900000e+01
  0.000000e+00  1.000000e+04  0.000000e+00  2.000000e+00  2.050000e+01 -9.000000e+00
  1.000000e+04  1.000000e+04  0.000000e+00  4.200000e+01  2.050000e+01  2.100000e+01
  2.000000e+04  1.000000e+04  0.000000e+00  8.200000e+01  2.050000e+01  5.100000e+01
```

:::

:::{tab-item} Python

```{code-block} python
import numpy

from spatialdata.spatialdb.SimpleGridAscii import createWriter
from spatialdata.geocoords.CSGeo import CSGeo

# Create the UTM zone 10n (WGS84 datum) coordinate system.
# The corresponding EPSG code is 32610. See https://epsg.io/32610.
cs = CSGeo()
cs.crsString = "EPSG:32610"
cs._configure()

# Create the coordinates of the points defining the spatial variation.
dx = 10.0e+3 # 10 km resolution
x1 = numpy.arange(-30000.0, +20000.0+0.5*dx, dx)
y1 = numpy.arange(-20000.0, +10000.0+0.5*dx, dx)
z1 = numpy.array([0.0])
x,y,z = numpy.meshgrid(x1, y1, z1, indexing="ij")
points = numpy.stack((x.ravel(),y.ravel(),z.ravel())).transpose()
del x,y,z
displacement = numpy.zeros(points.shape, dtype=numpy.float64)
displacement[:,0] = 2.0 + 4.0e-3*points[:,0]
displacement[:,1] = 0.5 + 2.0e-3*points[:,1]
displacement[:,2] = 1.0 + 3.0e-3*points[:,0] - 1.0e-3*points[:,1]

# Create a dictionary containing the data to write to the `SimpleDB` data file.
data = {
    "points": points,
    "x": x1,
    "y": y1,
    "z": z1,
    "coordsys": cs,
    "data_dim": 2,
    "values": [
        {
        "name": "displacement_x",
        "units": "m",
        "data": displacement[:,0],
        },{
        "name": "displacement_y",
        "units": "m",
        "data": displacement[:,1],
        },{
        "name": "displacement_z",
        "units": "m",
        "data": displacement[:,2],
        },
    ]
}

# Create the writer object and write the data file.
writer = createWriter("displacement.spatialdb")
writer.write(data)
```

:::

::::
