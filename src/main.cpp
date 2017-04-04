#include "camera.hpp"
#include "scene.hpp"
#include "lights/box_light.hpp"
#include "objects/plane.hpp"
#include "objects/sphere.hpp"
#include "objects/polygon_mesh.hpp"
#include "externals/json.hpp"
#include "textures/homo_texture.hpp"
#include "textures/grid_texture.hpp"
#include "textures/image_texture.hpp"

using json = nlohmann::json;

Vector parse_vector(const json &v) {
  return Vector(v[0], v[1], v[2]);
}

Vector parse_color(const json &c) {
  return Color(c[0], c[1], c[2]);
}

const Texture* parse_texture(const json &t) {
  if (t["type"] == "homo_texture") {
    return new HomoTexture(
      parse_color(t["color"]),
      t["k_diffusive"],
      t["k_diffusive_reflective"],
      t["k_specular"],
      t["k_reflective"],
      t["k_refractive"],
      t["k_refractive_index"]
    );
  } else if (t["type"] == "grid_texture") {
    return new GridTexture(
      {parse_color(t["colors"][0]), parse_color(t["colors"][1])},
      t["scale"],
      t["k_diffusive"],
      t["k_diffusive_reflective"],
      t["k_specular"],
      t["k_reflective"],
      t["k_refractive"],
      t["k_refractive_index"]
    );
  } else if (t["type"] == "image_texture") {
    return new ImageTexture(
      t["path"],
      t["scale"],
      t["k_diffusive"],
      t["k_diffusive_reflective"],
      t["k_specular"],
      t["k_reflective"],
      t["k_refractive"],
      t["k_refractive_index"]
    );
  }
  return nullptr;
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
        parse_vector(o["center"]),
        {parse_vector(o["axes"][0]), parse_vector(o["axes"][1])},
        parse_texture(o["texture"])
      ));
    } else if (o["type"] == "sphere") {
      scene.add(new Sphere(
        parse_vector(o["center"]),
        o["radius"],
        {parse_vector(o["axes"][0]), parse_vector(o["axes"][1])},
        parse_texture(o["texture"])
      ));
    } else if (o["type"] == "polygon_mesh") {
      scene.add(new PolygonMesh(
        o["path"],
        parse_vector(o["position"]),
        o["size"],
        parse_texture(o["texture"])
      ));
    }
  }
  return scene;
}

int main(int argc, char** argv) {
  std::string load_path = "../scenes/transparent.json";
  std::string dump_path = "../images/transparent.ppm";
  if (argc > 2) {
    load_path = argv[1];
    dump_path = argv[2];
  }
  std::ifstream ifs(load_path, std::ios::in);
  json s;
  ifs >> s;
  ifs.close();
  auto scene = parse_scene(s);
  scene.render();
  scene.save(dump_path);
}