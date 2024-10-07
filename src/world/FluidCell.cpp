//
// Created by ranch on 9/18/2024.
//

#include "FluidCell.h"

int n1or1();

void FluidCell::update(sf::Vector2i position, World& world)
{
    transfer_heat(position, world);
    int d = direction * 2 - 1;
    if (get_cell_type(world.get_cell(sf::Vector2i(position.x,position.y-1))->id) == NOTHING)
    {
        world.switch_cell(position,sf::Vector2i(position.x,position.y-1));
    } else {
        bool can_move = get_cell_type(world.get_cell(sf::Vector2i(position.x+d,position.y))->id) == NOTHING;
        if (can_move)
        {
            if (get_cell_type(world.get_cell(sf::Vector2i(position.x+d,position.y-1))->id) == NOTHING) {
                world.switch_cell(position,sf::Vector2i(position.x+d,position.y-1));
            } else {
                world.switch_cell(position,sf::Vector2i(position.x+d,position.y));
            }
        } else
        {
            direction = !direction;
            d = direction * 2 - 1;
            can_move = get_cell_type(world.get_cell(sf::Vector2i(position.x+d,position.y))->id) == NOTHING;
            if (can_move)
            {
                world.switch_cell(position,sf::Vector2i(position.x+d,position.y));
            }
        }
    }
}
