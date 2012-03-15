/* camera
 * by Ryan Lucchese
 * June 7 2011 */

#ifndef camera_h
#define camera_h

#include <math.h>
#include <mathlib.h>

typedef struct
{
	float *x;
	float *y;
	float *z;
	matrix transform;
	matrix modelview;
	matrix rotate_x;
	matrix rotate_y;
	matrix rotate_z;
} *camera;

#include "sdl_window.h"
#include "input.h"
#include "event.h"

extern camera add_camera(float _x, float _y, float _z);
extern void camera_transform(void* cp);
extern void camera_matrix_reset(matrix mat);
extern void camera_mouselook(camera c);
extern void camera_move(void* cp);
extern void enable_mouselook();
extern void disable_mouselook();
extern void camera_remove(void* cp);

#endif
