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
	bool pathFind(GameState& g,const unsigned char& i_s,const unsigned char& j_s,const unsigned char& i_f,const unsigned char& j_f,unsigned char& i,unsigned char& j);
	
	bool color;
};

#endif