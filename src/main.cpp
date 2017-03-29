#include "camera.hpp"
#include "scene.hpp"
#include "lights/box_light.hpp"
#include "objects/plane.hpp"
#include "objects/sphere.hpp"
#include "objects/triangle.hpp"
#include "objects/polygon_mesh.hpp"
#include "json.hpp"

int width = 400;
int height = 300;
int field = 45;

using json = nlohmann::json;

Vector parse_vector(const json &v) {
  return Vector(v[0], v[1], v[2]);
}

Vector parse_color(const json &c) {
  return Color(c[0], c[1], c[2]);
}

Material parse_material(const json &m) {
  return Material(
    parse_color(m["color"]),
    m["k_diffusive"],
    m["k_diffusive_reflective"],
    m["k_specular"],
    m["k_reflective"],
    m["k_refractive"],
    m["k_refractive_index"]
  );
}

Scene parse_scene(const json &s) {
  auto camera = new Camera(parse_vector(s["camera"]["position"]), width, height, field);
  auto scene = Scene(camera);
  for (auto &l : s["lights"]) {
    if (l["type"] == "box_light") {
      scene.add(new BoxLight(
        parse_color(l["color"]),
        l["intensity"],
        parse_vector(l["position"]),
        parse_vector(l["size"])
      ));
    }
  }
  for (auto &o : s["objects"]) {
    if (o["type"] == "plane") {
      scene.add(new Plane(
        parse_vector(o["point"]),
        parse_vector(o["normal"]),
        parse_material(o["material"])
      ));
    } else if (o["type"] == "sphere") {
      scene.add(new Sphere(
        parse_vector(o["center"]),
        o["radius"],
        parse_material(o["material"])
      ));
    } else if (o["type"] == "polygon_mesh") {
      scene.add(new PolygonMesh(
        o["path"],
        parse_vector(o["position"]),
        o["size"],
        parse_material(o["material"])
      ));
    }
  }
  return scene;
}

Scene read_scene(const std::string &path) {
  std::ifstream ifs(path, std::ios::in);
  json json;
  ifs >> json;
  ifs.close();
  return parse_scene(json);
}

int main(int argc, char** argv) {
  auto scene = read_scene("../scenes/scene1.json");
  scene.render();
  scene.save("scene1.ppm");
}