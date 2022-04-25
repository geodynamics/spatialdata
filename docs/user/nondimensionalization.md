# Nondimensionalization

Nondimensionalization allows solving a system equations across a vast range of scales.
We primary use SpatialData for elasticity boundary value problems, so we define length, prssure, time, density, and temperature scales.

## Nondimensional

The `Nondimensional` object sets scales used to nondimensionalize values.
The density scale is not independent of the length, pressure, and time scales.
In most cases it is computed from those scales.
For wave propagation boundary values problems it is more convenient to specify the velocity, time, and density scales, and compute the length and pressure scales.

In the following discussion, we will use $S_\mathit{scale}$ to denote the scale, where scale can be length, pressure, time, density, or temperature.
\begin{gather}
S_\mathit{density} = \frac{S_\mathit{pressure} S_\mathit{time}^2}{S_\mathit{length}^2} \\
S_\mathit{pressure} = \frac{S_\mathit{density} S_\mathit{length}^2}{S_\mathit{time}^2}
\end{gather}

:::{tip}
The default nondimensionalization is reasonable for many problems; however, it may be necessary to change the default values in some cases.
When doing so, keep in mind that the nondimensionalization generally applies to the minimum values
encountered for a problem.
For example, in a quasistatic elaticity boundary value problem, the `length_scale` should be on the order of the minimum cell size.
Similarly, the `relaxation_time` should be on the order of the minimum relaxation time or time scale associated with time-dependent boundary and interface conditions.
:::

## NondimensionalQuasistatic

`NondimensionalQuasistatic` provides convenient scales for nondimensionalizing quasistatic elasticity boundary values problems.
The scales are specified in terms of the length scale of deformation, shear modulus, and relaxation time.

:::{note}
The density scale will be very large in quasistatic problems, consistent with inertia not being important.
:::

```{table} Nondimensional scales for quasistatic elasticity boundary value problems.
:name: tab:nondimensional:quasistatic:scales
| Scale | Name | Default Value |
| :---: | :--: | :-----------: |
| length | length_scale | 1.0 km |
| pressure | shear_modulus | 30 GPa |
| time | relaxation_time | 100 years |
```

:::{admonition} Pyre User Interface
See [NondimensionalQuasistatic component](components/units/NondimensionalQuasistatic.md).
:::

## NondimensionalDynamic

`NondimensionalDynamic` provides convenient scales for nondimensionalizing quasistatic elasticity boundary values problems.
The scales are specified in terms of the minimum shear wave speed, minimum density, and minimum wave period.

```{table} Nondimensional scales for dynamic elasticity boundary value problems.
:name: tab:nondimensional:dynamic:scales
| Scale | Name | Default Value |
| :---: | :--: | :-----------: |
| velocity | shear_wave_speed | 3.0 km/s |
| density | mass_density | 3000 kg/m$^3$ |
| time | wave_period | 1.0 s |
```

:::{admonition} Pyre User Interface
See [NondimensionalDynamic component](components/units/NondimensionalDynamic.md).
:::
