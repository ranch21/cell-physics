//
// Created by ranch on 9/17/2024.
//

#include "Sand.h"

Sand::Sand()
{
    color = color_offset(sf::Color(240,240,10), 30);
    id = SAND;
    temperature = 22;
}

void Sand::step(sf::Vector2i position, World& world)
{

}
