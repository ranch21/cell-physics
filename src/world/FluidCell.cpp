//
// Created by ranch on 9/18/2024.
//

#include "FluidCell.h"

int n1or1();

void FluidCell::update(sf::Vector2i position, World& world)
{
    transfer_heat(position, world);
    int d = direction * 2 - 1;
    if (world.get_cell(sf::Vector2i(position.x,position.y-1))->type == NOTHING)
    {
        world.switch_cell(position,sf::Vector2i(position.x,position.y-1));
    } else {
        bool can_move = world.get_cell(sf::Vector2i(position.x+d,position.y))->type == NOTHING;
        //bool right = world.get_cell(sf::Vector2i(position.x+1,position.y))->type == NOTHING;
        if (can_move)
        {
            world.switch_cell(position,sf::Vector2i(position.x+d,position.y));
        } else
        {
            direction = !direction;
            d = direction * 2 - 1;
            can_move = world.get_cell(sf::Vector2i(position.x+d,position.y))->type == NOTHING;
            if (can_move)
            {
                world.switch_cell(position,sf::Vector2i(position.x+d,position.y));
            }
        }
    }
}
