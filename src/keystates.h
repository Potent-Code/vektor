/* key states
 * by Ryan Lucchese
 * April 12 2012 */

#ifndef keystates_h
#define keystates_h

#include "keybind.h"
#include "event.h"

extern void keystates_init();
extern int keystate_get(int key);
extern void keystates_remove();

#endif // keystates_h
