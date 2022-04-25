# UserFunctionDB

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.UserFunctionDB`

Analytical function spatial database.
The analytical function must be provided in C++.
This spatial database is intended for use in tests using the Method of Manufactured Solutions.

Implements `SpatialDB`.

## Pyre Facilities

* `coordsys`: Coordinate system.
  - **current value**: 'cscart', from {default}
  - **configurable as**: cscart, coordsys

## Pyre Properties

* `description`=\<str\>: Descriptive description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x11c2979d0>

## Example

Example of setting `UserFunctionDB` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[db]
label = Linear function
cs = spatialdata.geocoords.CSCart
cs.space_dim = 2
:::

