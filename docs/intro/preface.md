# Preface

## Conventions

:::{warning}
This is a warning.
:::

:::{important}
This is something important.
:::

:::{tip}
This is a tip, helpful hint, or suggestion.
:::

For features recently added to SpatialData, we show the version number when they
were added.

:::{info}
New in v2.8.0.
:::

### Command Line Arguments

Example of a command line argument: `--help`.

### Filenames and Directories

Example of filenames and directories: `spatialdata`, `/usr/local`.

### Unix Shell Commands

Commands entered into a Unix shell (i.e., terminal) are shown in a box.
Comments are delimited by the # character. We use `$` to indicate the bash shell prompt.

```{code-block} bash
#This is a comment.
$ ls -l
```

### Excerpts of cfg Files

Example of an excerpt from a `.cfg` file:

```{code-block} cfg
# This is a comment.
[pylithapp.problem]
timestep = 2.0*s
bc = [x_pos, x_neg]
```

## Support

SpatialData development is supported by the CIG and U.S. Geological Survey <https://www.usgs.gov/> funding.
Pyre development was funded by the Department of Energy's <https://www.energy.gov/energygov> Advanced Simulation and Computing program and the National Science Foundation's Information Technology Research (ITR) program.

This material is based upon work supported by the National Science Foundation under Grants No. 0313238, 0745391, 1150901, and EAR-1550901.
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

%## Acknowledgments

## Request for Comments

Your suggestions and corrections can only improve this documentation.
Please report any errors, inaccuracies, or typos to the PyLith section of the CIG Community Forum <https://community.geodynamics.org/c/pylith> or create a GitHub pull request.
