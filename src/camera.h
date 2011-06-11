/* camera
 * by Ryan Lucchese
 * June 7 2011 */

#ifndef CAMERA_H
#define CAMERA_H

typedef struct
{
	float x;
	float y;
	float z;
	float theta; // inclination angle
	float phi; // azimuthal angle
} *camera;

camera add_camera(float x, float y, float z);

#endif
