#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rwops.h"
#include "gl.h"
#include "glu.h"
#include "Types.h"

GLuint getTextureFromImage(String image);

#endif