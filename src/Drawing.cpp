#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
//#include "world/cell_types.h"
#include "world/World.h"
//
// Created by ranch on 10/2/24.
//
void draw_shapes(sf::RenderWindow& window, World& world)
{
    sf::RectangleShape cell_shape(sf::Vector2f(1,1));
    cell_shape.setOrigin(0.5,0.5);;
    for (int columnid = 0; columnid < world.size.x; columnid++)
    {
        for (int cellid = 0; cellid < world.size.y; cellid++)
        {
            if (get_cell_type(world.cells[columnid][cellid]->id) == 3) {continue;}

            //srand(cellid);
            cell_shape.setPosition(columnid, -cellid);
            //cell_shape.setFillColor(sf::Color(rand() % 255, rand()%255, rand()%255));
            sf::Color color = world.cells[columnid][cellid]->color;
            //sf::Color color = sf::Color::Black;
            color.r = std::clamp(color.r + (static_cast<int>(world.cells[columnid][cellid]->temperature) - 22) / 10,0,255);
            //color.g = std::clamp(color.r - (static_cast<int>(this->cells[columnid][cellid]->temperature) + 22) / 10,0,255);
            //color.b = std::clamp(color.r - (static_cast<int>(this->cells[columnid][cellid]->temperature) + 22) / 10,0,255);
            cell_shape.setFillColor(color);
            window.draw(cell_shape);


            //if (this->cells[columnid][cellid]->type == NOTHING) {continue;}
        }
    }
}

void draw_texture(sf::RenderWindow& window, World& world)
{
    sf::Texture texture;
    texture.create(world.size.x,world.size.y);
    sf::Image image = texture.copyToImage();

    for (int columnid = 0; columnid < world.size.x; columnid++)
    {
        for (int cellid = 0; cellid < world.size.y; cellid++)
        {
            //if (world.cells[columnid][cellid]->type == 3) {continue;}

            sf::Color color = world.cells[columnid][cellid]->color;
            color.r = std::clamp(color.r + (static_cast<int>(world.cells[columnid][cellid]->temperature) - 22) / 10,0,255);

            image.setPixel(columnid, cellid, color);
        }
    }
    image.flipVertically();
    texture.loadFromImage(image);
    sf::RectangleShape texture_rect(sf::Vector2f(world.size.x,world.size.y));
    texture_rect.setPosition(-0.5,-world.size.y + 0.5);
    texture_rect.setTexture(&texture);
    window.draw(texture_rect);
}