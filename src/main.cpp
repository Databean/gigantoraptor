#include "CApp.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "SDL.h"
#include "SDL_events.h"
#include "ArimaaGame.h"
#include "RandomPlayer.h"
#include "QueenAggressor.h"
#include "HumanPlayer.h"
#include "HumanVisPlayer.h"
#include "MinimaxPlayer.h"
#include <map>
#include <string>

using std::string;
using std::map;

Player* getPlayer(string name) {
	if(name=="minimax") { return new MinimaxPlayer(); }
	else if(name=="human") { return new HumanPlayer(); }
	else if(name=="humanvis") { return new HumanVisPlayer(); }
	else if(name=="random") { return new RandomPlayer(); }
	else if(name=="aggressor") { return new QueenAggressor(); }
	else { return NULL; }
}

int main(int argc,char** argv) {
	srand(time(NULL));
	if(argc < 3) { return 0; }
	
	Player* p1 = getPlayer(argv[1]);
	Player* p2 = getPlayer(argv[2]);
	ArimaaGame r(*p1,*p2);
	if(!r.init()) { return -1; }
	SDL_Event event;
	bool running = true;
	r.playGame();
	while(running) {
		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
				std::cout << "exiting" << std::endl;
				running=false;
				break;
			}
			r.handleEvent(event);
		}
		r.render();
		SDL_Delay(10);
	}

	r.haltGame();
	
	delete p1;
	delete p2;
}
