#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rwops.h"
#include "gl.h"
#include "glu.h"
#include "Types.h"

GLuint getTextureFromImage(String image);
GLuint getTextureFromText(String text, int& w, int& h, String fontname = "fonts/ConsolaMono.ttf", int fontsize = 24);

#endif