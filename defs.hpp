#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "component.hpp"
#include "system.hpp"

typedef bool trait;

struct Position : public IComponent {
    std::size_t id;
    int x;
    int y;
    
    Position(int _x, int _y) : x(_x), y(_y) {}
    Position() {
      x = 0;
      y = 0;
    }    

    ~Position() {}
};

struct Display : public IComponent {
  sf::Color background;
  sf::Color foreground;
  std::string sprite_name;
  
  Display() {}
  Display(sf::Color _b, sf::Color _f, std::string _s) {
    background = _b;
    foreground = _f;
    sprite_name = _s;
  }
 
  ~Display() {}
};

struct Floor   : public IComponent {
  bool passable;
  Floor() {}
  Floor(bool pass) : passable(pass) {}
  ~Floor() {}
    
};

struct Description : public IComponent {
    std::string name;
    Description() {}
    Description(std::string s) { name = s; }
    ~Description() {}
    
};

struct Item : public IComponent {
    bool pickable;
    bool dropable;
    bool sellable;
    uint price;
    
    Item() {}
    Item(bool pick = true, bool drop = true, bool sell = false, uint prc = 0 ) {
        pickable = pick; // can be picked
        dropable = drop; // can be dropped
        sellable = sell; // can be bought and sold
        price    = prc;
    }
    ~Item() {}
};

struct Storage : public IComponent {
    std::vector<uint> items;
    uint maxitem;
    Storage() {}
    
    Storage(uint max, std::vector<uint> it) {
        maxitem = max;
        items = it;
    }
    
    Storage(uint max) {
        maxitem = max;
    }
    
    ~Storage() {}
}; 



class World;
struct Entity;

class DisplaySystem : public IDraw, public ISystem {
public:
    void draw(Entity* entity);
    void update(Entity*);
};

class MovementSystem : public ISystem {
public:
    
    void update(Entity*) {return;}
    void update(Entity* entity, int dx, int dy);
};

class CollisionSystem : public ISystem {
public:
    void update(Entity*) {}
    bool check(Entity* entity, uint x, uint y);
};



class InventorySystem : public ISystem, IDraw {
public:
    void draw(Entity* ) {}
    void update(Entity*) {}
      
    void take(Entity* entity, Entity* object, sf::Vector2i coord);
    void drop(Entity* entity, Entity * object, sf::Vector2i coord); 
private:
    void _displayMsg(std::vector<uint> data, uint width, uint height, uint x, uint y);
    
}; 
