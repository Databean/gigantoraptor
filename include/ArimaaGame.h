#ifndef ARIMAA_GAME_H
#define ARIMAA_GAME_H

#include "CApp.h"
#include "Player.h"
#include "GameState.h"

class ArimaaGame : public CApp {
public:
	ArimaaGame(Player& white,Player& black);
	virtual ~ArimaaGame();
	
	virtual bool init();
	virtual void draw();
	
private:
	GLuint pieceTextures[128];
	GameState state;
	Player& white;
	Player& black;
};

#endif