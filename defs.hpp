#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "component.hpp"
#include "system.hpp"

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
  char code;
  
  Display() {}
  Display(sf::Color _b, sf::Color _f, char _c) {
    background = _b;
    foreground = _f;
    code = _c;
  }
 
  ~Display() {}
};

struct Floor   : public IComponent {
  bool passable;
  Floor() {}
  Floor(bool pass) : passable(pass) {}
  ~Floor() {}
    
};



class World;
struct Entity;
class DisplaySystem : public IDraw, public ISystem {
public:
    void draw(Entity& entity, char alter_code);
    void draw(Entity& entity);
    void update(Entity&);
};

class MovementSystem : public ISystem {
public:
    
    void update(Entity&) {return;}
    void update(Entity& entity, int dx, int dy);
};

class CollisionSystem : public ISystem {
public:
    void update(Entity&) {}
    bool check(Entity& entity, float x, float y);
};