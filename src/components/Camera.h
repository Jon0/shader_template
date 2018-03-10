/*
 * Camera.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <memory>

#include <epoxy/gl.h>
#include <epoxy/glx.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../buffer/Buffer.h"

namespace std {

struct CameraProperties {
	glm::mat4 P;
	glm::mat4 V;
	glm::mat4 M;
};

class Camera {
private:
	/*
	 * point the camera looks at
	 */
	glm::vec3 focus;

	glm::quat cam_angle, cam_angle_d;
	int windowwidth, windowheight;
	float viewzoom, cam_aspect;
	Buffer<CameraProperties> camera_properties;

public:
	Camera();
	virtual ~Camera();

	void update( float );
	void resize(int, int);

	void printAngle();
	void zoom(float);
	void rotate(glm::quat);
	void translate(glm::vec3);

	glm::quat cameraAngle();
	glm::vec3 project(const glm::vec3 &);
	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix();
	Buffer<CameraProperties> *properties();
};

} /* namespace std */
#endif /* CAMERA_H_ */
