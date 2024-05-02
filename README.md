## Introduction

*How and when to use*

*Template not required, just an example*

### Getting Started

First, you need to make a copy of this repository. You can either fork it and continue from there, or change the remote later.
Either way, first clone the repository. Assuming you are using a version of git newer or equal to `2.13`, you can use the following command:
```sh
git clone --recurse-submodules -j8 [url]
```
Insert the clone url at `url`, removing the square brackets `[]`.
From there you can test for compilation using the *(TODO)* compile script, or manually using the appropriate CMake commands found below. *(TODO: system dependend, link to setup scripts for environments)*
```sh
cmake -S . -B build
cmake --build build
```
The compiled executable can be found under `build/my_game`, adjust ending and path-separators depending on your system.
