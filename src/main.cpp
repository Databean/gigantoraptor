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

int main() {
	srand(time(NULL));
	HumanPlayer p1;
	HumanPlayer p2;
	ArimaaGame r(p1,p2);
	if(!r.init()) { return -1; }
	SDL_Event event;
	bool running = true;
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
}