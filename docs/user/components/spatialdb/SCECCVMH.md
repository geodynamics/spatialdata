# SCECCVMH

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.SCECCVMH`

Spatial database for the SCEC CVM-H seismic velocity model versions 5.2 and 5.3.

Implements `SpatialDB`.

:::{danger}
These models are obsolete and no longer available from SCEC.
:::

## Pyre Properties

* `data_dir`=\<str\>: Directory containing SCEC CVM-H data files.
  - **default value**: '.'
  - **current value**: '.', from {default}
* `description`=\<str\>: Descriptive description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x11c2979d0>
* `label`=\<str\>: Descriptive label for seismic velocity model.
  - **default value**: 'SCEC CVM-H'
  - **current value**: 'SCEC CVM-H', from {default}
* `min_vs`=\<dimensional\>: Minimum shear wave speed.
  - **default value**: 500*m*s**-1
  - **current value**: 500*m*s**-1, from {default}
* `squash`=\<bool\>: Squash topography/bathymetry to sea level.
  - **default value**: False
  - **current value**: False, from {default}
* `squash_limit`=\<dimensional\>: Elevation above which topography is squashed.
  - **default value**: -2000*m
  - **current value**: -2000*m, from {default}

## Example

Example of setting `SCECCVMH` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
label = SCEC CVM-H v5.3
data_dir = data/scec-cvmh
min_vs = 500.0*m/s
squash = False
squash_limit = -20.0*km
:::

