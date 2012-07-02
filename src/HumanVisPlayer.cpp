#include "HumanVisPlayer.h"
#include <SDL_opengl.h>
#include <gl.h>
#include "ArimaaGame.h"
#include <iostream>
#include <sstream>
#include <string>
#include "ImageLoader.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

template<class T>
string toString(const T& t) {
	stringstream stream;
	stream << t;
	return stream.str();
}


bool HumanVisPlayer::initializeText() {
	int pos=0;
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			textures[pos] = getTextureFromText(toString(i) + "," + toString(j),textWidth,textHeight);
			pos++;
		}
	}
	
	return true;
}

//draw is constantly being called by ArimaaGame
void HumanVisPlayer::draw(const ArimaaGame& a, const GameState& g){

    //placing pieces
    if(!g.getGameStarted()) {
        //piece and color are from superclass
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
    
    static bool b = initializeText();
    if(b) {
		int pos=0;
		for(int i=0;i<8;i++) {
			for(int j=0;j<8;j++) {
				glBindTexture( GL_TEXTURE_2D, textures[pos]);
				glBegin(GL_QUADS);
				glColor4f(1.0f,1.0f,1.0f,0.5f);
				glTexCoord2d(0.0,0.0); glVertex3f(i*50,j*50,0.5);
				glTexCoord2d(1.0,0.0); glVertex3f(i*50+textWidth,j*50,0.5);
				glTexCoord2d(1.0,1.0); glVertex3f(i*50+textWidth,j*50+textHeight,0.5);
				glTexCoord2d(0.0,1.0); glVertex3f(i*50,j*50+textHeight,0.5);
				glEnd();
				glBindTexture(GL_TEXTURE_2D,0);
				
				
				pos++;
			}
		}
	}
}
