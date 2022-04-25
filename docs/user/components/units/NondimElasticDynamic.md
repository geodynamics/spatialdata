# NondimElasticDynamic

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.units.NondimElasticDynamic`

Convenience object for nondimensionalizing dynamic elasticity problems.

Implements `Nondimensional`.

## Pyre Properties

* `mass_density`=\<dimensional\>: Mass density to nondimensionalize problem
  - **default value**: 3000*m**-3*kg
  - **current value**: 3000*m**-3*kg, from {default}
  - **validator**: (greater than 0*m**-3*kg)
* `shear_wave_speed`=\<dimensional\>: Shear wave speed to nondimensionalize problem.
  - **default value**: 3000*m*s**-1
  - **current value**: 3000*m*s**-1, from {default}
  - **validator**: (greater than 0*m*s**-1)
* `wave_period`=\<dimensional\>: Period of wave to nondimensionalize problem.
  - **default value**: 1*s
  - **current value**: 1*s, from {default}
  - **validator**: (greater than 0*s)

## Example

Example of setting `NondimElasticDynamic` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[normalizer]
shear_wave_speed = 3.0*km/s
mass_density = 3.0*kg/m**3
wave_period = 2.0*s
:::

