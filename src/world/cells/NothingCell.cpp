//
// Created by ranch on 9/17/2024.
//

#include "NothingCell.h"

#include <iostream>

NothingCell::NothingCell()
{
    color = sf::Color(0,0,0,0);
    id = AIR;
    temperature = 22;
}


void NothingCell::update(sf::Vector2i position, World& world)
{

}
