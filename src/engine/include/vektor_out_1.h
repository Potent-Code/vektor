/* Vektor game engine
 * by Ryan Lucchese, Kenneth Wilke
 * May 14 2011 */

#ifndef vektor_h
#define vektor_h

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <time.h>
#include <stdint.h>
#include <mathlib.h>


#define log_err(str) _log_err(str, __func__, __FILE__, __LINE__)
#define log_err_sys(str) _log_err_sys(str, errno, __func__, __FILE__, __LINE__)

#define get_scene_data(obj) &(obj->scene_data)

