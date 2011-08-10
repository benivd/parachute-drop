#include "Camera.h"
#include <cmath>
#include <GL/glut.h>

#include "global.h"

#define Sqr(x)  x*x

// Constructor, initializes a camera to default values
Camera::Camera(void) {
	cx = GAME_WIDTH/2, cy = GAME_HEIGHT/2, cz = 10.0;
	dx = 0.0, dy = 0.0, dz = -1.0;
	ux = 0.0, uy = 1.0, uz = 0.0;
	rx = 1.0, ry = 0.0, rz = 0.0;
	camYaw = 0.0, camPitch = 0.0, camRoll = 0.0;

    fov = FOV; zNear = 0.1; zFar = -GAME_DEPTH;

}

// Destructor
Camera::~Camera(void) {

}

// Sets the camera to view the scene
void Camera::view() {
	glLoadIdentity();
	gluLookAt(cx, cy, cz, cx+dx, cy+dy, cz+dz, ux, uy, uz);
}

// Yaws the camera, a positive value yaws to the right
void Camera::yaw(float angle) {
	camYaw += angle;
	float x = dx*cos(angle*M_PI/180.0) + rx*sin(angle*M_PI/180.0);
	float y = dy*cos(angle*M_PI/180.0) + ry*sin(angle*M_PI/180.0);
	float z = dz*cos(angle*M_PI/180.0) + rz*sin(angle*M_PI/180.0);
	normalizeVector(x, y, z);
	dx = x, dy = y, dz = z;
	crossProduct(dx, dy, dz, ux, uy, uz, rx, ry, rz);
}

// Pitches the camera, a positive value pitches upwards
void Camera::pitch(float angle) {
	camPitch += angle;
	float x = dx*cos(angle*M_PI/180.0) + ux*sin(angle*M_PI/180.0);
	float y = dy*cos(angle*M_PI/180.0) + uy*sin(angle*M_PI/180.0);
	float z = dz*cos(angle*M_PI/180.0) + uz*sin(angle*M_PI/180.0);
	normalizeVector(x, y, z);
	dx = x, dy = y, dz = z;
	crossProduct(rx, ry, rz, dx, dy, dz, ux, uy, uz);
}

// Rolls the camera, a positive value rolls clockwise
void Camera::roll(float angle) {
	camRoll += angle;
	float x = rx*cos(angle*M_PI/180.0) - ux*sin(angle*M_PI/180.0);
	float y = ry*cos(angle*M_PI/180.0) - uy*sin(angle*M_PI/180.0);
	float z = rz*cos(angle*M_PI/180.0) - uz*sin(angle*M_PI/180.0);
	normalizeVector(x, y, z);
	rx = x, ry = y, rz = z;
	crossProduct(rx, ry, rz, dx, dy, dz, ux, uy, uz);
}

// Translates the camera from its current location by the vector (stepX, stepY, stepZ)
void Camera::translate(float stepX, float stepY, float stepZ) {
	cx += stepX;
	cy += stepY;
	cz += stepZ;
}

// Strafes the camera, a positive value strafes to the right
void Camera::strafe(float step) {
	cx += rx*step;
	cy += ry*step;
	cz += rz*step;
}

// Moves the camera, a positive value moves forward
void Camera::move(float step) {
	cx += dx*step;
	cy += dy*step;
	cz += dz*step;
}

// Raises the camera, a negative value lowers it
void Camera::rise(float step) {
	cx += ux*step;
	cy += uy*step;
	cz += uz*step;
}

// Helper method used to compute cross products
void Camera::crossProduct(float x1, float y1, float z1, float x2, float y2, float z2, float &xr, float &yr, float &zr) {
	xr = y1*z2-z1*y2;
	yr = z1*x2-x1*z2;
	zr = x1*y2-y1*x2;
}

// Helper method used to compute the magnitude of a vector
float Camera::magnitude(float x, float y, float z) {
	return (sqrt(Sqr(x)+Sqr(y)+Sqr(z)));
}

// Helper method used to normalize vectors
void Camera::normalizeVector(float &x, float &y, float &z) {
	float m = magnitude(x, y, z);
	if (m!=0) {
		x = x/m;
		y = y/m;
		z = z/m;
	}
}
