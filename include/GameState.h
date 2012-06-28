#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Types.h"

/**
 * Each bit represents a different piece
 * These are used to interact with the char resultant from getPiece
 */
#define BLACK_BIT 0
#define WHITE_BIT 1
#define COLOR_MASK 0x1
#define PAWN_MASK 0x2
#define KNIGHT_MASK 0x4
#define BISHOP_MASK 0x8
#define ROOK_MASK 0x10
#define QUEEN_MASK 0x20
#define KING_MASK 0x40

/**
 * \brief Encapsulates the game and provides an interface for player interaction
 * 
 * 
 */
class GameState {
public:
	GameState();
	virtual ~GameState();
	//GameState(const GameState&); the default is acceptable, since no pointers are stored
	//GameState& operator=(const GameState&); the default is acceptable, since no pointers are stored
	bool operator==(const GameState& other);
	
	bool canPlace(const pos& type,const pos& i,const pos& j);
	bool canMove(const pos& i_s,const pos& j_s,const pos& i_f,const pos& j_f); //move from (i_s,j_s) to (i_f,j_f)
	bool canPush(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3); //piece on (i_1,j_1) pushes piece on (i_2,j_2) to (i_3,j_3)
	bool canPull(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3); //piece on (i_1,j_1) pulls piece on (i_2,j_2) and moves to (i_3,j_3)
	
	bool placePiece(const pos& type,const pos& i,const pos& j);
	bool movePiece(const pos& i_s,const pos& j_s,const pos& i_f,const pos& j_f); //move from (i_s,j_s) to (i_f,j_f)
	bool pushPiece(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3); //piece on (i_1,j_1) pushes piece on (i_2,j_2) to (i_3,j_3)
	bool pullPiece(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3); //piece on (i_1,j_1) pulls piece on (i_2,j_2) and moves to (i_3,j_3)
	
	/**
	 * Returns the piece located at provided coordinates
	 */
	inline const pos& getPiece(const pos& i,const pos& j) const { return board[i*8+j]; }
	
	/**
	 */
	inline const bool& getToMove() const { return toMove; }
	inline const pos& getMovesLeft() const { return movesLeft; }
	inline const bool& getGameStarted() const { return gameStarted; }
	bool frozen(const pos& i,const pos& j);
	inline bool stronger(const pos& p1,const pos& p2) { return (p1&(~COLOR_MASK))>(p2&(~COLOR_MASK)); } //is p1 stronger than p2?
	
private:
	inline pos& piece(const pos& i,const pos& j) { return board[i*8+j]; }
	
	void finalizeMove();
	void killUnguardedTrapPieces();
	void updateTurn();
	
	pos board[64]; //the board is filled with things that look like (QUEEN_MASK | WHITE_BIT)
	bool toMove; //whose turn is it?
	pos movesLeft; //how many moves left in the current turn?
	bool gameStarted; //are we placing pieces or moving them?
};

#endif
