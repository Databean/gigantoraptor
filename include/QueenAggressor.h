#ifndef QUEEN_AGGRESSOR_H
#define QUEEN_AGGRESSOR_H

#include "Player.h"

class QueenAggressor : public Player {
public:
	QueenAggressor();
	virtual ~QueenAggressor();
	
	virtual void setColor(const bool& b) { color = b; }
	virtual const bool& getColor() { return color; }
	
	virtual void placePiece(GameState&);
	virtual void doMove(GameState&);
private:
	void doRandom(GameState& g);
	bool pathFind(GameState& g,const int& i_s,const int& j_s,const int& i_f,const int& j_f,const int& i,const int& j);
	
	bool color;
};

#endif