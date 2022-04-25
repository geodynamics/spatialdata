# Time History Database

Inevitably you will want to specify both a spatial and temporal variation in values.
We currently decouple the two and provide a simple time history database to describe temporal variations.
The `TimeHistoryDB` uses a data file to specify an amplitude as a function of time.
Currently, only a single scalar amplitude can be specified.

Linear interpolation is used to determine the amplitude for times in between points in the database.
This means that the time history database must span the range of time values of interest.
The points in the time history must also be ordered in time.
If a query request the amplitude at a time beyond the last point in the database, then the amplitude for the last point will be used.

The file format is described in {ref}`sec-file-formats-TimeHistoryDB`.

:::{admonition} Pyre User Interface
See [TimeHistory component](../components/spatialdb/TimeHistory.md).
:::

## Examples

We specify a time history with time stamps in years.
The amplitude is nondimensional.
You can create a `TimeHistoryDB` data file manually in a text editor or generate the file using a Python script.
In most cases, using a Python script is easier because you do not have to worry about the format of the file.

::::{tab-set}

:::{tab-item} Time History File

```{code-block} c++
#TIME HISTORY ascii
TimeHistory {
  num-points =     11
  time-units = year
}
  0.000000e+00  1.000000e+00
  1.000000e+00  1.353353e-01
  2.000000e+00  1.831564e-02
  3.000000e+00  2.478752e-03
  4.000000e+00  3.354626e-04
  5.000000e+00  4.539993e-05
  6.000000e+00  6.144212e-06
  7.000000e+00  8.315287e-07
  8.000000e+00  1.125352e-07
  9.000000e+00  1.522998e-08
  1.000000e+01  2.061154e-09
```

:::

:::{tab-item} Python

```{code-block} python
---
caption: Creating a `TimeHistoryDB` file using Python.
---
import numpy

times = numpy.arange(0.0, 10.1, 1.0)
amplitude = numpy.exp(-2.0*times, dtype=numpy.float64)

from spatialdata.spatialdb.TimeHistoryIO import write
write(times, amplitude, "year", "amplitude.timedb")
```

:::

::::
