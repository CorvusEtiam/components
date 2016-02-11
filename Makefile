CPP=clang++
SFML=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=-Wpedantic -std=c++11 -g 
NAME=-o__NAME__
ENTITY=entitymanager.cpp entitycreator.cpp
GUI=./ui/resourcemanager.cpp ./ui/tilemap.cpp ./ui/gui.cpp

TARGET=util.cpp $(ENTITY) $(GUI) defs.cpp eventhandler.cpp component.cpp world.cpp game.cpp main.cpp

build: 
	$(CPP) $(FLAGS) -c $(TARGET) $(GUI) globals.hpp  
	$(CPP) $(patsubst %.cpp, %.o, $(TARGET)) -oapp $(SFML)
field:
	$(CPP) $(FLAGS) $(SFML) -oproblem problematic.cpp
clean:
	rm -r *.o 
	
	