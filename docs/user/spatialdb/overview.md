# Overview

A spatial database defines how values for some field (scalar, vector, tensor) vary spatially, and they can be quite complex.
Temporal variations of a field are not supported.
In most cases, the fields must be continuous, but it is possible in some cases to specify a field that contains discontinuities.
The simplest case is a field with uniform values.
A slightly more complex case would be values that vary linearly along a given direction.
In more sophisticated models, the values might have vary in 2D or 3D.
This library implements a few different types of spatial databases, and we have created some special case spatial databases in external libraries.

The layout and source of the data dictate the type of spatial database used.
For example, a field with uniform values is most easily specified using a `UniformDB`.
A field defined by points on a logically rectangular grid in 1D, 2D, or 3D can be specified using a `SingleGridDB`.
If the points defining the values are not on a logically rectangular grid, then a `SimpleDB` can be used.
The `CompositeDB` type is used to combine values from two separate spatial databases into a single spatial database.

A spatial database does need not to provide the data using the same coordinate system as the one associated with the locations being queried, provided the two coordinate systems are compatible.
Examples of compatible coordinate systems include geographic coordinates (longitude/latitude/elevation), and projected coordinates (for example, coordinates in a transverse Mercator projection).
Spatial database queries use the [Proj Cartographic Projections library](https://proj.maptools.org) to convert between coordinate systems, so a large number of geographic projections are available with support for converting between NAD27 and WGS84 horizontal datums as well as several other frequently used datums.
Because the interpolation is done in the coordinate system of the spatial database, geographic coordinates should only be used for very simple datasets, or undesirable results will occur.
This is especially true when the spatial database coordinate system combines latitude, longitude, and elevation in meters; longitude and latitude in degrees are often much smaller than elevations in meters leading to distorted ``distance'' between locations and interpolation.
