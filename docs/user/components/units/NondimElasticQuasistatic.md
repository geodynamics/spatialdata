# NondimElasticQuasistatic

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.units.NondimElasticQuasistatic`

Convenience object for nondimensionalizing quasi-static elasticity problems.

Implements `Nondimensional`.

## Pyre Properties

* `length_scale`=\<dimensional\>: Value to nondimensionalize length scale.
  - **default value**: 1000*m
  - **current value**: 1000*m, from {default}
  - **validator**: (greater than 0*m)
* `relaxation_time`=\<dimensional\>: Relaxation time to nondimensionalize time.
  - **default value**: 3.15576e+09*s
  - **current value**: 3.15576e+09*s, from {default}
  - **validator**: (greater than 0*s)
* `shear_modulus`=\<dimensional\>: Shear modulus to nondimensionalize pressure.
  - **default value**: 3e+10*m**-1*kg*s**-2
  - **current value**: 3e+10*m**-1*kg*s**-2, from {default}
  - **validator**: (greater than 0*m**-1*kg*s**-2)

## Example

Example of setting `NondimElasticQuasistatic` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[normalizer]
length_scale = 5.0*km
shear_modulus = 30.0*GPa
relaxation_time = 200.0*year
:::

