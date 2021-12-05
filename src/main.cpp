#include <SFML/Graphics/Image.hpp>
#include <vector>
#include <memory>
#include <fstream>

#include <sphere.h>
#include <cube.h>
#include <plane.h>
#include <triangle.h>
#include <cylinder.h>
#include <camera.h>
#include <structs.h>

using namespace linalg::aliases;

const int window_size_x = 1280, window_size_y = 720;
float aspect_ratio = float(window_size_x) / window_size_y, fov = M_PI / 2;

float3 sky_color{0, 200, 255};

std::vector<std::shared_ptr<Camera>> cameras;
std::vector<std::shared_ptr<Object>> objects;
std::vector<std::shared_ptr<Light>> lights;

byte4 colors_matrix[window_size_x * window_size_y];

float3 raytrace(Ray ray, std::shared_ptr<Object> ignored = nullptr){
	std::shared_ptr<Object> near = nullptr;
	float rv, min_rv, reflection_intensity;
	float3 ray_color, surf_color;
	Ray reflection, transformed;

	// Searching for nearest intersected object
	for (const auto& elem : objects){
		if (elem == ignored) continue;
		rv = elem->getIntersectonWith(ray);
		if (rv > 0 && rv < 500 && (!near || rv < min_rv))
			near = elem, min_rv = rv;
	}

	if (!near)
		return sky_color;
	ray.tail = ray.origin + min_rv * ray.direction;

	// Calculation reflected ray color
	reflection_intensity = near->getReflectionIntensity();
	if (reflection_intensity > 0){
		reflection.origin = ray.tail,
		reflection.direction = 2 * near->getNormal() * 
			dot(near->getNormal(), -ray.direction) + ray.direction,
		ray_color += reflection_intensity * raytrace(reflection, near);
	}

	for (const auto &light : lights){
		// Calculation surface color
		surf_color += near->getPhongColor(ray, *light);
		
		// Calculation shadows
		for (const auto &elem : objects)
			if (elem != near && elem->getIntersectonWith({ray.tail, -light->getDirection(ray.tail)}) > 0){
				ray_color += -45.f;
				break;
			}
	}
	ray_color += (1 - reflection_intensity) * surf_color;

	return linalg::max(linalg::min(ray_color, 255), 0);
}

bool readSceneFromFile(std::string file_name){
	std::ifstream fin(file_name);
	if (!fin.is_open())
		return false;
	std::string name;
	float3 pos, color, norm, up, center, point[3];
	float fv, rad, refl = 0.f;
	while (fin >> name){
		if (name == "Camera"){
			fin >> pos.x >> pos.y >> pos.z >> up.x >> up.y >> up.z 
				>> center.x >> center.y >> center.z >> fv;
			cameras.push_back(std::make_shared<Camera>(pos, up, center, fv * M_PI / 180, aspect_ratio));	
		}
		else if (name == "Light"){
			fin >> pos.x >> pos.y >> pos.z >> color.x >> color.y >> color.z;
			lights.push_back(std::make_shared<Light>(pos, color));
		}
		else if (name != "" && name != "#") {
			fin >> pos.x >> pos.y >> pos.z >> color.x >> color.y >> color.z;
			if (name == "Sphere"){
				fin >> rad >> refl;
				objects.push_back(std::make_shared<Sphere>(color, rad));
			}
			else if (name == "Cube"){
				fin >> rad >> refl;
				objects.push_back(std::make_shared<Cube>(color, rad));
			}
			else if (name == "Plane"){
				fin >> norm.x >> norm.y >> norm.z >> refl;
				objects.push_back(std::make_shared<Plane>(color, norm));
			}
			else if (name == "Cylinder"){
				fin >> rad 
					>> point[0].x >> point[0].y >> point[0].z
					>> point[1].x >> point[1].y >> point[1].z >> refl;
				objects.push_back(std::make_shared<Cylinder>(color, rad, point[0], point[1]));
			}
			else if (name == "Triangle"){
				fin >> point[0].x >> point[0].y >> point[0].z
					>> point[1].x >> point[1].y >> point[1].z
					>> point[2].x >> point[2].y >> point[2].z >> refl;
				objects.push_back(std::make_shared<Triangle>(color, point[0], point[1], point[2]));
			}
			objects[objects.size() - 1]->applyTransform(linalg::translation_matrix(pos));
			objects[objects.size() - 1]->setReflectionIntensity(refl);
		}
		for (char c = fin.peek(); c != '\n' && c != EOF; fin.get(c));
		name = "";
		pos = float3(0.f);
	}
	fin.close();
	return true;
}

int main(int argc, char *argv[])
{
	if (!readSceneFromFile("./scene.txt"))
		return 0;

	for (int k = 0; k < cameras.size(); ++k){
		sf::Image im;
		for (int j = 0; j < window_size_y; ++j)
			for (int i = 0; i < window_size_x; ++i){
				Ray ray = cameras[k]->getRay(2.f * i / window_size_x - 1, 1 - 2.f * j / window_size_y);
				colors_matrix[i + j * window_size_x] = {byte3{raytrace(ray)}, 255};
			}
		im.create(window_size_x, window_size_y, &colors_matrix[0].x);
		im.saveToFile("camera" + std::to_string(k) + ".png");
	}
	return 0;
}