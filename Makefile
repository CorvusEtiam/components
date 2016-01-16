CPP=clang++
SFML=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=-Wall -std=c++11 -g 
NAME=-o__NAME__
TARGET=defs.cpp component.cpp world.cpp game.cpp main.cpp
build: 
	$(CPP) $(FLAGS) -c $(TARGET) 
	$(CPP) $(NAME:__NAME__=app) $(patsubst %.cpp, %.o, $(TARGET)) $(SFML) 
	

	