# `ray-tracer`

## Introduction

`ray-tracer` is a photo-realistic 3D rendering engine written in `C++`.

## Features
* multi-thread rendering
* acceleration with [k-dimensional tree](https://en.wikipedia.org/wiki/K-d_tree)
* read scene setting from a simple `.json` file
* rendering of plane, sphere and polygon mesh
* read polygon mesh from a simple `.obj` file
* soft shadow (area lights)
* procedural and custom texture
* mesh smoothing

## Usage

### Requirements
* `Unix / Linux`
* `GCC / G++ 4.8+`
* `CMake 3.5+`

### Compile
```
mkdir bin/ && cd bin/
cmake .. && make all
```

### Render
```
./ray-tracer <input-scene-path> <output-image-path>
```

For example, in order to render `texture.json`, you may use the following instruction:

```
./ray-tracer ../scenes/texture.json ../images/texture.png
```

## Examples

### Polygon Mesh
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/mesh.png?token=AFg7pXpXn6uAR-L5a7T5GReCxJ6ye3izks5Y7feVwA%3D%3D)

### Procedural and Custom Texture
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/texture.png?token=AFg7pU2Byriy1aq_iKS6rzPu3nj5hjdHks5Y7dcbwA%3D%3D)

### Transparency
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/transparency.png?token=AFg7pQbDaRErdzj_H-w_htaiA7k82zvhks5Y7deGwA%3D%3D)

### Refraction
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/refraction.png?token=AFg7pfgtsNps7IKnm01yuNhUW6A1SxsVks5Y7deKwA%3D%3D)

### Color Bleeding
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/sphere-bleeding.png?token=AFg7pfCouP7DkGDPfERG-Sk7LgATaI0Gks5Y7deLwA%3D%3D)
![](https://raw.githubusercontent.com/zhijian-liu/ray-tracer/master/images/plane-bleeding.png?token=AFg7pT20KmuMc_LIJeiAvNxdEQy-AZ61ks5Y7deMwA%3D%3D)

## References
* [Scratchapixel -- Learn Computer Graphics from Scratch](https://www.scratchapixel.com)
* [Flipcode -- Raytracing Topics and Techniques](http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_1_Introduction.shtml)
* [Yuxin Wu's Repository -- Ray Tracing Engine](https://github.com/ppwwyyxx/Ray-Tracing-Engine)

## Acknowledgements
This project is built with [`json`](https://github.com/nlohmann/json), [`stb`](https://github.com/nothings/stb) and [`concurrentqueue`](https://github.com/cameron314/concurrentqueue). A big thank you to these folks.

