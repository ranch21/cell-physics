//
// Created by ranch on 9/18/2024.
//

#include "Water.h"

Water::Water()
{
    color = color_offset(sf::Color(0,0,255), 20);
    id = WATER;
    temperature = 22;

}

void Water::step(sf::Vector2i position, World& world)
{

}
