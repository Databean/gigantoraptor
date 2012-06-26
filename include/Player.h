#ifndef PLAYER_H
#define PLAYER_H

#include "GameState.h"

class Player {
public:
	Player();
	virtual ~Player();
	
	virtual void setColor(const bool& b) = 0;
	virtual const bool& getColor() = 0;
	
	virtual void placePiece(GameState&) = 0;
	virtual void doMove(GameState&) = 0;
	
private:
};


#endif