#include <iostream>

#include <glm/glm.hpp>

using namespace std;

int print() {
	glm::vec3 a(1, 2, 3);
	glm::vec3 b(4, 5, 6);
	glm::vec3 r = glm::cross(a, b);
	cout << "r = " << r.x << ", " << r.y << ", " << r.z << endl;
}
