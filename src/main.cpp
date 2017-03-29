#include "camera.hpp"
#include "scene.hpp"
#include "box_light.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "polygon_mesh.hpp"

void scene1(const Camera* camera) {
  auto scene = Scene(camera);
  // box light
  scene.add(new BoxLight(
    Color::WHITE, 3000,
    Vector(-10, 20, -20),
    Vector(20, .5, 20)
  ));
  // floor
//  scene.add(new Plane(
//    Vector(0, 0, 0),
//    Vector(0, 1, 0),
//    Material(Color::YELLOW, 1, .8, 0, 0, 0)
//  ));
  // back wall
//  scene.add(new Plane(
//    Vector(0, 0, -30),
//    Vector(0, 0, 1),
//    Material(Color::BLUE, 1, .8, 0, 0, 0)
//  ));
//  // red ball
//  scene.add(new Sphere(
//    Vector(5, 5, -15), 2,
//    Material(Color::RED, .5, .8, .2, 0, 0)
//  ));
//  // white ball
//  scene.add(new Sphere(
//    Vector(-5, 5, -15), 3,
//    Material(Color::WHITE, .5, .8, .2, 0, 0)
//  ));
  scene.add(new PolygonMesh(
    "../models/teapot.obj",
    Material(Color::RED, .5, .8, .2, 0, 0)
  ));
//  scene.add(new Triangle(
//    Vector(-5, 5, -15),
//    Vector(-5, -5, -15),
//    Vector(0, 0, -15),
//    Material(Color::RED, .5, .8, .2, 0, 0)
//  ));
//  // glass ball
//  scene.add(new Sphere(
//    Vector(0, 5, 5), 5,
//    Material(Color::WHITE, 0, 0, 0, 1, 1.05)
//  ));
  scene.render();
  scene.save("out.ppm");
}

int main(int argc, char** argv) {
  srand((unsigned)time(nullptr));
  scene1(new Camera(Vector(0, 10, 40)));
//  scene1(new Camera(Vector(0, 10, 40), 800, 600));
}