#include "CApp.h"
#include "SDL_ttf.h"
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

CApp::CApp(unsigned int windowWidth,unsigned int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

CApp::~CApp() {
	TTF_Quit();
	SDL_Quit();
}

bool CApp::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL failed to initialize." << endl;
		return false;
	}
	if(TTF_Init()==-1) {
		cout << "SDL_ttf failed to initialize." << endl;
		cout << "TTF_GetError: " << TTF_GetError() << endl;
		return false;
	} else {
		cout << "initialized SDL_ttf" << endl;
	}
	
	if((Surf_Display = SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_HWSURFACE | SDL_OPENGL)) == NULL) {
		cout << "Failed to create OpenGL surface: " << SDL_GetError() << std::endl;
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

