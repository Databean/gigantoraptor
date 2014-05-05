export CC := g++
LINK_FILES := -lGL -lGLU -lSDL -lSDL_image -lSDL_ttf -Wl,-R/usr/lib/
export OBJ_HOME = $(realpath obj)
export INCL_HOME = $(realpath include)
EXECUTABLE := gigantoraptor

$(EXECUTABLE): $(wildcard src/*) $(wildcard include/*)
	cd src && $(MAKE)
	$(CC) -Wall obj/*.o -o $(EXECUTABLE) $(LINK_FILES) 

.PHONY: clean
clean: 
	rm -f obj/*.o
	rm -f $(EXECUTABLE)
