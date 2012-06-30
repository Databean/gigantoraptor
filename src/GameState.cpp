#include "GameState.h"
#include <cmath>
#include <iostream>
#include <cstdio>
#include "Debug.h"

using std::cout;
using std::abs;
using std::endl;

GameState::GameState() {
	for(pos i=0;i<64;i++) {
		board[i]=0;
	}
	gameStarted = false;
	toMove = WHITE_BIT;
	movesLeft = 16;
	gameFinished = false;
}

GameState::~GameState() {
	
}


bool GameState::canPlace(const pos& type,const pos& i,const pos& j) const {
	if(gameStarted) { return false; } //are we placing pieces?
	if(i < 0 || j < 0 || i > 7 || j > 7) { return false ;} //is this inside the board?
	if(toMove != (type&COLOR_MASK)) { return false; } //not accpetable if the piece is not of the person who is to move
	if(isWhite(type) && i < 6) { return false; }
	if(isBlack(type) && i > 1) { return false; }
	if(piece(i,j)!=0) { return false; } //already something there
	pos typeNoColor = stripColor(type);
	pos intendedOfType = 0;
	switch(typeNoColor) {
		case PAWN_MASK: intendedOfType = 8; break;
		case KNIGHT_MASK:
		case BISHOP_MASK:
		case ROOK_MASK: intendedOfType = 2; break;
		case KING_MASK:
		case QUEEN_MASK: intendedOfType = 1; break;
		default: return false; //not a valid piece
	}
	pos actualOfType = 0;
	if(isWhite(type)) {
		for(pos i=0;i<8;i++) {
			actualOfType += (piece(6,i) == type) + (piece(7,i) == type);
		}
	} else {
		for(pos i=0;i<8;i++) {
			actualOfType += (piece(0,i) == type) + (piece(1,i) == type);
		}
	}
	if(actualOfType == intendedOfType) { return false; } //already got enough of those
	return true;
}

bool GameState::placePiece(const pos& type,const pos& i,const pos& j) {
	if(!canPlace(type,i,j)) { return false; }
	
	piece(i,j) = type;
	movesLeft--;
	if(movesLeft == 0) {
		if(toMove == WHITE_BIT) {
			movesLeft = 16;
			toMove = BLACK_BIT;
		} else {
			movesLeft = 4;
			toMove = WHITE_BIT;
			gameStarted = true;
		}
	}
	
	return true;
}

bool GameState::canMove(const pos& i_s,const pos& j_s,const pos& i_f,const pos& j_f) const {
	if(!gameStarted) { DEBUG("game hasn't started"); return false; } //are we moving pieces?
	if(i_s < 0 || j_s < 0 || i_s > 7 || j_s > 7 || i_f < 0 || j_f < 0 || i_f > 7 || j_f > 7) { DEBUG("not in board"); return false; } //is this inside the board?
	if(!piece(i_s,j_s)) { DEBUG("no piece"); return false; }
	if((piece(i_s,j_s) & COLOR_MASK) != toMove) { DEBUG("wrong color"); return false; } //is it this person's turn?
	if(piece(i_f,j_f)!=0) { DEBUG("moving to occupied"); return false; } // is there something occupying the spot to move to?
	if(frozen(i_s,j_s)) { DEBUG("frozen"); return false; }
	if(abs(i_f-i_s)+abs(j_f-j_s)!=1) { DEBUG("too far"); return false; }
	if(isPawn(piece(i_s,j_s))) {
		if((i_f-i_s) == (getColor(piece(i_s,j_s)) * 2 - 1)) { DEBUG("pawns don't move back"); return false; } //pawns going in the right direction?
	}
	return true;
}
	
bool GameState::movePiece(const pos& i_s,const pos& j_s,const pos& i_f,const pos& j_f) {
	if(!canMove(i_s,j_s,i_f,j_f)) { return false; }
	
	piece(i_f,j_f) = piece(i_s,j_s);
	piece(i_s,j_s) = 0;
	
	movesLeft--;
	
	finalizeMove();
	return true;
}

void GameState::killUnguardedTrapPieces() {
	pos i_arr[] = {2, 2, 5, 5};
	pos j_arr[] = {2, 5, 2, 5};
	
	for(pos a=0;a<4;a++) {
		for(pos b=0;b<4;b++) {
			pos i = i_arr[a];
			pos j = j_arr[b];
			if(piece(i,j)) {
				pos color = getColor(piece(i,j));
				pos count = 0;
				count += (piece(i+1,j)!=0) && ((piece(i+1,j)&COLOR_MASK) == color);
				count += (piece(i,j+1)!=0) && ((piece(i,j+1)&COLOR_MASK) == color);
				count += (piece(i-1,j)!=0) && ((piece(i-1,j)&COLOR_MASK) == color);
				count += (piece(i,j-1)!=0) && ((piece(i,j-1)&COLOR_MASK) == color);
				if(count==0) {
					DEBUG("a " << int(piece(i,j)) << " from " << getColor(piece(i,j)) << " died in " << int(i) << ", " << int(j))
					piece(i,j) = 0;
				}
			}
		}
	}
}

void GameState::updateTurn() {
	if(movesLeft==0) {
		toMove = !toMove;
		movesLeft = 4;
	}
}

void GameState::finalizeMove() {
	killUnguardedTrapPieces();
	updateTurn();
}

