CPP=clang++
SFML=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=-Wpedantic -std=c++11 -g 
NAME=-o__NAME__
TARGET=entitymanager.cpp entitycreator.cpp eventhandler.cpp defs.cpp component.cpp world.cpp game.cpp main.cpp
build: 
	$(CPP) $(FLAGS) -c $(TARGET) 
	$(CPP) $(patsubst %.cpp, %.o, $(TARGET)) -oapp $(SFML) 
	

field:
	$(CPP) $(FLAGS) $(SFML) -oproblem problematic.cpp
