CC := g++
LINK_FILES := -lGL -lGLU -lSDL -lSDL_image -lSDL_ttf -Wl,-R/usr/lib/
export OBJ_HOME = $(realpath obj)
export INCL_HOME = $(realpath include)
EXECUTABLE := main

.PHONY: main
main: 
	cd src && $(MAKE)
	$(CC) -Wall obj/*.o -o gigantoraptor $(LINK_FILES) 

.PHONY: clean
clean: 
	rm -f obj/*.o
	rm -f $(EXECUTABLE)
