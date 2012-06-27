#include "HumanPlayer.h"
#include <SDL_opengl.h>
#include <gl.h>
#include "ArimaaGame.h"
#include <iostream>

using std::cout;
using std::endl;

HumanPlayer::HumanPlayer() {
	select_i_1 = select_j_1 = select_i_2 = select_j_2 = select_i_3 = select_j_3 = -1;
	mouseX = mouseY = 0;
	piece = PAWN_MASK;
	pieceCount = 0;
	color = 0;
}

HumanPlayer::~HumanPlayer() {
	
}

void HumanPlayer::placePiece(GameState& g) {
	if(select_i_1 != -1 && select_j_1 != -1) {
		if(g.placePiece(piece | color,select_i_1,select_j_1)) {
			pieceCount++;
			switch(piece) {
				case PAWN_MASK:
					if(pieceCount==8) { piece <<= 1; pieceCount = 0; }
					break;
				case KNIGHT_MASK:
				case BISHOP_MASK:
				case ROOK_MASK:
					if(pieceCount==2) { piece <<= 1; pieceCount = 0; }
					break;
				case QUEEN_MASK:
				case KING_MASK:
					if(pieceCount==1) { piece <<= 1; pieceCount = 0; }
					break;
			}
		}
		select_i_1 = select_j_1 = -1;
	}
}

void HumanPlayer::doMove(GameState& g) {
	pos p1 = g.getPiece(select_i_1,select_j_1);
	if(!p1 || (p1 & COLOR_MASK) != color) {
		select_i_1 = select_j_1 = select_i_2 = select_j_2 = select_i_3 = select_j_3 = -1;
	}
	if(select_i_2 != -1) {
		pos p2 = g.getPiece(select_i_2,select_j_2);
		if(!p2) {
			g.movePiece(select_i_1,select_j_1,select_i_2,select_j_2);
			select_i_1 = select_j_1 = select_i_2 = select_j_2 = select_i_3 = select_j_3 = -1;
		} else {
			if(select_i_3 != -1) {
				if(!g.pushPiece(select_i_1,select_j_1,select_i_2,select_j_2,select_i_3,select_j_3)) {
					g.pullPiece(select_i_1,select_j_1,select_i_2,select_j_2,select_i_3,select_j_3);
				}
				select_i_1 = select_j_1 = select_i_2 = select_j_2 = select_i_3 = select_j_3 = -1;
			}
		}
	}
}

void HumanPlayer::handleEvent(const GameState& g,const SDL_Event& e) {
	switch(e.type) {
		case SDL_MOUSEMOTION:
			mouseX = e.motion.x;
			mouseY = e.motion.y;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseX = e.button.x;
			mouseY = e.button.y;
			if(select_i_1 == -1) {
				//cout << "select 1" << endl;
				select_i_1 = mouseX / 50;
				select_j_1 = mouseY / 50;
			} else if(select_i_2 == -1) {
				//cout << "select 2" << endl;
				select_i_2 = mouseX / 50;
				select_j_2 = mouseY / 50;
			} else if(select_i_3 == -1) {
				//cout << "select 3" << endl;
				select_i_3 = mouseX / 50;
				select_j_3 = mouseY / 50;
			} else {
				select_i_1 = select_j_1 = select_i_2 = select_j_2 = select_i_3 = select_j_3 = -1;
			}
			break;
	}
}

void HumanPlayer::draw(const ArimaaGame& a,const GameState& g) {
	if(!g.getGameStarted()) {
		glBindTexture( GL_TEXTURE_2D, a.getPieceTexture(piece | color));
		glBegin(GL_QUADS);
		glColor4f(1.0f,1.0f,1.0f,0.5f);
		glTexCoord2d(0.0,0.0); glVertex3f(mouseX-25,mouseY-25,0.5);
		glTexCoord2d(1.0,0.0); glVertex3f(mouseX+25,mouseY-25,0.5);
		glTexCoord2d(1.0,1.0); glVertex3f(mouseX+25,mouseY+25,0.5);
		glTexCoord2d(0.0,1.0); glVertex3f(mouseX-25,mouseY+25,0.5);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
	} else {
		glBegin(GL_QUADS);
		glColor4f(1.0f,0.0f,0.0f,0.5f);
		if(select_i_1 != -1) {
			glVertex3f(select_i_1*50,select_j_1*50,0.5);
			glVertex3f((select_i_1+1)*50,select_j_1*50,0.5);
			glVertex3f((select_i_1+1)*50,(select_j_1+1)*50,0.5);
			glVertex3f(select_i_1*50,(select_j_1+1)*50,0.5);
		}
		if(select_i_2 != -1) {
			glVertex3f(select_i_2*50,select_j_2*50,0.5);
			glVertex3f((select_i_2+1)*50,select_j_2*50,0.5);
			glVertex3f((select_i_2+1)*50,(select_j_2+1)*50,0.5);
			glVertex3f(select_i_2*50,(select_j_2+1)*50,0.5);
		}
		if(select_i_3 != -1) {
			glVertex3f(select_i_3*50,select_j_3*50,0.5);
			glVertex3f((select_i_3+1)*50,select_j_3*50,0.5);
			glVertex3f((select_i_3+1)*50,(select_j_3+1)*50,0.5);
			glVertex3f(select_i_3*50,(select_j_3+1)*50,0.5);
		}
		glEnd();
	}
}