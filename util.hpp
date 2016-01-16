#ifndef UTIL
#define UTIL
#include <stack>
#include <typeinfo>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>


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

struct GenerateId {
    private:
        uint id;
        std::stack<uint> freeId;
    public:
        GenerateId() { id = 0; }
        uint operator()() {
            if ( !freeId.empty() ) {
                auto val = freeId.top();
                freeId.pop();
                return val;
            } else {
                auto old = id;
                id += 1;
                return old;
            }
        }

        void operator()(uint _id) {
            freeId.push(_id);
        }
}; 




#define abstract /* abstract */
#define VDEST(CLS) ~CLS() {}

#endif /* UTIL */