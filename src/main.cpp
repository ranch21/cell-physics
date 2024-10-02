#include <iostream>
#include <SFML/Graphics.hpp>
#include "world/World.h"
#include "world/cells/Barrier.h"
#include "world/cells/Metal.h"
#include "world/cells/NothingCell.h"
#include "world/cells/Sand.h"
#include "world/cells/Water.h"

#define SIM_WIDTH 25
#define SIM_HEIGHT 25
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define TPS 35

void eventloop(sf::RenderWindow& window);
int get_selected_key(int selected);
void update(World& world);
void render(sf::RenderWindow& window, World& world);
void spawn_cells(World& world, sf::Vector2i mpos, sf::Vector2i pmpos, int size, sf::View& view, int& selected);
sf::Vector2i get_mouse_pos(sf::RenderWindow& window);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(240);
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    unsigned int tps = TPS;
    unsigned long tick = 0;
    int selected = 0;
    int size = 1;
    sf::Event event;

    auto world = new World(SIM_WIDTH,SIM_HEIGHT);
    sf::View view(sf::FloatRect(-0.5, -SIM_HEIGHT + 0.5, SIM_WIDTH, SIM_HEIGHT));
    window.setView(view);

    auto prevmpos = sf::Vector2i(0,0);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            } else if (event.type == sf::Event::MouseWheelScrolled)
            {
                size += event.mouseWheelScroll.delta;
                if (size < 1) {size = 1;}
            }
        }
        selected = get_selected_key(selected);


        auto mousepos = get_mouse_pos(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {spawn_cells(*world, mousepos, prevmpos, size, view, selected);}
        prevmpos = mousepos;
        float spt = 1.0f / tps;
        float elapsed = clock.getElapsedTime().asSeconds();
        if (elapsed > spt)
        {
            for (int i = 1; spt * i < elapsed; ++i)
            {
                update(*world);
            }
            clock.restart();
        }
        render(window, *world);
        tick++;
    }

    return 0;
}

int get_selected_key(int selected) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) return 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) return 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) return 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) return 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) return 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) return -1;
    return selected;
}


sf::Vector2i get_mouse_pos(sf::RenderWindow& window)
{
    sf::Vector2f mousepos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    mousepos.y = -mousepos.y;
    mousepos.x /= WINDOW_WIDTH;
    mousepos.y /= WINDOW_HEIGHT;
    mousepos.x *= SIM_WIDTH;
    mousepos.y *= SIM_HEIGHT;
    mousepos.y += SIM_HEIGHT;
    mousepos.x = std::clamp(mousepos.x, 1.0f, SIM_WIDTH -2.0f);
    mousepos.y = std::clamp(mousepos.y, 1.0f, SIM_HEIGHT -2.0f);
    return static_cast<sf::Vector2i>(mousepos);
}

void spawn_cells(World& world, sf::Vector2i mpos, sf::Vector2i pmpos, int size, sf::View& view, int& selected)
{
    std::vector<sf::Vector2i> path = World::shortest_path(pmpos, mpos);
    path.emplace_back(mpos);
    for (auto pos : path)
    {
        Cell* cell;

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (selected == 2) {cell = new Water();}
                else if (selected == 3) {cell = new Barrier();}
                else if (selected == 4) {cell = new NothingCell();}
                else if (selected == 5) {cell = new Metal();}
                else if (selected == -1) {
                    cell = world.cells[std::clamp(pos.x+i - size/2, 1 ,SIM_WIDTH -2 )][(std::clamp(pos.y+j - size/2, 1 ,SIM_HEIGHT - 2))];
                    cell->temperature += 0.5f;
                }
                else {cell = new Sand();}

                world.cells[std::clamp(pos.x+i - size/2, 1 ,SIM_WIDTH - 2)][std::clamp(pos.y+j - size/2, 1 ,SIM_HEIGHT - 2)] = cell;
                //std::cout << pos.y << std::endl;
                //world.cells[std::clamp(pos.x+i - size/2, 2 ,SIM_WIDTH - 1)][pos.y+j - size/2] = cell;
            }
        }
    }
}

void update(World& world)
{
    int ix[SIM_WIDTH];
    int iy[SIM_HEIGHT];


    for (int i = 0; i < SIM_WIDTH; ++i)
    {
        ix[i]=i;
    }
    for (int i = 0; i < SIM_HEIGHT; ++i)
    {
        iy[i]=i;
    }

    size_t i;
    for (i = 0; i < SIM_WIDTH - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (SIM_WIDTH - i) + 1);
        int t = ix[j];
        ix[j] = ix[i];
        ix[i] = t;
    }
    for (i = 0; i < SIM_HEIGHT - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (SIM_HEIGHT - i) + 1);
        int t = iy[j];
        iy[j] = iy[i];
        iy[i] = t;
    }
    //for (i = 0; i < 255 - 1; i++)
    //{
    //    size_t j = i + rand() / (RAND_MAX / (255 - i) + 1);
    //    int t = iy[j];
    //    iy[j] = iy[i];
    //    iy[i] = t;
    //}


    for (int i = 0; i < SIM_WIDTH; ++i)
    {
        for (int j = 0; j < SIM_HEIGHT ; ++j)
        {
            sf::Vector2i pos = sf::Vector2i(ix[i],iy[j]);
            //std::cout << pos.x << ", " << pos.y << std::endl;
            Cell* cell = world.get_cell(pos);
            if (!cell->updated) {cell->update(pos, world);}
            cell->updated = true;
        }
    }

    for (int i = 0; i < SIM_WIDTH; ++i)
    {
        for (int j = 0; j < SIM_HEIGHT; ++j)
        {
            world.get_cell(sf::Vector2i(i,j))->updated = false;
        }
    }
}

void render(sf::RenderWindow& window, World& world)
{
    window.clear();
    world.draw(window);
    window.display();
}


// #include <SFML/Graphics.hpp>

// #include "world/World.h"

// int main()
// {
//     auto window = sf::RenderWindow{ { 1000u, 1000u }, "CMake SFML Project" };
//     window.setFramerateLimit(144);

//     auto world = new World();
//     sf::View view(sf::FloatRect(-0.5, -254.5, 255, 255));
//     window.setView(view);

//     while (window.isOpen())
//     {
//         for (auto event = sf::Event{}; window.pollEvent(event);)
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//         }

//         for (int i = 0; i < 255; ++i)
//         {
//             for (int j = 0; j < 255; ++j)
//             {
//                 world->cells[i][j]->update(sf::Vector2i(i,j), *world);
//             }
//         }

//         window.clear();
//         world->draw(window);
//         window.display();
//     }
// }
