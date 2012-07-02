#include "MinimaxPlayer.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

//using std::max;
//using std::min;
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
				//if(g.frozen(i,j)) { ret -= modifier; }
			}
		}
	}
	return ret;
}

inline minimax_res max(const minimax_res& a,const minimax_res& b, int& i) {
	if(a == b && (random() % i == 0)) { i++; return b; }
	if(a < b) { i = 1; return b; }
	else { i = 1; return a; }
}
inline minimax_res min(const minimax_res& a,const minimax_res& b, int& i) {
	if(a == b && (random() % i == 0)) { i++; return b; }
	if(a < b) { i = 1; return a; }
	else { i = 1; return b; }
}

#define TEST_PIECE_MOVE(_i1,_j1,_i2,_j2) \
GameState g_clone = g; \
g_clone.movePiece(_i1,_j1,_i2,_j2); \
minimax_res res = minimax(g_clone,depth-1,alpha,beta); \
res.i1 = _i1; \
res.j1 = _j1; \
res.i2 = _i2; \
res.j2 = _j2; \
if(maximize) { \
	alpha = max(alpha,res,count); \
	if(alpha > beta) { \
		return alpha; \
	} \
} else { \
	beta = min(beta,res,count); \
	if(alpha > beta) { \
		return beta; \
	} \
}

#define TEST_PIECE_PULL(_i1,_j1,_i2,_j2,_i3,_j3) \
GameState g_clone = g; \
g_clone.pullPiece(_i1,_j1,_i2,_j2,_i3,_j3); \
minimax_res res = minimax(g_clone,depth-1,alpha,beta); \
res.i1 = _i1; \
res.j1 = _j1; \
res.i2 = _i2; \
res.j2 = _j2; \
res.i3 = _i3; \
res.j3 = _j3; \
if(maximize) { \
	alpha = max(alpha,res,count); \
	if(alpha > beta) { \
		return alpha; \
	} \
} else { \
	beta = min(beta,res,count); \
	if(alpha > beta) { \
		return beta; \
	} \
}

#define TEST_PIECE_PUSH(_i1,_j1,_i2,_j2,_i3,_j3) \
if(g.canPush(_i1,_j1,_i2,_j2,_i3,_j3)) { \
	GameState g_clone = g; \
	g_clone.pushPiece(_i1,_j1,_i2,_j2,_i3,_j3); \
	minimax_res res = minimax(g_clone,depth-1,alpha,beta); \
	res.i1 = _i1; \
	res.j1 = _j1; \
	res.i2 = _i2; \
	res.j2 = _j2; \
	res.i3 = _i3; \
	res.j3 = _j3; \
	if(maximize) { \
		alpha = max(alpha,res,count); \
		if(alpha > beta) { \
			return alpha; \
		} \
	} else { \
		beta = min(beta,res,count); \
		if(alpha > beta) { \
			return beta; \
		} \
	} \
}

