/*
 * Camera.h
 * 
 * Description:
 * Camera Class.
 *
 * Last Modified:   11/07/22
 * Changelog:       11/07/22 - Constructor, Accessors, Mutators
 *                  11/08/02 - Adapted for helicopter
 */

#ifndef CAMERA_H
#define CAMERA_H
#include "global.h"

class Camera
{
    public:
        // Perspective
        float fov;
        float zNear;
        float zFar;

        // Direction
        float xAt;
        float yAt;
        float zAt;
        
        Camera();
        // ~Camera(); // Using default

        void setPerspective(float fov, float zNear, float zFar);
        void setLookAt(float xAt, float yAt, float zAt);
};

#endif
