# CSGeo

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.geocoords.CSGeo`

Python manager for geographic coordinate systems.

Implements `CoordSys`.

## Pyre Properties

* `crs_string`=\<str\>: String specifying coordinate system (PROJ parameters, EPSG, or WKT). Default is WGS84.
  - **default value**: 'EPSG:4326'
  - **current value**: 'EPSG:4326', from {default}
* `space_dim`=\<int\>: Number of dimensions for coordinate system.
  - **default value**: 3
  - **current value**: 3, from {default}

## Example

Example of setting `CSGeo` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[coordsys]
# WGS84 (latitude, longitude) coordinate system
crs_string = EPSG:4326
space_dim = 2
:::

