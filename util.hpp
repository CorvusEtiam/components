#ifndef UTIL
#define UTIL
#include <stack>
#include <typeinfo>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

using Vector2d = std::vector< std::vector < uint > >;

typedef uint uint32_t;

inline std::size_t getUniqId() noexcept {
  static std::size_t lastID{0};
  return lastID++;
}

template<typename T>
inline std::size_t getTypeId() noexcept {
  static std::size_t typeId{ getUniqId() };
  return typeId;
}

std::vector<std::string> split(std::string str, char sep); 
    

#endif /* UTIL */
