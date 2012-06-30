#ifndef QUEEN_AGGRESSOR_H
#define QUEEN_AGGRESSOR_H

#include "Player.h"

class QueenAggressor : public Player {
public:
	QueenAggressor();
	virtual ~QueenAggressor();
	
	virtual void setColor(const bool& b) { color = b; }
	virtual const bool& getColor() { return color; }
	
	virtual GameState placePiece(const GameState&);
	virtual GameState doMove(const GameState&);
private:
	void doRandom(GameState& g);
	bool pathFind(GameState& g,const pos& i_s,const pos& j_s,const pos& i_f,const pos& j_f,pos& i,pos& j);
	
	bool color;
};

#endif