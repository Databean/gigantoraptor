CC := g++
INCLUDES := -I/usr/include/GL/ -I/usr/include/SDL/ -I$(INCL_HOME)
CFLAGS := -Wall -c $(INCLUDES)
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

main: $(OBJECTS)
	

%.o: %.cpp
	g++ $(CFLAGS) $< -o $(OBJ_HOME)/$@ -g



.PHONY: clean
clean:
	rm *.o