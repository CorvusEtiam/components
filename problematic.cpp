#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using Vector2D = std::vector<std::vector<int>>;

std::vector<std::string> split(std::string str, char sep) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> vec;
    while ( std::getline(ss, item, sep ) ) {
        if ( !item.empty() ) vec.push_back(item);
    }
    return vec;  
}

void loadMapFile(const std::string& path)
{
    Vector2D vec;
    std::ifstream file(path);
    if ( !file.good() ) return;
    std::string line;
    
    std::getline(file, line);
    auto header = split(line, ';');
    std::cout << header.size() << std::endl;
    auto width = std::stoi(header[0]);
    auto height = std::stoi(header[1]);
    std::cout << width << " " << height << std::endl;
    
    vec.resize(height);
    for ( auto& line : vec ) {
        line.resize(width);
    }
    
    int x = 0, y = 0;
    while ( std::getline(file, line) ) {
        auto item = split(line, ';');
        for ( auto chr : item ) {
            std::cout << chr << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    loadMapFile("media/simplemap.csv");
    return 0;
}
