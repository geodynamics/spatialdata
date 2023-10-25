# CSGeoLocal

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.geocoords.CSGeoLocal`
:Journal name: `csgeoLocal`

Python manager for local, rotated geographic coordinate systems.

Implements `CSGeo`.

## Pyre Properties

* `crs_string`=\<str\>: String specifying coordinate system (PROJ parameters, EPSG, or WKT). Default is WGS84.
  - **default value**: 'EPSG:4326'
  - **current value**: 'EPSG:4326', from {default}
* `origin_x`=\<float\>: X coordinate of local origin.
  - **default value**: 0.0
  - **current value**: 0.0, from {default}
* `origin_y`=\<float\>: Y coordinate of local origin.
  - **default value**: 0.0
  - **current value**: 0.0, from {default}
* `space_dim`=\<int\>: Number of dimensions for coordinate system.
  - **default value**: 3
  - **current value**: 3, from {default}
* `y_azimuth`=\<float\>: Azimuth (degrees) of local y axis.
  - **default value**: 0.0
  - **current value**: 0.0, from {default}

## Example

Example of setting `CSGeoLocal` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[coordsys]
# Local, rotated UTM Zone 10 coordinate system
crs_string = EPSG:29610
space_dim = 2
origin_x = 300000.0
origin_y = 4000000.0
y_azimuth = -25.0
:::

