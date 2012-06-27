#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer();
	virtual ~HumanPlayer();
	
	virtual void setColor(const bool& b) {color = b;}
	virtual const bool& getColor() {return color;}
	
	virtual void placePiece(GameState&);
	virtual void doMove(GameState&);
	
	virtual void handleEvent(const GameState&,const SDL_Event&);
	virtual void draw(const ArimaaGame&, const GameState&);
	
private:
	bool color;
	pos select_i_1, select_j_1, select_i_2, select_j_2, select_i_3, select_j_3;
	pos piece;
	pos pieceCount;
	unsigned short mouseX, mouseY;
	
};

#endif