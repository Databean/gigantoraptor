#ifndef HUMAN_VIS_PLAYER
#define HUMAN_VIS_PLAYER

#include "HumanPlayer.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <gl.h>

class HumanVisPlayer : public HumanPlayer {
public:
    
    virtual void draw(const ArimaaGame&, const GameState&);
	
private:
	
	bool initializeText();
	
	int textWidth, textHeight;
	
	GLuint textures[64];

};
#endif



