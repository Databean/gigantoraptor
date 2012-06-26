#include "CApp.h"
#include <stdlib.h>

CApp::CApp(unsigned int windowWidth,unsigned int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

CApp::~CApp() {
	SDL_Quit();
}

bool CApp::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);
	
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);
	
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
	
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);
	
	if((Surf_Display = SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_HWSURFACE | SDL_OPENGL)) == NULL) {
		return false;
	}
	
	glClearColor(0, 0, 0, 0);
	
	glViewport(0, 0, windowWidth, windowHeight);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0, windowWidth, windowHeight, 0, 1, -1);
	//glFrustum(-windowWidth/2.f, windowWidth/2.f, -windowHeight/2.f, windowHeight/2.f, 20, 0.01);
	//glFrustum(0,windowWidth,windowHeight,0,40,0.01);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	return true;
}

void CApp::render() {
	draw();
	
	SDL_GL_SwapBuffers();
}

void CApp::draw() {}
void CApp::handleEvent(const SDL_Event& se) {}

int CApp::getWindowHeight() {
	return windowHeight;
}

int CApp::getWindowWidth() {
	return windowWidth;
}

SDL_Surface* CApp::getSDLSurface() {
	return Surf_Display;
}

