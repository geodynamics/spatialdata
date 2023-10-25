# GravityField

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.GravityField`
:Journal name: `gravityfield`

Spatial database with gravity field information.

Implements `SpatialDB`. 

## Pyre Properties

* `acceleration`=\<dimensional\>: Gravitational acceleration.
  - **default value**: 9.80665*m*s**-2
  - **current value**: 9.80665*m*s**-2, from {default}
* `description`=\<str\>: Description for database.
  - **default value**: ''
  - **current value**: 'Gravity field', from {file='/Users/baagaard/software/unix/py310-venv/pylith-debug/lib/python3.10/site-packages/pythia/pyre/inventory/ConfigurableClass.py', line=26, function='__set__'}
  - **validator**: <function validateDescription at 0x102e94dc0>
* `gravity_dir`=\<list\>: Direction of gravitational body force. (used only with a Cartesian coordinate system.
  - **default value**: [0.0, 0.0, -1.0]
  - **current value**: [0.0, 0.0, -1.0], from {default}

## Example

Example of setting `GravityField` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
# Specify a gravity field in 2D with gravity in the -y direction.
[gravity_field]
gravity_dir = [0, -1]
acceleration = 9.80665*meter/second**2
:::

