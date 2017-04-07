# `ray-tracer`

## Introduction

`ray-tracer` is a photo-realistic 3D rendering engine written in `C++`.

## Features
* Multi-thread rendering
* Accelerate using k-dimensional tree
* Read scene setting from `.json` files
* Read polygon mesh from `.obj` files
* Save rendered image to `.png` files
* Mesh smoothing

## Effects
* Transparent and reflective object
* Procedural and custom texture
* Soft shadow (area lights)
* Diffusive reflection
* Color bleeding

## Structure
```
scenes/           # scene setting files (json files)
images/           # rendering results (png files)
resources/        # 3D models and textures (obj and jpeg files)
src/              # source code
| externals/      # external libraries
| libraries/      # libraries (vector, color, ray and k-d tree)
| objects/        # renderable objects (plane, sphere, triangle and polygon mesh)
| lights/         # renderable lights (point light, distant light and area light)
| textures/       # renderable textures (homo texture, grid texture and image texture)
| camera.hpp      # camera ray
| scene.hpp       # rendering engine
| main.cpp        # entrance
```

## Usages

### Requirements
* `Unix / Linux`
* `GCC / G++ 4.8+`
* `CMake 3.5+`

### Compilation
```
mkdir -p build/ && cd build/
cmake ../ && make all
```

### Rendering
```
./ray-tracer <input-scene-path> <output-image-path>
```

For example, in order to render `texture.json`, you may use the following instruction:

```
./ray-tracer ../scenes/texture.json ../images/texture.png
```

You may also create new scene settings (you may refer to `scenes/mesh.json` and `scenes/texture.json` for more details).

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

## License
`ray-tracer` is released under the [open-source MIT license](https://github.com/zhijian-liu/ray-tracer/blob/master/LICENSE).

## References
* [Scratchapixel -- Learn Computer Graphics from Scratch](https://www.scratchapixel.com)
* [Flipcode -- Raytracing Topics and Techniques](http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_1_Introduction.shtml)
* [Yuxin Wu's Repository -- Ray Tracing Engine](https://github.com/ppwwyyxx/Ray-Tracing-Engine)

## Acknowledgements
This project is built with [`json`](https://github.com/nlohmann/json), [`stb`](https://github.com/nothings/stb) and [`concurrentqueue`](https://github.com/cameron314/concurrentqueue). A big thank you to these folks.

