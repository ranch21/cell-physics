//
// Created by ranch on 9/18/2024.
//

#include "Water.h"

Water::Water()
{
    mass = 1.0;
    color = color_offset(sf::Color(0,0,255), 20);
    type = LIQUID;
    temperature = 22;
    heat_conductivity = 0.9f;
}

void Water::step(sf::Vector2i position, World& world)
{

}
