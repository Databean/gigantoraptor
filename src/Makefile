INCLUDES := -I/usr/include/GL/ -I/usr/include/SDL/ -I$(INCL_HOME)
CFLAGS := -Wall -c $(INCLUDES) -O2 -std=c++11 -Wall
SOURCES := $(wildcard *.cpp)
OBJECTS := $(addprefix $(OBJ_HOME)/,$(SOURCES:.cpp=.o))

main: $(OBJECTS)
	

$(OBJ_HOME)/%.o: %.cpp
	g++ $(CFLAGS) $< -o $@ -g


.PHONY: clean
clean:
	rm *.o