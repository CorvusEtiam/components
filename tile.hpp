#ifndef TILE_DEFINITION_HPP
#define TILE_DEFINITION_HPP
#include <string>
#include <vector>
#include <iostream>

struct Tile {
    uint x; 
    uint y;
    std::string floor_tile;
    uint actor; 
    std::vector<uint> objects;
    bool passable; 
    bool visible;
    bool occupied; // by another actor
    bool taken;    // by some object
    
    Tile() {}
    Tile(uint _x, uint _y, std::string _floor, bool _pass, bool _vis) :
        x(_x),
        y(_y),
        floor_tile(_floor),
        passable(_pass),
        visible(_vis) {}   
#define BOOL_TO_STR(B) ((B) ? "true" : "false")
    friend std::ostream& operator<<(std::ostream& os, const Tile& t) {
        os << "X: " << t.x << " Y: " << t.y << " FLOOR: " << t.floor_tile << "\n";
        os << "vis: " << BOOL_TO_STR(t.visible) << "occ " << BOOL_TO_STR(t.occupied) << " pas: " << BOOL_TO_STR(t.passable); 
        return os; 
    }
#undef BOOL_TO_STR

};



#endif /* TILE_DEFINITION_HPP */