#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "GameState.h"

class ArimaaGame;

class Player {
public:
	Player();
	virtual ~Player();
	
	virtual void setColor(const bool& b) = 0;
	virtual const bool& getColor() = 0;
	
	virtual void placePiece(GameState&) = 0;
	virtual void doMove(GameState&) = 0;
	
	virtual void handleEvent(const GameState&,const SDL_Event&) {}
	virtual void draw(const ArimaaGame&,const GameState&) {}
	
private:
};


#endif