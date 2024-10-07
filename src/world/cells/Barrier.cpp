//
// Created by ranch on 9/17/2024.
//

#include "Barrier.h"

Barrier::Barrier()
{
    color = color_offset(sf::Color(20,20,20), 5);
    id = BARRIER;
    temperature = 22;
}

void Barrier::step(sf::Vector2i position, World& world)
{
    //temperature = 22;
}
