# SpatialData

SpatialData is a Python and C++ library for

* interpolating values for spatially distributed data,
* converting coordinates among geographic projections using [Proj](https://proj.maptools.org),
* nondimensionalization of quantities,
* specification of units via Pyre (optional).

This library is used in the finite-element code [PyLith](https://github.com/geodynamics/pylith).
The primary focus is specification of parameters that vary in space, such as values for boundary conditions and parameters of constitutive models.
This provides a specification of these parameters independent of the discretization.

## Dependencies

* GNU build tools w/C++ and C compilers
* [Proj](https://proj.maptools.org) cartographic projections library (v6.0 or later)
* [Optional] Pyre 1.0.0 and NumPy
* [Optional] Catch2 (for unit testing)

```{include} ../LICENSE.md
```

```{toctree}
---
caption: Table of Contents
hidden: True
---
intro/index.md
user/index.md
developer/index.md
```

