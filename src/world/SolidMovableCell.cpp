//
// Created by ranch on 9/15/2024.
//

#include "SolidMovableCell.h"
int n1or1();

void SolidMovableCell::update(sf::Vector2i position, World& world)
{
    Cell* below_cell = world.get_cell(sf::Vector2i(position.x,position.y-1));
    if (get_cell_type(below_cell->id) == NOTHING)
    {
        world.switch_cell(position,sf::Vector2i(position.x,position.y-1));
    } else if (get_cell_type(below_cell->id) == LIQUID && get_mass(below_cell->id) < get_mass(this->id))
    {
        world.switch_cell(position,sf::Vector2i(position.x,position.y-1));
    }
    else {
        bool l1 = get_cell_type(world.get_cell(sf::Vector2i(position.x-1,position.y-1))->id) == NOTHING || get_cell_type(world.get_cell(sf::Vector2i(position.x-1,position.y-1))->id) == LIQUID;
        bool r1 = get_cell_type(world.get_cell(sf::Vector2i(position.x+1,position.y-1))->id) == NOTHING || get_cell_type(world.get_cell(sf::Vector2i(position.x+1,position.y-1))->id) == LIQUID;

        bool left = l1 && (get_cell_type(world.get_cell(sf::Vector2i(position.x-1,position.y))->id) == NOTHING || get_cell_type(world.get_cell(sf::Vector2i(position.x-1,position.y))->id) == LIQUID);
        bool right = r1 && (get_cell_type(world.get_cell(sf::Vector2i(position.x+1,position.y))->id) == NOTHING || get_cell_type(world.get_cell(sf::Vector2i(position.x+1,position.y))->id) == LIQUID);
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
