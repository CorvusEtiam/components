CPP=clang++
SFML=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=-Wpedantic -std=c++11 -g 
NAME=-o__NAME__
TARGET=gui.cpp 
build: 
	$(CPP) $(FLAGS) -c $(TARGET)  
	$(CPP) $(FLAGS) $(patsubst %.cpp, %.o, $(TARGET)) guitest.cpp -oapp $(SFML)


