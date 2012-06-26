#include "QueenAggressor.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

QueenAggressor::QueenAggressor() {
	
}

QueenAggressor::~QueenAggressor() {
	
}

void QueenAggressor::placePiece(GameState& g) {
	char piece = (1 << ((random()%6)+1)) | color;
	char i = (color*6)+random()%2;
	char j = random()%8;
	if(piece & KING_MASK) {
		i = color ? 6 : 1;
	}
	if(g.placePiece(piece,i,j)) {
		//cout << "successful piece placement" << endl;
		cout << "placing " << int(piece) << " at " << int(i) << ", " << int(j) << " as " << color << endl;
	}
	//
}

void QueenAggressor::doMove(GameState& g) {
	//find our queen
	signed char qi=9;
	signed char qj=9;
	for(unsigned char a = 0;a < 8;a++) {
		for(unsigned char b = 0;b < 8;b++) {
			if(g.getPiece(a,b)==(KING_MASK | color)) {
				qi = a;
				qj = b;
			}
		}
	}
	if(qi==9 || qj==9) { //if we have no queen, do something silly
		cout << "no king found" << endl;
		doRandom(g); return;
	}
	//find the nearest enemy piece that we can take
	signed char ei = 100;
	signed char ej = 100;
	for(unsigned char a = 0;a < 8;a++) {
		for(unsigned char b = 0;b < 8;b++) {
			char piece = g.getPiece(a,b);
			if(((piece & COLOR_MASK) != color) && (abs(qi-a)+abs(qj-b)<abs(qi-ei)+abs(qj-ej)) && g.stronger(QUEEN_MASK,piece)) {
				ei = a;
				ej = b;
			}
		}
	}
	if(ei == 100 || ej == 100) {
		cout << "no enemy pieces found" << endl;
		doRandom(g); return;
	}
	if(abs(qi-ei)+abs(qj-ej)>1) {
		//move towards it
		unsigned char i;
		unsigned char j;
		if(pathFind(g,qi,qj,ei,ej,i,j)) {
			cout << "can't get there" << endl;
		} else {
			doRandom(g);
		}
	}
	cout << "not implemented yet" << endl;
	doRandom(g);
	
}

void QueenAggressor::doRandom(GameState& g) {
	char i_s = random()%8, j_s = random()%8, i_f = random()%8, j_f = random()%8;
	if(g.movePiece(i_s,j_s,i_f,j_f)) {
		cout << "moving from " << int(i_s) << ", " << int(j_s) << " to " << int(i_f) << ", " << int(j_f) << " as " << int(color) << endl;
	}
}

struct data {
	unsigned char i;
	unsigned char j;
	unsigned char prev;
};

bool QueenAggressor::pathFind(GameState& g,const unsigned char& i_s,const unsigned char& j_s,const unsigned char& i_f,const unsigned char& j_f,unsigned char& i,unsigned char& j) {
	
	vector<data> moveVec;
	bool visited[64];
	for(unsigned char a=0;a<64;a++) {
		const unsigned char& p = g.getPiece(a/8,a%8);
		visited[a] = p && (p & COLOR_MASK) == color;
	}
	visited[2*8+2] = visited[2*8+5] = visited[5*8+2] = visited[5*8 + 5] = true;
	visited[i_s*8+j_s] = true;
	data initial = { i_s, j_s, 0 };
	moveVec.push_back(initial);
	for(unsigned char b=0;b<moveVec.size();b++) {
		data v = moveVec[b];
		if(v.i == i_f && v.j == j_f) {
			while(v.prev != 0) {
				v = moveVec[v.prev];
			}
			i = v.i;
			j = v.j;
			return true;
		}
		if(v.i<7 && !visited[(v.i+1)*8+j]) {
			data v_up = {(unsigned char)(v.i+1), v.j, b};
			moveVec.push_back(v_up);
		}
		if(v.i>0 && !visited[(v.i-1)*8+j]) {
			data v_down = {(unsigned char)(v.i-1), v.j, b};
			moveVec.push_back(v_down);
		}
		if(v.j<7 && !visited[v.i*8+j+1]) {
			data v_right = {v.i, (unsigned char) (v.j+1), b};
			moveVec.push_back(v_right);
		}
		if(v.j>0 && !visited[v.i*8+j-1]) {
			data v_left = {v.i, (unsigned char) (v.j+1), b};
			moveVec.push_back(v_left);
		}
	}
	return false;
}