#ifndef ARIMAA_GAME_H
#define ARIMAA_GAME_H

#include "CApp.h"
#include "Player.h"
#include "GameState.h"
#include "SDL.h"

//don't call this
int gameLoopFunction(void* data);

class ArimaaGame : public CApp {
public:
	ArimaaGame(Player& white,Player& black);
	virtual ~ArimaaGame();
	
	virtual bool init();
	virtual void draw();
	
	virtual void playGame();
	virtual void haltGame();
	
	virtual void handleEvent(const SDL_Event&);
	
	inline GLuint getPieceTexture(const pos& piece) const {
		if(0 > piece || 127 < piece) { return 0; }
		return pieceTextures[piece];
	}
	
	friend int gameLoopFunction(void* data);
	
private:
	SDL_Thread* gameThread;
	SDL_mutex* stateMutex;
	bool running;
	
	//
	GLuint pieceTextures[128];
	GameState state;
	Player& white;
	Player& black;
};

#endif