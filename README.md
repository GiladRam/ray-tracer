# `ray-tracer`

## Introduction

`ray-tracer` is a multi-thread 3D rendering engine written in `C++`.

## Features
* multi-thread rendering
* read scene setting from a simple `.json` file
* [Phong reflection model](http://en.wikipedia.org/wiki/Phong_reflection_model) and [Monte Carlo path tracing model](http://en.wikipedia.org/wiki/Path_tracing)
* rendering of plane, sphere and polygon mesh
* read polygon mesh from a simple `.obj` file
* soft shadow (area lights)
* procedural texture
* mesh smoothing

## Usage

### Dependencies
* `CMake >= 3.5`

### Compile
```
mkdir bin/ && cd bin/
cmake .. && make all
```
## Examples