bool GameState::frozen(const pos& i,const pos& j) const {
	if(i < 0 || j < 0 || i > 7 || j > 7) { return true; } //is this inside the board?
	if(piece(i,j)==0) { return true; } // is there actually a piece here?
	
	pos count = 0;
	pos color = getColor(piece(i,j));
	pos pieceNoColor = stripColor(piece(i,j));
	pos p;
#define FROZEN_OPERATION \
if(isColor(p,color)) { count += 10; } \
else if(stronger(p,pieceNoColor)) { count--; }
	
	if(i < 7 && ((p = piece(i+1,j)) != 0)) {
		FROZEN_OPERATION
	}
	if(i > 0 && ((p = piece(i-1,j)) != 0)) {
		FROZEN_OPERATION
	}
	if(j < 7 && ((p = piece(i,j+1)) != 0)) {
		FROZEN_OPERATION
	}
	if(j > 0 && ((p = piece(i,j-1)) != 0)) {
		FROZEN_OPERATION
	}
	if(count < 0) {
		DEBUG("piece at " << i << ", " << j << " frozen")
	}
	//cout << "count: " << (int)count << endl;
	return count < 0;
}

bool GameState::canPush(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3) const {
	//piece on (i_1,j_1) pushes piece on (i_2,j_2) to (i_3,j_3)
	if(movesLeft < 2) { return false; }
	if(i_1 < 0 || j_1 < 0 || i_1 > 7 || j_1 > 7) { return false; } //is this inside the board?
	if(i_2 < 0 || j_2 < 0 || i_2 > 7 || j_2 > 7) { return false; } //is this inside the board?
	if(i_3 < 0 || j_3 < 0 || i_3 > 7 || j_3 > 7) { return false; } //is this inside the board?
	if(! piece(i_1,j_1)) { return false; } //does the pushing piece exist?
	if(! piece(i_2,j_2)) { return false; } //does the piece being pushed exist?
	if(piece(i_3,j_3)) { return false; } //is the pushing to square unoccupied?
	const pos& p1 = piece(i_1,j_1);
	const pos& p2 = piece(i_2,j_2);
	if(frozen(i_1,j_1)) { return false; }
	if(!isColor(p1,toMove)) { return false; }
	if(isColor(p2,toMove)) { return false; }
	if(abs(i_2-i_1)+abs(j_2-j_1)!=1) { return false; } //are pusher and pushee on neighboring squares?
	if(abs(i_3-i_2)+abs(j_3-j_2)!=1) { return false; } //are pushee and spot to be pushed to on neighboring squares?
	if(! stronger(p1,p2)) { return false; }
	
	return true;
}

bool GameState::pushPiece(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3) {
	if(!canPush(i_1,j_1,i_2,j_2,i_3,j_3)) { return false; }
	
	piece(i_3,j_3) = piece(i_2,j_2);
	piece(i_2,j_2) = piece(i_1,j_1);
	piece(i_1,j_1) = 0;
	movesLeft -= 2;
	
	finalizeMove();
	
	return true;
}

bool GameState::canPull(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3) const {
	//piece on (i_1,j_1) pulls piece on (i_2,j_2) and moves to (i_3,j_3)
	if(movesLeft < 2) { DEBUG("haven't got enough moves"); return false; }
	if(i_1 < 0 || j_1 < 0 || i_1 > 7 || j_1 > 7) { return false; } //is this inside the board?
	if(i_2 < 0 || j_2 < 0 || i_2 > 7 || j_2 > 7) { return false; } //is this inside the board?
	if(i_3 < 0 || j_3 < 0 || i_3 > 7 || j_3 > 7) { return false; } //is this inside the board?
	if(! piece(i_1,j_1)) { return false; } //does the pulling piece exist?
	if(! piece(i_2,j_2)) { return false; } //does the piece being pulled exist?
	if(piece(i_3,j_3)) { return false; } //is the pulling to square unoccupied?
	const pos& p1 = piece(i_1,j_1);
	const pos& p2 = piece(i_2,j_2);
	if(frozen(i_1,j_1)) { DEBUG("frozen"); return false; }
	if(!isColor(p1,toMove)) { return false; }
	if(isColor(p2,toMove)) { return false; }
	if(abs(i_2-i_1)+abs(j_2-j_1)!=1) { return false; } //are puller and pullee on neighboring squares?
	if(abs(i_3-i_1)+abs(j_3-j_1)!=1) { return false; } //are puller and spot to be moved to neighboring?
	if(! stronger(p1,p2)) { return false; }
	return true;
}

bool GameState::pullPiece(const pos& i_1,const pos& j_1,const pos& i_2,const pos& j_2,const pos& i_3,const pos& j_3) {
	if(!canPull(i_1,j_1,i_2,j_2,i_3,j_3)) { return false; }
	
	piece(i_3,j_3) = piece(i_1,j_1);
	piece(i_1,j_1) = piece(i_2,j_2);
	piece(i_2,j_2) = 0;
	movesLeft -= 2;
	
	finalizeMove();
	
	return true;
}

bool GameState::operator==(const GameState& other) {
	for(pos i=0;i<64;i++) {
		if(other.board[i] != board[i]) {
			return false;
		}
	}
	return toMove == other.toMove && movesLeft == other.movesLeft && gameStarted == other.gameStarted;
}