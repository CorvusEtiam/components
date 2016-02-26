#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once
#include "componentmanager.hpp"
#include "util.hpp"
#include "eventhandler.hpp"
#include <unordered_map>
#include <string>
enum class Kind {
    Item,
    Actor,
    Obstacle,
    Player,
    Floor
};


class World;
struct Entity {
public:
  Entity() {}
  
  bool operator==(Entity& other) {
    return other.id == id;
  }
  bool haveTrait(std::string s) noexcept {
    if ( flags.find(s) != flags.end() ) {
      return flags[s];
    } else {
      return false;
    }
  } 
  
  std::unordered_map<std::string, bool> flags;
  Kind kind;
  EventHandler evmgr;
  ComponentManager cmgr;
  World * world;
  uint id;
  
};

#endif

