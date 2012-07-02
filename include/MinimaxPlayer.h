#ifndef MINIMAX_PLAYER
#define MINIMAX_PLAYER

#include "GameState.h"
#include "Player.h"

struct minimax_res {
	minimax_res(const pos& score) : score(score) {}
	pos score, i1, j1, i2, j2, i3, j3;
	inline bool operator<(const minimax_res& other) const { return score < other.score; }
	inline bool operator>(const minimax_res& other) const { return score > other.score; }
	inline bool operator==(const minimax_res& other) const { return score == other.score; }
	
};

class MinimaxPlayer : public Player {
public:
	MinimaxPlayer();
	virtual ~MinimaxPlayer();
	
	virtual void setColor(const bool& b) {color = b;}
	virtual const bool& getColor() {return color;}
	
	virtual GameState placePiece(const GameState&);
	virtual GameState doMove(const GameState&);
	
	//virtual void handleEvent(const GameState&,const SDL_Event&);
	//virtual void draw(const ArimaaGame&, const GameState&);
	
private:
	
	pos evaluate(const GameState& g);
	minimax_res minimax(const GameState& g,pos depth,minimax_res alpha,minimax_res beta);
	
	bool color;
	
};

#endif