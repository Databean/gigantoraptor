#ifndef GAME_STATE_H
#define GAME_STATE_H

#define BLACK_BIT 0
#define WHITE_BIT 1
#define COLOR_MASK 0x1
#define PAWN_MASK 0x2
#define KNIGHT_MASK 0x4
#define BISHOP_MASK 0x8
#define ROOK_MASK 0x10
#define QUEEN_MASK 0x20
#define KING_MASK 0x40

class GameState {
public:
	GameState();
	virtual ~GameState();
	//GameState(const GameState&); the default is acceptable, since no pointers are stored
	//GameState& operator=(const GameState&); the default is acceptable, since no pointers are stored
	
	bool placePiece(const char& type,const char& i,const char& j);
	bool movePiece(const char& i_s,const char& j_s,const char& i_f,const char& j_f); //move from (i_s,j_s) to (i_f,j_f)
	bool pushPiece(const char& i_1,const char& j_1,const char& i_2,const char& j_2,const char& i_3,const char& j_3); //piece on (i_1,j_1) pushes piece on (i_2,j_2) to (i_3,j_3)
	bool pullPiece(const char& i_1,const char& j_1,const char& i_2,const char& j_2,const char& i_3,const char& j_3); //piece on (i_1,j_1) pulls piece on (i_2,j_2) and moves to (i_3,j_3)
	
	
	inline const char& getPiece(const char& i,const char& j) const { return board[i*8+j]; }
	inline const bool& getToMove() const { return toMove; }
	inline const char& getMovesLeft() const { return movesLeft; }
	inline const bool& getGameStarted() const { return gameStarted; }
	bool frozen(const char& i,const char& j);
	inline bool stronger(const char& p1,const char& p2) { return (p1&(~COLOR_MASK))>(p2&(~COLOR_MASK)); } //is p1 stronger than p2?
	
private:
	inline char& piece(const char& i,const char& j) { return board[i*8+j]; }
	
	void finalizeMove();
	void killUnguardedTrapPieces();
	void updateTurn();
	
	char board[64]; //the board is filled with things that look like (QUEEN_MASK | WHITE_BIT)
	bool toMove; //whose turn is it?
	char movesLeft; //how many moves left in the current turn?
	bool gameStarted; //are we placing pieces or moving them?
};

#endif