#include "MinimaxPlayer.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

using std::max;
using std::min;
using std::cout;
using std::endl;
using std::exit;

MinimaxPlayer::MinimaxPlayer() {
	
}

MinimaxPlayer::~MinimaxPlayer() {
	
}

GameState MinimaxPlayer::placePiece(const GameState& g_old) {
	GameState g = g_old;
	pos piece = (1 << ((random()%6)+1)) | color;
	pos i = (color*6)+random()%2;
	pos j = random()%8;
	if(piece & KING_MASK) {
		i = color ? 6 : 1;
	}
	while(!g.placePiece(piece,i,j)) {
		i = (color*6)+random()%2;
		j = random()%8;
		piece = (1 << ((random()%6)+1)) | color;
		//cout << "successful piece placement" << endl;
		//cout << "placing " << int(piece) << " at " << int(i) << ", " << int(j) << " as " << color << endl;
	}
	return g;
}

pos MinimaxPlayer::evaluate(const GameState& g) {
	pos ret = 0;
	for(pos i=0;i<8;i++) {
		for(pos j=0;j<8;j++) {
			const pos& piece = g.getPiece(i,j);
			if(piece) {
				bool pieceColor = getPieceColor(piece);
				pos modifier = (pieceColor == color)*2 - 1;
				switch(stripColor(piece)) {
					case PAWN_MASK: ret += modifier * 1; break;
					case KNIGHT_MASK: ret += modifier * 3; break;
					case BISHOP_MASK: ret += modifier * 4; break;
					case ROOK_MASK: ret += modifier * 5; break;
					case QUEEN_MASK: ret += modifier * 8; break;
					case KING_MASK: ret += modifier * 10; break;
				}
			}
		}
	}
	return ret;
}

minimax_res MinimaxPlayer::minimax(GameState& g,pos depth) {
	if(depth <= 0) {
		return minimax_res(evaluate(g),-1,-1,-1,-1);
	}
	
	bool maximize = g.getToMove() == color;
	minimax_res alpha = minimax_res((pos)((maximize*2 - 1) * 100),-1,-1,-1,-1);
	
	for(pos i=0;i<8;i++) {
		for(pos j=0;j<8;j++) {
			if(!g.getPiece(i,j) || !isColor(g.getPiece(i,j),color)) {
				continue;
			}
			//canMove, etc reject i,j that are outside of the board, so i'm not doing that here
			if(g.canMove(i,j,i+1,j)) {
				GameState g_clone = g;
				g_clone.movePiece(i,j,i+1,j);
				minimax_res res = minimax(g_clone,depth-1);
				res.i1 = i;
				res.j1 = j;
				res.i2 = i+1;
				res.j2 = j;
				alpha = maximize ? max(alpha,res) : min(alpha,res);
			} else { //we can push/pull this dude
				
			}
			if(g.canMove(i,j,i-1,j)) {
				GameState g_clone = g;
				g_clone.movePiece(i,j,i-1,j);
				minimax_res res = minimax(g_clone,depth-1);
				res.i1 = i;
				res.j1 = j;
				res.i2 = i-1;
				res.j2 = j;
				alpha = maximize ? max(alpha,res) : min(alpha,res);
			} else { //we can push/pull this dude
				
			}
			if(g.canMove(i,j,i,j+1)) {
				GameState g_clone = g;
				g_clone.movePiece(i,j,i,j+1);
				minimax_res res = minimax(g_clone,depth-1);
				res.i1 = i;
				res.j1 = j;
				res.i2 = i;
				res.j2 = j+1;
				alpha = maximize ? max(alpha,res) : min(alpha,res);
			}
			if(g.canMove(i,j,i,j-1)) {
				GameState g_clone = g;
				g_clone.movePiece(i,j,i,j-1);
				minimax_res res = minimax(g_clone,depth-1);
				res.i1 = i;
				res.j1 = j;
				res.i2 = i;
				res.j2 = j-1;
				alpha = maximize ? max(alpha,res) : min(alpha,res);
			}
		}
	}
	
	return alpha;
	
}

GameState MinimaxPlayer::doMove(const GameState& g_old) {
	GameState g = g_old;
	minimax_res m = minimax(g,4);
	if(g.movePiece(m.i1,m.j1,m.i2,m.j2)) {
		cout << "success! " << (int)m.i1 << " " << (int)m.j1 << " " << (int)m.i2 << " " << (int)m.j2 << endl;
		exit(0);
	}
	return g;
	
}