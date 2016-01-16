#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once
#include "componentmanager.hpp"
#include "util.hpp"

static GenerateId generator;
class World;
struct Entity {
public:
  Entity() {
    id = generator();
  }
  
  ~Entity() {
    generator(id);
  }
 
  
  
  
  bool operator==(Entity& other) {
    return other.id == id;
  }
  
  ComponentManager cmgr;
  World * world;
  uint id;
  
};

#endif

