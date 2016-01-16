#pragma once
#include <utility>
#include <type_traits>
#include "component.hpp"
#include "util.hpp"



using CompArray = std::bitset<MAX_COMPONENT>;
class ComponentManager {
public:
  template<typename T, typename... Args>
  ComponentManager& createComponent(Args&&... args) {
    if ( std::is_base_of<IComponent, T>() ) {
        comp[getTypeId<T>()] = new T(std::forward<Args>(args)...);
        compFlags[getTypeId<T>()].flip();
    }
    return *this;
  }
  
  template<typename T>
  void removeComponent() {
    comp.erase(comp.find(getTypeId<T>()));
    compFlags[getTypeId<T>()].flip();
  }
  
  
  template<typename T>
  T* getComponent() {
    return static_cast<T*>(comp[getTypeId<T>()]);
  }

  template<typename T>
  bool hasComponent() { 
    return compFlags[getTypeId<T>()]; 
  }
  
private:
  std::map<std::size_t, IComponent*> comp;
   CompArray compFlags;
  
};
