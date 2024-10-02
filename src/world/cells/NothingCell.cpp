//
// Created by ranch on 9/17/2024.
//

#include "NothingCell.h"

NothingCell::NothingCell()
{
    mass = 0;
    color = sf::Color(0,0,0,0);
    type = NOTHING;
    temperature = 22;
    heat_conductivity = 0.0f;
}


void NothingCell::update(sf::Vector2i position, World& world)
{
}
