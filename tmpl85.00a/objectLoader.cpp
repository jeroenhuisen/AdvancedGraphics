#include "template.h"

#include "objectLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader-master\tiny_obj_loader.h"


vector<Triangle*> ObjectLoader::loadObject(const std::string filename) {
	Material* pink = new Material(Color(0xFF, 0, 0xFF));
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str(), NULL, true);

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;
	

	vector<Triangle*> meshes;
	for (tinyobj::shape_t shape : shapes) {
		for (size_t f = 0; f < shape.mesh.indices.size() / 3; f++) {
			std::cout << "# of indices: " << shape.mesh.indices.size() << std::endl;
			tinyobj::index_t idx0 = shape.mesh.indices[3 * f + 0];
			tinyobj::index_t idx1 = shape.mesh.indices[3 * f + 1];
			tinyobj::index_t idx2 = shape.mesh.indices[3 * f + 2];

			//float v[3][3];
			glm::vec3 v1, v2, v3;
			int f0 = idx0.vertex_index;
			int f1 = idx1.vertex_index;
			int f2 = idx2.vertex_index;
				assert(f0 >= 0);
				assert(f1 >= 0);
				assert(f2 >= 0);

			v1.x = attrib.vertices[3 * f0];
			v2.x = attrib.vertices[3 * f1];
			v3.x = attrib.vertices[3 * f2];

			v1.y = attrib.vertices[3 * f0 + 1];
			v2.y = attrib.vertices[3 * f1 + 1];
			v3.y = attrib.vertices[3 * f2 + 1];

			v1.z = attrib.vertices[3 * f0 + 2];
			v2.z = attrib.vertices[3 * f1 + 2];
			v3.z = attrib.vertices[3 * f2 + 2];

			Triangle* t;
			if (attrib.normals.size() > 0) {
				int n0 = idx0.normal_index;
				int n1 = idx0.normal_index;
				int n2 = idx0.normal_index;
				glm::vec3 normal1 = glm::vec3(attrib.normals[3 * n0], attrib.normals[3 * n0 + 1], attrib.normals[3 * n0 + 2]);
				glm::vec3 normal2 = glm::vec3(attrib.normals[3 * n1], attrib.normals[3 * n1 + 1], attrib.normals[3 * n1 + 2]);
				glm::vec3 normal3 = glm::vec3(attrib.normals[3 * n2], attrib.normals[3 * n2 + 1], attrib.normals[3 * n2 + 2]);
				//std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
				t = new Triangle(v1, v2, v3, normal1, normal2, normal3, pink);
			}
			else {
				t = new Triangle(v1, v2, v3, pink);
			}
			
			meshes.push_back(t);
		}
	}
	return meshes;

}



ImportObject* ObjectLoader::loadObjectImportObject(const std::string filename, int* objSize) {
	Material* pink = new Material(Color(0xFF, 0, 0xFF));
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str(), NULL, true);

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;


	ImportObject* objects = new ImportObject[shapes.size()];
	ImportObject* objPtr = objects;
	*objSize = shapes.size();
	for (tinyobj::shape_t shape : shapes) {
		int size = shape.mesh.indices.size() / 3;
		std::cout << "# of indices: " << size << std::endl;
		Triangle* triangles = new Triangle[size];
		Triangle* trianglePtr = triangles;
		for (size_t f = 0; f < shape.mesh.indices.size() / 3; f++) {
			tinyobj::index_t idx0 = shape.mesh.indices[3 * f + 0];
			tinyobj::index_t idx1 = shape.mesh.indices[3 * f + 1];
			tinyobj::index_t idx2 = shape.mesh.indices[3 * f + 2];

			glm::vec3 v1, v2, v3;
			int f0 = idx0.vertex_index;
			int f1 = idx1.vertex_index;
			int f2 = idx2.vertex_index;
			assert(f0 >= 0);
			assert(f1 >= 0);
			assert(f2 >= 0);

			v1.x = attrib.vertices[3 * f0];
			v2.x = attrib.vertices[3 * f1];
			v3.x = attrib.vertices[3 * f2];

			v1.y = attrib.vertices[3 * f0 + 1];
			v2.y = attrib.vertices[3 * f1 + 1];
			v3.y = attrib.vertices[3 * f2 + 1];

			v1.z = attrib.vertices[3 * f0 + 2];
			v2.z = attrib.vertices[3 * f1 + 2];
			v3.z = attrib.vertices[3 * f2 + 2];

			trianglePtr->v1 = v1;
			trianglePtr->v2 = v2;
			trianglePtr->v3 = v3;
			trianglePtr->centroid = (v1 + v2 + v3) / 3.0f;
			trianglePtr->material = pink;

			if (attrib.normals.size() > 0) {
				int n0 = idx0.normal_index;
				int n1 = idx0.normal_index;
				int n2 = idx0.normal_index;
				glm::vec3 normal1 = glm::vec3(attrib.normals[3 * n0], attrib.normals[3 * n0 + 1], attrib.normals[3 * n0 + 2]);
				glm::vec3 normal2 = glm::vec3(attrib.normals[3 * n1], attrib.normals[3 * n1 + 1], attrib.normals[3 * n1 + 2]);
				glm::vec3 normal3 = glm::vec3(attrib.normals[3 * n2], attrib.normals[3 * n2 + 1], attrib.normals[3 * n2 + 2]);
				//std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
				trianglePtr->direction = glm::normalize(normal1 + normal2 + normal3);
				//new Triangle(v1, v2, v3, normal1, normal2, normal3, pink);
			}
			else {
				trianglePtr->direction = glm::normalize(glm::cross((v2 - v1), (v3 - v1)));
			}

			trianglePtr++;
		}
		objPtr->triangles = triangles;
		objPtr->amount = shape.mesh.indices.size() / 3;
		objPtr++;
	}
	return objects;

}




// based on viewerexample from tinyobjlibrary
