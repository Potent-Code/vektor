/* camera
 * by Ryan Lucchese
 * June 7 2011 */

#ifndef camera_h

#ifndef vektor_in_h
#define camera_h

#include <math.h>
#include <mathlib.h>

#include "log.h"
#include "window.h"

#endif // vektor_in_h

// types of cameras
#define CAMERA_TYPE_FIXED 1
#define CAMERA_TYPE_FOLLOW 2
#define CAMERA_TYPE_MOUSELOOK 3

typedef struct
{
	float *x;
	float *y;
	float *z;
	float position[3]; // position vektor (*x, *y, *z)
	float speed; // movement speed
	// for mouse calculations
	float dx;
	float dy;
	float pitch;
	float yaw;
	// state variables
	unsigned int type;
	unsigned int active;
} *camera;

#ifndef vektor_in_h
#include "input.h"
#include "event.h"
#endif // vektor_in_h

extern camera add_camera(float _x, float _y, float _z);
extern void camera_mouselook(camera c);
extern void camera_move(void* cp);
extern void enable_mouselook(camera c);
extern void disable_mouselook(camera c);
extern void camera_remove(void* cp);

#endif
