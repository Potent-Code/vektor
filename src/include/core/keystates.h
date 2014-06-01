/* key states
 * by Ryan Lucchese
 * April 12 2012 */

#ifndef keystates_h

#ifndef vektor_in_h
#define keystates_h

#include <core/keybind.h>
#include <core/event.h>

#endif // vektor_in_h

extern void keystates_init();
extern int keystate_get(int key);
extern void keystates_remove();

#endif // keystates_h
