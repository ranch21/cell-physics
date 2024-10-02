//
// Created by ranch on 9/17/2024.
//

#include "SolidImmovableCell.h"

void SolidImmovableCell::update(sf::Vector2i position, World& world)
{
    transfer_heat(position, world);
}
