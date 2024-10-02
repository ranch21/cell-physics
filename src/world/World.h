//
// Created by ranch on 9/7/2024.
//

#ifndef CHUNK_H
#define CHUNK_H
#include <cmath>
#include <memory>
#include <vector>

#include "Cell.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

class Cell;

class World {
    public:
    Cell*** cells;
    sf::Vector2i size;


    World(unsigned int width, unsigned int height);

    static std::vector<sf::Vector2i> shortest_path(sf::Vector2i start, sf::Vector2i end);
    static std::vector<sf::Vector2i> surrounding(sf::Vector2i pos);
    Cell* get_cell(sf::Vector2i pos);
    void set_cell(sf::Vector2i pos, Cell* cell);
    void switch_cell(sf::Vector2i p1,sf::Vector2i p2);
    void draw(sf::RenderWindow& window);
    ~World();
};



#endif //CHUNK_H
