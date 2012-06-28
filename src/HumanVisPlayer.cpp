#include "HumanVisPlayer.h"
#include <SDL_opengl.h>
#include <gl.h>
#include "ArimaaGame.h"
#include <iostream>

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


}
