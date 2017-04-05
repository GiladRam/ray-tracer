# `ray-tracer`

## Introduction

`ray-tracer` is a photo-realistic 3D rendering engine written in `C++`.

## Features
* multi-thread rendering
* accelerate using [k-dimensional tree](https://en.wikipedia.org/wiki/K-d_tree)
* read scene setting from a simple `.json` file
* [Phong reflection model](http://en.wikipedia.org/wiki/Phong_reflection_model) and [Monte Carlo path tracing model](http://en.wikipedia.org/wiki/Path_tracing)
* rendering of plane, sphere and polygon mesh
* read polygon mesh from a simple `.obj` file
* soft shadow (area lights)
* procedural and custom texture
* mesh smoothing

## Usage

### Dependencies
* `gcc >= 4.8`
* `cmake >= 3.5`

### Compile
```
mkdir bin/ && cd bin/
cmake .. && make all
```
## Examples

### Polygon Mesh
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/mesh.ppm?token=AFg7pV3xTZX2tQGvdtCeE8_Y_Sh5q2uwks5Y7XSnwA%3D%3D)

### Procedural and Custom Texture
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/texture.png?token=AFg7pU2Byriy1aq_iKS6rzPu3nj5hjdHks5Y7dcbwA%3D%3D)

### Transparency
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/transparency.png?token=AFg7pQbDaRErdzj_H-w_htaiA7k82zvhks5Y7deGwA%3D%3D)

### Refraction
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/refraction.png?token=AFg7pfgtsNps7IKnm01yuNhUW6A1SxsVks5Y7deKwA%3D%3D)

### Color Bleeding
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/sphere-bleeding.png?token=AFg7pfCouP7DkGDPfERG-Sk7LgATaI0Gks5Y7deLwA%3D%3D)
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/plane-bleeding.png?token=AFg7pT20KmuMc_LIJeiAvNxdEQy-AZ61ks5Y7deMwA%3D%3D)

