CPP=clang++
SFML=-lsfml-window -lsfml-graphics -lsfml-system
FLAGS=-Wpedantic -std=c++11 -g 
NAME=-o__NAME__


GUI=./ui/resourcemanager.cpp ./ui/tilemap.cpp ./ui/layer.cpp ./ui/engine.cpp util.cpp
TARGET=entitymanager.cpp entitycreator.cpp component.cpp defs.cpp world.cpp game.cpp util.cpp

build:
	$(CPP) $(FLAGS) -c $(GUI)
	$(CPP) $(FLAGS) -c $(TARGET) 
	@mv *.o ./out
	$(CPP) $(FLAGS) -oapp ./out/*.o main.cpp $(SFML)

field:
	$(CPP) $(FLAGS) $(SFML) -oproblem problematic.cpp
clean:
	rm -r *.o 
	
	
