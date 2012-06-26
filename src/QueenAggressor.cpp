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
	signed qi=9;
	signed qj=9;
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
		if(qi!=ei && !g.getPiece(qi+abs(ei-qi)/(ei-qi),qj)) {
			if(!g.movePiece(qi,qj,qi+abs(ei-qi)/(ei-qi),qj)) {
				cout << "can't move from " << qi << ", " << qj << " to " << qi+abs(ei-qi)/(ei-qi) << ", " << qj << endl;
			}
			return;
		}
		if(qj!=ej && !g.getPiece(qi,qj+abs(ej-qj)/(ej-qj))) {
			cout << "moving towards along j" << endl;
			g.movePiece(qi,qj,qi,qj+abs(ej-qj)/(ej-qj)); return;
		}
		cout << "can't move towards any enemies" << endl;
		doRandom(g);
	}
	
	
}

void QueenAggressor::doRandom(GameState& g) {
	char i_s = random()%8, j_s = random()%8, i_f = random()%8, j_f = random()%8;
	if(g.movePiece(i_s,j_s,i_f,j_f)) {
		cout << "moving from " << int(i_s) << ", " << int(j_s) << " to " << int(i_f) << ", " << int(j_f) << " as " << int(color) << endl;
	}
}

bool QueenAggressor::pathFind(GameState& g,const int& i_s,const int& j_s,const int& i_f,const int& j_f,const int& i,const int& j) {
	struct data {
		char i;
		char j;
		char prev;
	};
	vector<data> moveVec;
	bool visited[64];
	for(unsigned char a=0;a<64;a++) {
		const char& p = g.getPiece(a/8,a%8);
		visited[a] = p && (p & COLOR_MASK) == color;
	}
	visited[2*8+2] = visited[2*8+5] = visited[5*8+2] = visited[5*8 + 5] = true;
	visited[i_s*8+j_s] = true;
	data initial = { i_s, j_s, 0 };
	moveVec.push_back(initial);
	for(unsigned char b=0;b<moveVec.size(),b++) {
		data v = moveVec[b];
		if(v.i == i_f && v.j == j_f) {
			
		}
		if(v.i<7 && !visited[(v.i+1)*8+j]) {
			data v_up = {v.i+1, v.j, b};
			moveList.push_back(v_up);
		}
		if(v.i>0 && !visited[(v.i-1)*8+j]) {
			data v_down = {v.i-1, v.j, b};
			moveList.push_back(v_down);
		}
		if(v.j<7 && !visited[v.i*8+j+1]) {
			data v_right = {v.i, v.j+1, b};
			moveList.push_back(v_right);
		}
		if(v.j>0 && !visited[v.i*8+j-1]) {
			data v_left = {v.i, v.j+1, b};
			moveList.push_back(v_left);
		}
	}
}