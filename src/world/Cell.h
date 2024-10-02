//
// Created by ranch on 9/7/2024.
//

#ifndef CELL_H
#define CELL_H
#include "cell_types.h"
#include "World.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

// 1 cell is cm big
class World;

class Cell {
public:
    virtual ~Cell() = default;
    sf::Color color;
    Cell_Type type;
    float mass; // g/cm3
    float temperature; // c
    bool updated = false;
    float heat_conductivity;// 0-1

    virtual void update(sf::Vector2i position, World& world) = 0;
    static sf::Color color_offset(sf::Color color, unsigned char amount);
    void transfer_heat(sf::Vector2i position, World& world);
};



#endif //CELL_H
