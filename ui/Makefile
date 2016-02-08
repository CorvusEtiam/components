CPP=g++
SFML=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=-Wpedantic -std=c++1y -g 
NAME=-o__NAME__
TARGET=gui.cpp resourcemanager.cpp
build: 
	$(CPP) $(FLAGS) -c $(TARGET)  
	$(CPP) $(FLAGS) $(patsubst %.cpp, %.o, $(TARGET)) guitest.cpp -oapp $(SFML)


clean:
	rm -r *.o