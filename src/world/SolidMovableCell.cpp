//
// Created by ranch on 9/15/2024.
//

#include "SolidMovableCell.h"
int n1or1();

void SolidMovableCell::update(sf::Vector2i position, World& world)
{
    Cell* below_cell = world.get_cell(sf::Vector2i(position.x,position.y-1));
    if (below_cell->type == NOTHING)
    {
        world.switch_cell(position,sf::Vector2i(position.x,position.y-1));
    } else if (below_cell->type == LIQUID && below_cell->mass < mass)
    {
        world.switch_cell(position,sf::Vector2i(position.x,position.y-1));
    }
    else {
        bool l1 = world.get_cell(sf::Vector2i(position.x-1,position.y-1))->type == NOTHING || world.get_cell(sf::Vector2i(position.x-1,position.y-1))->type == LIQUID;
        bool r1 = world.get_cell(sf::Vector2i(position.x+1,position.y-1))->type == NOTHING || world.get_cell(sf::Vector2i(position.x+1,position.y-1))->type == LIQUID;

        bool left = l1 && (world.get_cell(sf::Vector2i(position.x-1,position.y))->type == NOTHING || world.get_cell(sf::Vector2i(position.x-1,position.y))->type == LIQUID);
        bool right = r1 && (world.get_cell(sf::Vector2i(position.x+1,position.y))->type == NOTHING || world.get_cell(sf::Vector2i(position.x+1,position.y))->type == LIQUID);
        if (left && right)
        {
            world.switch_cell(position,sf::Vector2i(position.x+n1or1(),position.y-1));
        } else if (left)
        {
            world.switch_cell(position,sf::Vector2i(position.x-1,position.y-1));
        } else if (right)
        {
            world.switch_cell(position,sf::Vector2i(position.x+1,position.y-1));
        }
    }
}
