/* camera
 * by Ryan Lucchese
 * June 7 2011 */

#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

typedef struct
{
	float position[3];
	float up[3];
	float forward[3];
} *camera;

#include "sdl_window.h"
#include "input.h"

extern camera add_camera(float x, float y, float z);
extern void camera_matrix(camera c);
extern void camera_mouselook(camera c);

#endif
