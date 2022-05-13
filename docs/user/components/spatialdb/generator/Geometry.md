# Geometry

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.generator.Geometry`
:Journal name: `geometry`

Geometry used in generating database.

## Pyre Facilities

* `coordsys`: Coordinate system for database.
  - **current value**: 'cscart', from {default}
  - **configurable as**: cscart, coordsys
* `reader`: Object to read geometry.
  - **current value**: 'dummy', from {default}
  - **configurable as**: dummy, reader

## Pyre Properties

* `data_dim`=\<int\>: Spatial dimension of database locations.
  - **default value**: 2
  - **current value**: 2, from {default}
  - **validator**: (in [0, 1, 2, 3])

## Example

Example of setting `Geometry` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[gensimplebd.geometry]
data_dim = 2
reader = read_geometry
coordsys = spatialdata.geocoords.CSCart
:::

