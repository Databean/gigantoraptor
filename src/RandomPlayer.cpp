#include "RandomPlayer.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

RandomPlayer::RandomPlayer() {
	srand(time(NULL));
}

RandomPlayer::~RandomPlayer() {
	
}

GameState RandomPlayer::placePiece(const GameState& g_old) {
	GameState g = g_old;
	
	pos piece = (1 << ((random()%6)+1)) | color;
	pos i = (random()%2) + color*6;
	pos j = random()%8;
	
	
	if(g.placePiece(piece,i,j)) {
		//cout << "successful piece placement" << endl;
		cout << "placing " << int(piece) << " at " << int(i) << ", " << int(j) << " as " << color << endl;
	}
	//
	
	return g;
}

GameState RandomPlayer::doMove(const GameState& g_old) {
	GameState g = g_old;
	
	pos i_s = random()%8, j_s = random()%8, i_f = random()%8, j_f = random()%8;
	if(g.movePiece(i_s,j_s,i_f,j_f)) {
		cout << "moving from " << int(i_s) << ", " << int(j_s) << " to " << int(i_f) << ", " << int(j_f) << " as " << int(color) << endl;
	}
	
	return g;
}