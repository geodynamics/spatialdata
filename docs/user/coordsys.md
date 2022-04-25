# Coordinate Systems

SpatialData provides two types of coordinate systems: Cartesian (`CSCart`) and georeferenced (`CSGeo`).
The coordinate systems can be specified 

## CSCart

`CSCart` provides 1D, 2D, and 3D Cartesian coordinate systems.

:::{admonition} Pyre User Interface
See [CSCart component](components/geocoords/CSCart.md).
:::

### Examples

We specify a 2D coordinate system with the coordinates given in meters.

::::{tab-set}

:::{tab-item} Spatial database file

```{code-block} c++
---
caption: Specifying a `CSCart` in a spatial database file.
---
cs-data = cartesian {
    to-meters = 1000.0
    space-dim = 2
}
```

:::

:::{tab-item} C++

```{code-block} c++
---
caption: Create a `CSCart` object in C++.
---
#include "spatialdata/geocoords/CSCart.hh"

spatialdata::geocoords:CSCart cs;
cs.setToMeters(1000.0);
cs.setSpaceDim(2);
```
:::

:::{tab-item} Python

```{code-block} python
---
caption: Create a `CSCart` object in Python.
---
from spatialdata.geocoords.CSCart import CSCart

cs = CSCart()
cs.units = "km"
cs.spaceDim = 2
cs._configure()
```

:::

::::

## CSGeo

`CSGeo` provides 2D and 3D georeferenced coordinate systems.
We use [Proj](https://proj.maptools.org) to perform coordinate system operations, so any coordinate system supported by Proj can be used.
The coordinate systems can be specified using [EPSG codes](https://epsg.io), Well-Known Text (WKT), or Proj parameters.
See the [Proj documentation](https://proj.org/development/reference/functions.html#c.proj_create) for more information.

```{table} Frequently used EPSG codes.
:name: tab:common:epsg:codes
| EPSG Code | Description |
| :-------: | :---------- |
| [EPSG:4326](https://epsg.io/4326) | WGS84 (latitude, longitude) |
| [EPSG:4269](https://epsg.io/4269) | NAD83 (latitude, longitude) |
| [EPSG:4267](https://epsg.io/4267) | NAD27 (latitude, longitude) |
| [EPSG:32610](https://epsg.io/32610)[^utm] | UTM Zone 10N WGS84 datum (easting, northing) |
| [EPSG:26910](https://epsg.io/26910)[^utm] | UTM Zone 10N NAD83 datum (easting, northing) |
| [EPSG:26710](https://epsg.io/26710)[^utm] | UTM Zone 10N NAD27 datum (easting, northing) |
```

[^utm]: EPSG codes for Universal Transverse Mercator (UTM) zones are numbered consecutively.
For example, in the WGS84 datum EPSG:32501 is UTM Zone 1S, EPSG:32560 is UTM Zone 60S, EPSG:32601 is UTM Zone 1N, and EPSG:32660 is UTM Zone 60N.

:::{important}
Georeferencing has become much more accurate since the availability of the Global Positional System and its successors.
As a result, geographic coordinate systems or Coordinate Reference Systems (CRS) have become more complicated.
Traditional Proj parameters (used exclusively in Proj versions 5.0 and earlier) do not provide complete specification of a CRS; specifying CRS using EPSG codes or WKT are preferable to using Proj parameters.
:::

:::{admonition} Pyre User Interface
See [CSGeo component](components/geocoords/CSGeo.md).
:::

### Examples

We create a 3D georeferenced coordinate system corresponding to UTM Zone 10N with the WGS84 datum (EPSG:32610).

::::{tab-set}

:::{tab-item} Spatial database file

```{code-block} c++
---
caption: Specifying a `CSGeo` in a spatial database file.
---
cs-data = geographic {
    crs-string = EPSG:32610
    space-dim = 3
}
```

:::

:::{tab-item} C++

```{code-block} c++
---
caption: Create a `CSGeo` object in C++.
---
#include "spatialdata/geocoords/CSGeo.hh"

spatialdata::geocoords:CSGeo cs;
cs.setString("EPSG:32610");
cs.setSpaceDim(3);
```

:::

:::{tab-item} Python

```{code-block} python
---
caption: Create a `CSGeo` object in Python.
---
from spatialdata.geocoords.CSGeo import CSGeo

cs = CSGeo()
cs.crsString = "EPSG:32610"
cs.spaceDim = 3
cs._configure()
```

:::

::::

## Converting between coordinate systems

We convert from 34.5N 118.0W in the WGS84 datum (EPSG:4326) to UTM Zone 10N in the NAD27 datum.

### Examples

::::{tab-set}

:::{tab-item} Command line

```{code-block} console
---
caption: Using the Proj `cs2cs` command line tool to convert between coordinate systems.
---
$ echo "37.5 -121.0" | cs2cs EPSG:4326 EPSG:26710 -f "%.1f"
676885.9        4152025.1 0.0
```

:::

:::{tab-item} C++

The points are converted in place (array values are changed).

```{code-block} c++
#include "spatialdata/geocoords/CSGeo.hh"
#include "spatialdata/geocoords/Converter.hh"

const size_t numPoints = 1;
const size_t spaceDim = 2;
const double points[numPoints*spaceDim] = { 37.5, -121.0 };

spatialdata::geocoords::CSGeo csSrc;
csSrc.setString("EPSG:4326");
csSrc.setSpaceDim(spaceDim);

spatialdata::geocoords::CSGeo csDest;
csSrc.setString("EPSG:26710");
csSrc.setSpaceDim(spaceDim);

spatialdata::geocoords::Converter converter;
converter.convert(points, numPoints, spaceDim, &csDest, &csSrc);
```

:::

:::{tab-item} Python

The points are converted in place (array values are changed).

```{code-block} python
import numpy

from spatialdata.geocoords.CSGeo import CSGeo
from spatialdata.geocoords.Converter import convert

csSrc = CSGeo()
csSrc.crsString = "EPSG:4326"
csSrc.spaceDim = 2
csSrc._configure()

csDest = CSGeo()
csDest.crsString = "EPSG:26710"
csDest.spaceDim = 2
csDest._configure()

points = numpy.array([[37.5, -121.0]], dtype=numpy.float64)
convert(points, csDest, csSrc)
```

:::

::::