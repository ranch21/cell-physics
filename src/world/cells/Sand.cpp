//
// Created by ranch on 9/17/2024.
//

#include "Sand.h"

Sand::Sand()
{
    mass = 1.631;
    color = color_offset(sf::Color(240,240,10), 30);
    type = SOLID_MOVABLE;
    temperature = 22;
    heat_conductivity = 0.1f;
}

void Sand::step(sf::Vector2i position, World& world)
{

}
