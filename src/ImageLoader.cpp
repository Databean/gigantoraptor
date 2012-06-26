#include "ImageLoader.h"

using namespace std;

GLuint getTextureFromImage(String image) {
	SDL_Surface* surface;
	SDL_RWops *rwop;
	rwop=SDL_RWFromFile(image.c_str(), "rb");
	surface=IMG_LoadPNG_RW(rwop);
	if(!surface) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
		// handle error
		return 0;
	}
	GLenum texture_format;
	GLint  nOfColors;
	GLuint texture;
	
	// get the number of channels in the SDL surface
	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4)     // contains an alpha channel
	{
		printf("image is 4 colors\n");
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			
			texture_format = GL_BGRA;
	} else if (nOfColors == 3)     // no alpha channel
	{
		printf("image is 3 colors\n");
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		printf("warning: the image is not truecolor..  this will probably break\n");
		// this error should not go unhandled
	}
		
	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );
	
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );
	
	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
					texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	
	SDL_FreeSurface(surface);
	(rwop)->close(rwop);
	
	glBindTexture( GL_TEXTURE_2D, 0);
	
	return texture;
}
