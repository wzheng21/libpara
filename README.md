# libpara
## Introduction
This library starts as the personal interest in practicing things learned
from daily work or reading books on C++. The focus is on providing useful
interfaces that can be reused in parallel, which is how the name came: lib(rary)para(llel)

There are several main goals for this library eventually to lead to:
* Support advanced threading features in old CXX standard (e.g. scoped lock in CXX11)
* Support processing and interesting derivatives out of it
* Support algorithms that are built upon previous bullets

## Prerequisites
cmake (>=3.10.0 && <= 3.19.0) is used to build the code.

We will tend to support cxx11/14/17 at the same time. But for now, at least
14 is required to compile tests

If `BUILD_TESTS` option is turned on (`ON` by default), user is required
to have googletest preinstalled and searchable by CMake.

## Platforms
With limited amount of spare time and equipment, this library is only tested
on Ubuntu 20.04 through WSL2 on Windows. It should work on native Ubuntu as
well.
