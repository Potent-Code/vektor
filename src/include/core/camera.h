/* camera
 * by Ryan Lucchese
 * June 7 2011 */

#ifndef camera_h

#ifndef vektor_in_h
#define camera_h

#include <math.h>
#include <delta.h>

#include <core/log.h>
#include <core/scenegraph.h>
#include <core/window.h>

#endif // vektor_in_h

// types of cameras
#define CAMERA_TYPE_FIXED 1
#define CAMERA_TYPE_FOLLOW 2
#define CAMERA_TYPE_MOUSELOOK 3

typedef struct
{
	scenegraph_node scene_data;
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
#include <core/input.h>
#include <core/event.h>
#endif // vektor_in_h

extern camera add_camera(float _x, float _y, float _z);
extern void camera_mouselook(camera c);
extern void camera_update(void* cp);
extern void camera_draw(void* cp);
extern void enable_mouselook(camera c);
extern void disable_mouselook(camera c);

#endif
