//
// Created by ranch on 9/7/2024.
//

#include "World.h"

#include <cmath>
#include <memory>

#include "cells/Barrier.h"
#include "cells/NothingCell.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

World::World(unsigned int width, unsigned int height)
{
    size = sf::Vector2i(width,height);

    cells = new Cell**[width];

    for (int i = 0; i < width; i++) {
        cells[i] = new Cell*[height];
    }

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            this->cells[x][y] = new NothingCell();



            if (x == width - 1 || x == 0 || y == height - 1 || y == 0)
            {
                this->cells[x][y] = new Barrier();
            }
        }
    }
}

std::vector<sf::Vector2i> World::shortest_path(sf::Vector2i start, sf::Vector2i end)
{
    std::vector<sf::Vector2i> out;

    int dx = end.x - start.x;
    int dy = end.y - start.y;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float x_increment = static_cast<float>(dx) / steps;
    float y_increment = static_cast<float>(dy) / steps;

    auto x = static_cast<float>(start.x);
    auto y = static_cast<float>(start.y);

    for (int i = 0; i < steps; ++i) {
        x += x_increment;
        y += y_increment;
        out.emplace_back(std::round(x), std::round(y));
    }
    return out;
}

/*void World::draw(sf::RenderWindow& window)
{
    sf::RectangleShape cell_shape(sf::Vector2f(1,1));
    cell_shape.setOrigin(0.5,0.5);
    int world_size = std::end(this->cells) - std::begin(this->cells);
    for (int columnid = 0; columnid < world_size; columnid++)
    {
        //int16_t start = 0;
        //int16_t len = 0;
        //sf::Color prevCol = sf::Color(5,5,5);
        //sf::Color prevCol2 = sf::Color(5,5,5);
        for (int cellid = 0; cellid < world_size; cellid++)
        {

            if (this->cells[columnid][cellid]->color != prevCol)
            {
                srand(cellid);
                len = cellid - start;
                prevCol = this->cells[columnid][cellid]->color;
                cell_shape.setPosition(columnid, -start - len);
                cell_shape.setSize(sf::Vector2f(1,len));
                start = cellid;
                cell_shape.setFillColor(sf::Color(rand() % 255, rand()%255, rand()%255));
                cell_shape.setFillColor(prevCol2);
                window.draw(cell_shape);
            }
            prevCol2 = cells[columnid][cellid]->color;
            //if (this->cells[columnid][cellid]->type == NOTHING) {continue;}
        }
    }

}*/

void World::draw(sf::RenderWindow& window)
{
    sf::RectangleShape cell_shape(sf::Vector2f(1,1));
    cell_shape.setOrigin(0.5,0.5);;
    for (int columnid = 0; columnid < size.x; columnid++)
    {
        for (int cellid = 0; cellid < size.y; cellid++)
        {
            if (this->cells[columnid][cellid]->type == NOTHING) {continue;}

            //srand(cellid);
            cell_shape.setPosition(columnid, -cellid);
            //cell_shape.setFillColor(sf::Color(rand() % 255, rand()%255, rand()%255));
            sf::Color color = this->cells[columnid][cellid]->color;
            //sf::Color color = sf::Color::Black;
            color.r = std::clamp(color.r + (static_cast<int>(this->cells[columnid][cellid]->temperature) - 22) / 10,0,255);
            //color.g = std::clamp(color.r - (static_cast<int>(this->cells[columnid][cellid]->temperature) + 22) / 10,0,255);
            //color.b = std::clamp(color.r - (static_cast<int>(this->cells[columnid][cellid]->temperature) + 22) / 10,0,255);
            cell_shape.setFillColor(color);
            window.draw(cell_shape);


            //if (this->cells[columnid][cellid]->type == NOTHING) {continue;}
        }
    }

}

std::vector<sf::Vector2i> World::surrounding(sf::Vector2i pos)
{
    std::vector<sf::Vector2i> out;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (i != 0 && j != 0) {out.emplace_back(sf::Vector2i(pos.x+j,pos.y+i));}
        }
    }
}

Cell* World::get_cell(sf::Vector2i pos)
{
    pos.x = std::clamp(pos.x, 0, size.x-1);
    pos.y = std::clamp(pos.y, 0, size.y-1);

    return cells[pos.x][pos.y];
}

void World::set_cell(sf::Vector2i pos, Cell* cell)
{
    pos.x = std::clamp(pos.x, 0, size.x-1);
    pos.y = std::clamp(pos.y, 0, size.y-1);

    cells[pos.x][pos.y] = cell;
}

void World::switch_cell(sf::Vector2i p1, sf::Vector2i p2)
{
    auto cell2copy = get_cell(p2);
    set_cell(p2, get_cell(p1));
    set_cell(p1,cell2copy);
}


World::~World()
{
    // Properly delete all allocated Cell objects
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            delete cells[i][j];
        }
    }
}
