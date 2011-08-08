/*
 * Camera.h
 * 
 * Description:
 * Camera Class.
 *
 * Last Modified:   11/07/22
 * Changelog:       11/07/22 - Constructor, Accessors, Mutators
 *                  11/08/02 - Adapted for helicopter
 *                  11/08/06 - Implemented camera functionality
 */

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
	Camera(void);
	virtual ~Camera(void);
	void view();
	void yaw(float angle);
	void pitch(float angle);
	void roll(float angle);
	void translate(float stepX, float stepY, float stepZ);
	void strafe(float step);
	void move(float step);
	void rise(float step);
	void crossProduct(float x1, float y1, float z1, float x2, float y2, float z2, float &xr, float &yr, float &zr);
	float magnitude(float x, float y, float z);
	void normalizeVector(float &x, float &y, float &z);
    float zNear, zFar, fov;
	float cx, cy, cz;	// Camera position
	float dx, dy, dz;	// Line of sight vector
private:
	float ux, uy, uz;	// Up vector
	float rx, ry, rz;	// Right vector
	float camYaw, camPitch, camRoll;
};

#endif
