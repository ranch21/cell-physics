//
// Created by ranch on 9/17/2024.
//

#include "Barrier.h"

Barrier::Barrier()
{
    mass = 9999;
    color = color_offset(sf::Color(20,20,20), 5);
    type = SOLID_IMMOVABLE;
    temperature = 22;
    heat_conductivity = 0.0f;
}

void Barrier::step(sf::Vector2i position, World& world)
{
    //temperature = 22;
}
