#ifndef C_APP_H
#define C_APP_H

#define DEBUG(text) std::cout << __FILE__ << ":" << __LINE__ << ":" << text << std::endl; 

#include <SDL.h>
#include <SDL_opengl.h>
#include <gl.h>
#include <glu.h>

class CApp {
public:
	CApp(unsigned int windowWidth,unsigned int windowHeight);
	virtual ~CApp();
	
	virtual bool init();
	virtual void render();
	virtual void handleEvent(const SDL_Event&);
	
	virtual int getWindowHeight();
	virtual int getWindowWidth();
	
protected:
	virtual void draw(); //override to put in own drawing commands
	virtual SDL_Surface* getSDLSurface();
private:
	
	
	unsigned int windowHeight;
	unsigned int windowWidth;
	SDL_Surface* Surf_Display;
};

#endif