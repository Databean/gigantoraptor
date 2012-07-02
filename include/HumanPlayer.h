#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer();
	virtual ~HumanPlayer();
	
	virtual void setColor(const bool& b) {color = b;}
	virtual const bool& getColor() {return color;}
	
	virtual GameState placePiece(const GameState&);
	virtual GameState doMove(const GameState&);
	
	virtual void handleEvent(const GameState&,const SDL_Event&);
	virtual void draw(const ArimaaGame&, const GameState&);
	
protected:
	bool color;
	pos select_i_1, select_j_1, select_i_2, select_j_2, select_i_3, select_j_3;
    
    //piece mask
	pos piece;

    // number of pieces
	pos pieceCount;

    //updated through handleEvent
	unsigned short mouseX, mouseY;
	
};

#endif
