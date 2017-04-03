#include "camera.hpp"
#include "scene.hpp"
#include "lights/box_light.hpp"
#include "objects/plane.hpp"
#include "objects/sphere.hpp"
#include "objects/polygon_mesh.hpp"
#include "json.hpp"

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
  auto c = s["camera"];
  auto camera = new Camera(
    parse_vector(c["position"]),
    c["width"],
    c["height"],
    c["field"]
  );
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

std::string input_path = "../scenes/scene4.json";
std::string output_path = "../images/scene4.ppm";

int main(int argc, char** argv) {
  std::ifstream ifs(input_path, std::ios::in);
  json s;
  ifs >> s;
  ifs.close();
  auto scene = parse_scene(s);
  scene.render();
  scene.save(output_path);
}