/* this file is used to generate vektor.h: cc -E vektor_in.h | sed '/^\#/d' | indent -st -ut -ts2 -sob -hnl -l0 > vektor_out.h
 * by Ryan Lucchese
 * April 13 2012 */

#define vektor_in_h

#include <core/log.h>
#include <core/glsl_shaders.h>
#include <core/net.h>
#include <core/sdl.h>
#include <core/image.h>
#include <core/texture.h>
#include <core/scenegraph.h>
#include <core/sprite.h>
#include <core/skybox.h>
#include <core/model.h>
#include <core/draw_model.h>
#include <core/event.h>
#include <core/input.h>
#include <core/keys.h>
#include <core/keybind.h>
#include <core/keystates.h>
#include <core/window.h>
#include <core/camera.h>
#include <core/engine.h>

