#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "GameState.h"

class ArimaaGame;


class Player {
public:
	Player();
	virtual ~Player();
	
	virtual void setColor(const bool& b) = 0;
	virtual const bool& getColor() = 0;
	
	/**
	 * Gives the player the state and requests
	 * the player to place piece
	 * 
	 * At this time the GameState will only accept
	 * placement calls
	 */
	virtual void placePiece(GameState&) = 0;
	/**
	 * Gives the player the state and requests the 
	 * player to change the state
	 * 
	 * Game state only accepts valid moves
	 */
	virtual void doMove(GameState&) = 0;
	
	/**
	 * Called by ArimaaGame::handleEvent
	 * 
	 * Hands any human generated events to the player
	 */
	virtual void handleEvent(const GameState&,const SDL_Event&) {}
	
	/**
	 * Draw is for any additional drawing the player wishes to do
	 * examples: unit selected, visualizations
	 */
	virtual void draw(const ArimaaGame&,const GameState&) {}
	
private:
};


#endif
