#ifndef HUMAN_VIS_PLAYER
#define HUMAN_VIS_PLAYER

#include "HumanPlayer.h"

class HumanVisPlayer : public HumanPlayer {
public:
    
    virtual void draw(const ArimaaGame&, const GameState&);

};
#endif



