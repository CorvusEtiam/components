CPP=g++
SFML=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=-Wpedantic -std=c++1y -g 
NAME=-o__NAME__
TARGET=resourcemanager.cpp tilemap.cpp ../util.cpp gui.cpp
build: 
	$(CPP) $(FLAGS) -c $(TARGET)  
	$(CPP) $(FLAGS) $(patsubst %.cpp, %.o, $(TARGET))  guitest.cpp -oapp $(SFML)


clean:
	rm -r *.o