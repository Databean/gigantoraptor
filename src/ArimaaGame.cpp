#include "ArimaaGame.h"
#include "ImageLoader.h"
#include <iostream>

using namespace std;

ArimaaGame::ArimaaGame(Player& white,Player& black) : CApp(400,400), white(white), black(black) {
	for(int i=0;i<128;i++) {
		pieceTextures[i] = 0;
	}
	
	white.setColor(WHITE_BIT);
	black.setColor(BLACK_BIT);
}

ArimaaGame::~ArimaaGame() {
	
}

bool ArimaaGame::init() {
	if(CApp::init()) {
		pieceTextures[PAWN_MASK | WHITE_BIT] = getTextureFromImage("images/pieces/WhiteP.png");
		pieceTextures[PAWN_MASK | BLACK_BIT] = getTextureFromImage("images/pieces/BlackP.png");
		pieceTextures[KNIGHT_MASK | WHITE_BIT] = getTextureFromImage("images/pieces/WhiteN.png");
		pieceTextures[KNIGHT_MASK | BLACK_BIT] = getTextureFromImage("images/pieces/BlackN.png");
		pieceTextures[BISHOP_MASK | WHITE_BIT] = getTextureFromImage("images/pieces/WhiteB.png");
		pieceTextures[BISHOP_MASK | BLACK_BIT] = getTextureFromImage("images/pieces/BlackB.png");
		pieceTextures[ROOK_MASK | WHITE_BIT] = getTextureFromImage("images/pieces/WhiteR.png");
		pieceTextures[ROOK_MASK | BLACK_BIT] = getTextureFromImage("images/pieces/BlackR.png");
		pieceTextures[KING_MASK | WHITE_BIT] = getTextureFromImage("images/pieces/WhiteK.png");
		pieceTextures[KING_MASK | BLACK_BIT] = getTextureFromImage("images/pieces/BlackK.png");
		pieceTextures[QUEEN_MASK | WHITE_BIT] = getTextureFromImage("images/pieces/WhiteQ.png");
		pieceTextures[QUEEN_MASK | BLACK_BIT] = getTextureFromImage("images/pieces/BlackQ.png");
		
		return true;
	}
	return false;
}
/**
 * Called by CApp::render
 * 

 */
void ArimaaGame::draw() {
	//Make players move
	if(state.getGameStarted()) { //move if game started
		if(state.getToMove() == WHITE_BIT) {
			white.doMove(state);
		} else {
			black.doMove(state);
		}
	} else { //place if game not started
		if(state.getToMove() == WHITE_BIT) {
			white.placePiece(state);
		} else {
			black.placePiece(state);
		}
	}
	//Draw board
	
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			//Draw square
			glBindTexture( GL_TEXTURE_2D, 0);
			int color = !(((i+1)%3 == 0) && ((j+1)%3 == 0));
			glBegin(GL_QUADS);
			glColor3f(color,color,color);
			glVertex3d(i*50,j*50,0);
			glVertex3d((i+1)*50,j*50,0);
			glVertex3d((i+1)*50,(j+1)*50,0);
			glVertex3d(i*50,(j+1)*50,0);
			glEnd();
			if(state.getPiece(i,j)!=0) {
				glBindTexture( GL_TEXTURE_2D, pieceTextures[(int)state.getPiece(i,j)] );
				glBegin(GL_QUADS);
				glColor3f(1,1,1);
				glTexCoord2d(0.0,0.0); glVertex3d(i*50,j*50,0);
				glTexCoord2d(1.0,0.0); glVertex3d((i+1)*50,j*50,0);
				glTexCoord2d(1.0,1.0); glVertex3d((i+1)*50,(j+1)*50,0);
				glTexCoord2d(0.0,1.0); glVertex3d(i*50,(j+1)*50,0);
				glEnd();
			}
		}
	}
	glBindTexture( GL_TEXTURE_2D, 0);
	//Draw board lines
	glBegin(GL_LINES);
	glColor3f(0,0,0);
	for(int i=1;i<8;i++) {
		glVertex3d(50*i,0,0.25);
		glVertex3d(50*i,400,0.25);
		glVertex3d(0,50*i,0.25);
		glVertex3d(400,50*i,0.25);
	}
	glEnd();
	
	//additional player drawing things
	if(state.getToMove() == WHITE_BIT) {
		white.draw(*this,state);
	} else {
		black.draw(*this,state);
	}
	
}

void ArimaaGame::handleEvent(const SDL_Event& event) {
	//give event to appropriate player
	if(state.getToMove() == WHITE_BIT) {
		white.handleEvent(state,event);
	} else {
		black.handleEvent(state,event);
	}
}