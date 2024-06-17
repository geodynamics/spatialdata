# Component Implementations

## Coordinate systems

[`CSCart`](geocoords/CSCart.md)
: Cartesian coordinate system.

[`CSGeo`](geocoords/CSGeo.md)
: Geographic coordinate system supported by Proj.

[`CSGeoLocal`](geocoords/CSGeoLocal.md)
: Geographic coordinate system with local origin and rotation angle.

## Spatial databases

[`AnalyticDB`](spatialdb/AnalyticDB.md)
: Spatial database with values specified by analytical functions.

[`UniformDB`](spatialdb/UniformDB.md)
: Spatial database with uniform values (no spatial variation).

[`SimpleDB`](spatialdb/SimpleDB.md)
: Spatial database with arbitrarily distributed points.

[`SimpleGridDB`](spatialdb/SimpleGridDB.md)
: Spatial database with points on a logically rectangular grid aligned with the coordinate axes.

[`CompositeDB`](spatialdb/CompositeDB.md)
: Spatial database comprised of two spatial databases.

[`UserFunctionDB`](spatialdb/UserFunctionDB.md)
: Spatial database with values specified by a C/C++ function (used in MMS tests).

[`GravityField`](spatialdb/GravityField.md)
: Special spatial database implementation for a gravity field.

## Temporal databasses

[`TimeHistory`](spatialdb/TimeHistory.md)
: User-specified time history using a file.

## Nondimensionalization

[`NondimElasticQuasistatic`](units/NondimElasticQuasistatic.md)
: Nondimensional length scales in terms of quasistatic parameters.

[`NondimElasticDynamic`](units/NondimElasticDynamic.md)
: Nondimensional length scales in terms of dynamic parameters.
