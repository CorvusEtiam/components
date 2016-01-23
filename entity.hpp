#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once
#include "componentmanager.hpp"
#include "util.hpp"
#include "eventhandler.hpp"

class World;
struct Entity {
public:
  Entity() {}
  
  bool operator==(Entity& other) {
    return other.id == id;
  }
 
  EventHandler evmgr;
  ComponentManager cmgr;
  World * world;
  uint id;
  
};

#endif

