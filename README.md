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
* procedural and custom texture
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

### Procedural and Custom Texture
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/texture.ppm?token=AFg7pVeGzE6vHhxvi03-9AaBNGDHQwH1ks5Y7I-fwA%3D%3D)

### Transparency
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/transparency.ppm?token=AFg7pUHTkBg7N22VosFDAC0Y5MFnflzjks5Y7I-4wA%3D%3D)

### Refraction
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/refraction.ppm?token=AFg7pdFSghDaS4idWkg84B3numM0SBF0ks5Y7I_rwA%3D%3D)

### Polygon Mesh

### Color Bleeding
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/sphere-bleeding.ppm?token=AFg7pd2abVu7wHlKdqByo2bsp_M4Tkojks5Y7MypwA%3D%3D)
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/plane-bleeding.ppm?token=AFg7pV0NBXy56X2V50p7Hu5JTJ-t11MHks5Y7MyvwA%3D%3D)

