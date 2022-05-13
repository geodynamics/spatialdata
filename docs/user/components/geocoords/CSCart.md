# CSCart

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.geocoords.CSCart`
:Journal name: `cscart`

Python manager for Cartesian coordinate systems.

Implements `CoordSys`.

## Pyre Properties

* `space_dim`=\<int\>: Number of dimensions for coordinate system.
  - **default value**: 3
  - **current value**: 3, from {default}
* `units`=\<str\>: Units of coordinates.
  - **default value**: 'm'
  - **current value**: 'm', from {default}

## Example

Example of setting `CSCart` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[coordsys]
units = meter
space_dim = 3
:::

