#include "ImageLoader.h"
#include <SDL_ttf.h>
#include <math.h>


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
	GLenum texture_format = GL_RGBA;
	GLint  nOfColors;
	GLuint texture;
	
	// get the number of channels in the SDL surface
	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4)     // contains an alpha channel
	{
		//printf("image is 4 colors\n");
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			
			texture_format = GL_BGRA;
	} else if (nOfColors == 3)     // no alpha channel
	{
		//printf("image is 3 colors\n");
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		printf("warning: the image is not truecolor..  this will probably break\n");
		// this error should not go unhandled
		return 0;
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

int nextpoweroftwo(int x) {
	double logbase2 = log(x) / log(2);
	return round(pow(2,ceil(logbase2)));
}

GLuint getTextureFromText(String text, int& w, int& h, String fontname, int fontsize) {
	
	SDL_Surface *initial;
	GLuint texture;
	
	TTF_Font *font = TTF_OpenFont( fontname.c_str(), fontsize );
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	
	if(!font) {
		printf("failed to load font\n");
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(0);
	}
	
	initial = TTF_RenderText_Blended(font, text.c_str(), color);
	
	if(!initial) {
		printf("Failed to draw text\n");
		return 0;
	}
	
	w = initial->w;
	h = initial->h;
	
	GLenum texture_format = GL_RGBA;
	GLint nOfColors = initial->format->BytesPerPixel;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (initial->format->Rmask == 0x000000ff) {
			texture_format = GL_RGBA;
		} else {
			texture_format = GL_BGRA;
		}
	} else if (nOfColors == 3)     // no alpha channel
	{
		//printf("image is 3 colors\n");
		if (initial->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		printf("warning: the image is not truecolor..  this will probably break\n");
		// this error should not go unhandled
		return 0;
	}
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, w, h, 0, texture_format, 
				 GL_UNSIGNED_BYTE, initial->pixels );
	
	SDL_FreeSurface(initial);
	
	TTF_CloseFont( font );
	
	glBindTexture( GL_TEXTURE_2D, 0);
	
	return texture;
}