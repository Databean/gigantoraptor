#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include "Player.h"

class RandomPlayer : public Player {
public:
	RandomPlayer();
	virtual ~RandomPlayer();
	
	virtual void setColor(const bool& b) { color = b; }
	virtual const bool& getColor() { return color; }
	
	virtual GameState placePiece(const GameState&);
	virtual GameState doMove(const GameState&);
	
private:
	bool color;
};

#endif