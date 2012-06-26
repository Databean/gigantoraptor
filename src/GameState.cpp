#include "GameState.h"
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;

GameState::GameState() {
	for(unsigned char i=0;i<64;i++) {
		board[i]=0;
	}
	gameStarted = false;
	toMove = WHITE_BIT;
	movesLeft = 16;
}

GameState::~GameState() {
	
}

bool GameState::placePiece(const char& type,const char& i,const char& j) {
	if(gameStarted) { return false; } //are we placing pieces?
	if(i < 0 || j < 0 || i > 7 || j > 7) { return false ;} //is this inside the board?
	if(toMove != (type&COLOR_MASK)) { return false; } //not accpetable if the piece is not of the person who is to move
	if((type & COLOR_MASK) == WHITE_BIT && i < 6) { return false; }
	if((type & COLOR_MASK) == BLACK_BIT && i > 1) { return false; }
	if(piece(i,j)!=0) { return false; } //already something there
	char typeNoColor = type & (~COLOR_MASK);
	char intendedOfType = 0;
	switch(typeNoColor) {
		case PAWN_MASK: intendedOfType = 8; break;
		case KNIGHT_MASK:
		case BISHOP_MASK:
		case ROOK_MASK: intendedOfType = 2; break;
		case KING_MASK:
		case QUEEN_MASK: intendedOfType = 1; break;
		default: return false; //not a valid piece
	}
	char actualOfType = 0;
	if((type & COLOR_MASK) == WHITE_BIT) {
		for(char i=0;i<8;i++) {
			actualOfType += (piece(6,i) == type) + (piece(7,i) == type);
		}
	} else {
		for(char i=0;i<8;i++) {
			actualOfType += (piece(0,i) == type) + (piece(1,i) == type);
		}
	}
	if(actualOfType == intendedOfType) { return false; } //already got enough of those
	
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

bool GameState::movePiece(const char& i_s,const char& j_s,const char& i_f,const char& j_f) {
	if(!gameStarted) { printf("game hasn't started\n"); return false; } //are we moving pieces?
	if(i_s < 0 || j_s < 0 || i_s > 7 || j_s > 7 || i_f < 0 || j_f < 0 || i_f > 7 || j_f > 7) { printf("not in board\n"); return false; } //is this inside the board?
	if(!piece(i_s,j_s)) { printf("no piece\n"); return false; }
	if((piece(i_s,j_s) & COLOR_MASK) != toMove) { printf("wrong color\n"); return false; } //is it this person's turn?
	if(piece(i_f,j_f)!=0) { printf("moving to occupied\n"); return false; } // is there something occupying the spot to move to?
	if(frozen(i_s,j_s)) { printf("frozen\n"); return false; }
	if(std::abs(i_f-i_s)+std::abs(j_f-j_s)!=1) { printf("too far\n"); return false; }
	if(piece(i_s,j_s) & PAWN_MASK) {
		if((i_f-i_s) == ((piece(i_s,j_s) & COLOR_MASK) * 2 - 1)) { printf("pawns don't move back\n"); return false; } //pawns going in the right direction?
	}
	
	piece(i_f,j_f) = piece(i_s,j_s);
	piece(i_s,j_s) = 0;
	
	movesLeft--;
	
	finalizeMove();
	return true;
}

void GameState::killUnguardedTrapPieces() {
	char i_arr[] = {2, 2, 5, 5};
	char j_arr[] = {2, 5, 2, 5};
	
	for(unsigned char a=0;a<4;a++) {
		for(unsigned char b=0;b<4;b++) {
			char i = i_arr[a];
			char j = j_arr[b];
			if(piece(i,j)) {
				char color = piece(i,j) & COLOR_MASK;
				char count = 0;
				count += (piece(i+1,j)!=0) && ((piece(i+1,j)&COLOR_MASK) == color);
				count += (piece(i,j+1)!=0) && ((piece(i,j+1)&COLOR_MASK) == color);
				count += (piece(i-1,j)!=0) && ((piece(i-1,j)&COLOR_MASK) == color);
				count += (piece(i,j-1)!=0) && ((piece(i,j-1)&COLOR_MASK) == color);
				if(count==0) {
					cout << "a " << int(piece(i,j)) << " from " << (piece(i,j) & (COLOR_MASK)) << " died in " << int(i) << ", " << int(j) << endl;
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

bool GameState::frozen(const char& i,const char& j) {
	if(i < 0 || j < 0 || i > 7 || j > 7) { return true; } //is this inside the board?
	if(piece(i,j)==0) { return true; } // is there actually a piece here?
	
	signed char count = 0;
	char color = piece(i,j) & COLOR_MASK;
	char pieceNoColor = piece(i,j) & (~COLOR_MASK);
	char p;
#define FROZEN_OPERATION \
if((p&COLOR_MASK) == color) { count += 10; } \
else if(stronger(p,pieceNoColor)) { count--; }
	
	if(i < 7 && (p = piece(i+1,j) != 0)) {
		FROZEN_OPERATION
	}
	if(i > 0 && (p = piece(i-1,j) != 0)) {
		FROZEN_OPERATION
	}
	if(j < 7 && (p = piece(i,j+1) != 0)) {
		FROZEN_OPERATION
	}
	if(j > 0 && (p = piece(i,j-1) != 0)) {
		FROZEN_OPERATION
	}
	if(count < 0) {
		cout << "piece at " << i << ", " << j << " frozen" << endl;
	}
	return count < 0;
}

bool GameState::pushPiece(const char& i_1,const char& j_1,const char& i_2,const char& j_2,const char& i_3,const char& j_3) {
	//piece on (i_1,j_1) pushes piece on (i_2,j_2) to (i_3,j_3)
	if(movesLeft < 2) { return false; }
	if(i_1 < 0 || j_1 < 0 || i_1 > 7 || j_1 > 7) { return false; } //is this inside the board?
	if(i_2 < 0 || j_2 < 0 || i_2 > 7 || j_2 > 7) { return false; } //is this inside the board?
	if(i_3 < 0 || j_3 < 0 || i_3 > 7 || j_3 > 7) { return false; } //is this inside the board?
	if(! piece(i_1,j_1)) { return false; } //does the pushing piece exist?
	if(! piece(i_2,j_2)) { return false; } //does the piece being pushed exist?
	if(piece(i_3,j_3)) { return false; } //is the pushing to square unoccupied?
	const char& p1 = piece(i_1,j_1);
	const char& p2 = piece(i_2,j_2);
	if(frozen(i_1,i_2)) { return false; }
	if((p1 & COLOR_MASK) != toMove) { return false; }
	if((p2 & COLOR_MASK) == toMove) { return false; }
	if(std::abs(i_2-i_1)+std::abs(j_2-j_1)!=1) { return false; } //are pusher and pushee on neighboring squares?
	if(std::abs(i_3-i_2)+std::abs(j_3-j_2)!=1) { return false; } //are pushee and spot to be pushed to on neighboring squares?
	if(! stronger(p1,p2)) { return false; }
	
	piece(i_3,j_3) = piece(i_2,j_2);
	piece(i_2,j_2) = piece(i_1,j_1);
	piece(i_1,j_1) = 0;
	movesLeft -= 2;
	
	finalizeMove();
	
	return true;
}

bool GameState::pullPiece(const char& i_1,const char& j_1,const char& i_2,const char& j_2,const char& i_3,const char& j_3) {
	//piece on (i_1,j_1) pulls piece on (i_2,j_2) and moves to (i_3,j_3)
	if(movesLeft < 2) { return false; }
	if(i_1 < 0 || j_1 < 0 || i_1 > 7 || j_1 > 7) { return false; } //is this inside the board?
	if(i_2 < 0 || j_2 < 0 || i_2 > 7 || j_2 > 7) { return false; } //is this inside the board?
	if(i_3 < 0 || j_3 < 0 || i_3 > 7 || j_3 > 7) { return false; } //is this inside the board?
	if(! piece(i_1,j_1)) { return false; } //does the pulling piece exist?
	if(! piece(i_2,j_2)) { return false; } //does the piece being pulled exist?
	if(piece(i_3,j_3)) { return false; } //is the pulling to square unoccupied?
	const char& p1 = piece(i_1,j_1);
	const char& p2 = piece(i_2,j_2);
	if(frozen(i_1,i_2)) { return false; }
	if((p1 & COLOR_MASK) != toMove) { return false; }
	if((p2 & COLOR_MASK) == toMove) { return false; }
	if(std::abs(i_2-i_1)+std::abs(j_2-j_1)!=1) { return false; } //are puller and pullee on neighboring squares?
	if(std::abs(i_3-i_1)+std::abs(j_3-j_1)!=1) { return false; } //are puller and spot to be moved to neighboring?
	if(! stronger(p1,p2)) { return false; }
	
	piece(i_3,j_3) = piece(i_1,j_1);
	piece(i_1,j_1) = piece(i_2,j_2);
	piece(i_2,j_2) = 0;
	movesLeft -= 2;
	
	finalizeMove();
	
	return true;
}