minimax_res MinimaxPlayer::minimax(const GameState& g,pos depth,minimax_res alpha,minimax_res beta) {
	if(depth <= 0) {
		return minimax_res(evaluate(g));
	}
	
	bool maximize = g.getToMove() == color;
	const bool& pColor = g.getToMove();
	//minimax_res alpha = minimax_res((pos)((maximize*-2 + 1) * 100));
	int count=1;
	
	for(pos i=0;i<8;i++) {
		for(pos j=0;j<8;j++) {
			const pos& mypiece = g.getPiece(i,j);
			if(!g.getPiece(i,j) || !isColor(g.getPiece(i,j),pColor) || g.frozen(i,j)) {
				continue;
			}
			bool canMoveTop, movablePieceTop;
			bool canMoveBot, movablePieceBot;
			bool canMoveLft, movablePieceLft;
			bool canMoveRgt, movablePieceRgt;
			
			if(g.canMove(i,j,i,j-1)) { canMoveTop = true; movablePieceTop = false; }
			else {
				canMoveTop = false;
				if(j > 0 && g.getPiece(i,j-1) && !isColor(g.getPiece(i,j-1),pColor) && stronger(mypiece,g.getPiece(i,j-1))) {
					movablePieceTop = true;
				} else { movablePieceTop = false; }
			}
			if(g.canMove(i,j,i,j+1)) { canMoveBot = true; movablePieceBot = false; }
			else {
				canMoveBot = false;
				if(j < 7 && g.getPiece(i+1,j) && !isColor(g.getPiece(i,j+1),pColor) && stronger(mypiece,g.getPiece(i,j+1))) {
					movablePieceBot = true;
				} else { movablePieceBot = false; }
			}
			if(g.canMove(i,j,i+1,j)) { canMoveRgt = true; movablePieceRgt = false; }
			else {
				canMoveRgt = false;
				if(i < 7 && g.getPiece(i+1,j) && !isColor(g.getPiece(i+1,j),pColor) && stronger(mypiece,g.getPiece(i+1,j))) {
					movablePieceRgt = true;
				} else { movablePieceRgt = false; }
			}
			if(g.canMove(i,j,i-1,j)) { canMoveLft = true; movablePieceLft = false; }
			else {
				canMoveLft = false;
				if(i > 0 && g.getPiece(i-1,j) && !isColor(g.getPiece(i-1,j),pColor) && stronger(mypiece,g.getPiece(i-1,j))) {
					movablePieceLft = true;
				} else { movablePieceLft = false; }
			}
			
			if(g.getMovesLeft()<2) {
				movablePieceBot = movablePieceLft = movablePieceRgt = movablePieceTop = false;
			}
			
			//canMove, etc reject i,j that are outside of the board, so i'm not doing that here
			if(canMoveRgt) {
				TEST_PIECE_MOVE(i,j,i+1,j)
			} else if(movablePieceRgt) { //we can push/pull this dude
				//pull
				if(canMoveLft) {
					TEST_PIECE_PULL(i,j,i+1,j,i-1,j)
				}
				if(canMoveTop) {
					TEST_PIECE_PULL(i,j,i+1,j,i,j-1)
				}
				if(canMoveBot) {
					TEST_PIECE_PULL(i,j,i+1,j,i,j+1);
				}
				TEST_PIECE_PUSH(i,j,i+1,j,i+2,j) //right
				TEST_PIECE_PUSH(i,j,i+1,j,i+1,j+1) //down
				TEST_PIECE_PUSH(i,j,i+1,j,i+1,j-1) //up
			}
			if(canMoveLft) {
				TEST_PIECE_MOVE(i,j,i-1,j)
			} else if(movablePieceLft) { //we can push/pull this dude
				//pull
				if(canMoveRgt) {
					TEST_PIECE_PULL(i,j,i-1,j,i+1,j)
				}
				if(canMoveTop) {
					TEST_PIECE_PULL(i,j,i-1,j,i,j-1)
				}
				if(canMoveBot) {
					TEST_PIECE_PULL(i,j,i-1,j,i,j+1);
				}
				TEST_PIECE_PUSH(i,j,i-1,j,i-2,j) //left
				TEST_PIECE_PUSH(i,j,i-1,j,i+1,j+1) //down
				TEST_PIECE_PUSH(i,j,i-1,j,i+1,j-1) //up
			}
			if(canMoveBot) {
				TEST_PIECE_MOVE(i,j,i,j+1)
			} else if(movablePieceBot) { //we can push/pull this dude
				//pull
				if(canMoveRgt) {
					TEST_PIECE_PULL(i,j,i,j+1,i+1,j)
				}
				if(canMoveTop) {
					TEST_PIECE_PULL(i,j,i,j+1,i,j-1)
				}
				if(canMoveLft) {
					TEST_PIECE_PULL(i,j,i,j+1,i-1,j);
				}
				TEST_PIECE_PUSH(i,j,i,j+1,i-1,j+1) //left
				TEST_PIECE_PUSH(i,j,i,j+1,i,j+2) //up
				TEST_PIECE_PUSH(i,j,i,j+1,i+1,j+1) //right
			}
			if(canMoveTop) {
				TEST_PIECE_MOVE(i,j,i,j-1)
			} else if(movablePieceTop) { //we can push/pull this dude
				//pull
				if(canMoveRgt) {
					TEST_PIECE_PULL(i,j,i,j-1,i+1,j)
				}
				if(canMoveBot) {
					TEST_PIECE_PULL(i,j,i,j-1,i,j+1)
				}
				if(canMoveLft) {
					TEST_PIECE_PULL(i,j,i,j-1,i-1,j);
				}
				TEST_PIECE_PUSH(i,j,i,j-1,i-1,j-1) //left
				TEST_PIECE_PUSH(i,j,i,j-1,i,j-2) //down
				TEST_PIECE_PUSH(i,j,i,j-1,i+1,j-1) //right
			}
		}
	}
	
	return alpha;
	
}

GameState MinimaxPlayer::doMove(const GameState& g_old) {
	GameState g = g_old;
	minimax_res m = minimax(g,6,-100,100);
	if(g.canMove(m.i1,m.j1,m.i2,m.j2)) {
		g.movePiece(m.i1,m.j1,m.i2,m.j2);
		//exit(0);
	} else if(g.canPull(m.i1,m.j1,m.i2,m.j2,m.i3,m.j3)) {
		g.pullPiece(m.i1,m.j1,m.i2,m.j2,m.i3,m.j3);
	} else if(g.canPush(m.i1,m.j1,m.i2,m.j2,m.i3,m.j3)) {
		g.pushPiece(m.i1,m.j1,m.i2,m.j2,m.i3,m.j3);
	} else {
		cout << "failure!  " << (int)m.i1 << " " << (int)m.j1 << " " << (int)m.i2 << " " << (int)m.j2 << " " << (int)m.i3 << " " << (int)m.j3 << endl;
	}
	return g;
	
}