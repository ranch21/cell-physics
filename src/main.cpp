#include <chrono>
#include <cstring>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "world/World.h"
#include "world/cells/Barrier.h"
#include "world/cells/Metal.h"
#include "world/cells/NothingCell.h"
#include "world/cells/Sand.h"
#include "world/cells/Water.h"

#define SIM_WIDTH (40 + 2)
#define SIM_HEIGHT (40 + 2)
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define TPS 35

enum DrawMode {
    SHAPES,
    TEXTURE
};

struct Sim_Data {
    int w;
    int h;
    int tps;
};

struct Window_Data {
    int w;
    int h;
};

struct Start_Data {
    Sim_Data s;
    Window_Data w;
};

void eventloop(sf::RenderWindow& window);
int get_selected_key(int selected);
void update(World& world, Sim_Data s);
void render(sf::RenderWindow& window, World& world, DrawMode mode);
void spawn_cells(World& world, sf::Vector2i mpos, sf::Vector2i pmpos, int size, int& selected, Sim_Data s);
sf::Vector2i get_mouse_pos(sf::RenderWindow& window, Start_Data sd);
void draw_shapes(sf::RenderWindow& window, World& world);
void draw_texture(sf::RenderWindow& window, World& world);
void save(World& world, std::string filename);
void main_loop(Start_Data sd, World &world);
void print_help();
World load(std::string filename);

int main(int argc, char *argv[])
{
    Start_Data sd;
    Sim_Data s;
    s.w = SIM_WIDTH;
    s.h = SIM_HEIGHT;
    s.tps = TPS;
    Window_Data w;
    w.w = WINDOW_WIDTH;
    w.h = WINDOW_HEIGHT;
    sd.s = s;
    sd.w = w;

    bool loaded = false;
    bool adjustp = false;
    int pval = 0;
    std::string filename = "";

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            char* arg = argv[i];
            if (arg[0] == '-' && argc > i+1) {
                char* p;
                if (argv[i+1][0] != '-') {
                    int val = strtol(argv[i+1],&p,10);
                    val = std::max(val,1);
                    switch (arg[1]) {
                        case 'x':
                            sd.s.w = val + 2;
                            break;
                        case 'y':
                            sd.s.h = val + 2;
                            break;
                        case 't':
                            sd.s.tps = val;
                            break;
                        case 'X':
                            sd.w.w = val;
                            break;
                        case 'Y':
                            sd.w.h = val;
                            break;
                        case 'p':
                            sd.w.h = sd.s.h * val;
                            sd.w.w = sd.s.w * val;
                            adjustp = true;
                            pval = val;
                            break;
                        case 'h':
                            print_help();
                            return 0;
                            break;
                        case 'l':
                            filename = argv[i+1];
                            loaded = true;
                            break;
                        default:
                            std::cout << "Invalid Argument \"" << arg << "\"" << "\n";
                            std::cout << "Use -h to get a list of available arguments" << "\n";
                            return 1;
                            break;
                    }
                }
            }
        }
    }



    if (!loaded) {
        auto world = new World(sd.s.w,sd.s.h);
        main_loop(sd, *world);
    } else {
        auto world = load(filename);
        sd.s.w = world.size.x;
        sd.s.h = world.size.y;
        if (adjustp) {
            sd.w.h = sd.s.h * pval;
            sd.w.w = sd.s.w * pval;
        }
        main_loop(sd, world);
    }

    return 0;
}

void print_help() {
    std::cout << "Available arguments:" << "\n"
    << "-x: Sets simulation width" << "\n"
    << "-y: Sets simulation height" << "\n"
    << "-t: Sets simulation ticks per second" << "\n"
    << "-X: Sets window width" << "\n"
    << "-Y: Sets window height" << "\n"
    << "-p: Sets pixels per cell, overrides previous window width and height parameters" << "\n"
    << "-h: Prints available parameters and quits" << "\n";
}

void main_loop(Start_Data sd, World &world) {
    sf::RenderWindow window(sf::VideoMode(sd.w.w, sd.w.h), "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(240);
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    unsigned int tps = sd.s.tps;
    unsigned long tick = 0;
    int selected = 0;
    int size = 1;
    sf::Event event;

    sf::View view(sf::FloatRect(-0.5, -sd.s.h + 0.5, sd.s.w, sd.s.h));
    window.setView(view);

    auto prevmpos = sf::Vector2i(0,0);

    while (window.isOpen() && selected != -11)
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
        auto mousepos = get_mouse_pos(window, sd);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selected > -10) {spawn_cells(world, mousepos, prevmpos, size, selected, sd.s);}
        if (selected == -10) {
            save(world, "test");
            selected = 1;
        }
        prevmpos = mousepos;
        float spt = 1.0f / tps;
        float elapsed = clock.getElapsedTime().asSeconds();
        if (elapsed > spt)
        {
            for (int i = 1; spt * i < elapsed; ++i)
            {
                update(world, sd.s);
            }
            clock.restart();
        }
        render(window, world, TEXTURE);
        tick++;
    }
}

int get_selected_key(int selected) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) return 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) return 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) return 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) return 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) return 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) return 6;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) return -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) return -10;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) return -11;
    return selected;
}


sf::Vector2i get_mouse_pos(sf::RenderWindow& window, Start_Data sd)
{
    sf::Vector2f mousepos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    mousepos.y = -mousepos.y;
    mousepos.x /= sd.w.w;
    mousepos.y /= sd.w.h;
    mousepos.x *= sd.s.w;
    mousepos.y *= sd.s.h;
    mousepos.y += sd.s.h;
    mousepos.x = std::clamp(mousepos.x, 1.0f, sd.s.w -2.0f);
    mousepos.y = std::clamp(mousepos.y, 1.0f, sd.s.h -2.0f);
    return static_cast<sf::Vector2i>(mousepos);
}

void spawn_cells(World& world, sf::Vector2i mpos, sf::Vector2i pmpos, int size, int& selected, Sim_Data s)
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
                    cell = world.cells[std::clamp(pos.x+i - size/2, 1 ,s.w -2 )][(std::clamp(pos.y+j - size/2, 1 ,s.h - 2))];
                    cell->temperature += 0.5f;
                }
                else {cell = new Sand();}

                world.cells[std::clamp(pos.x+i - size/2, 1 ,s.w - 2)][std::clamp(pos.y+j - size/2, 1 ,s.h - 2)] = cell;
                //std::cout << pos.y << std::endl;
                //world.cells[std::clamp(pos.x+i - size/2, 2 ,SIM_WIDTH - 1)][pos.y+j - size/2] = cell;
            }
        }
    }
}

void update(World& world, Sim_Data s)
{
    int ix[s.w];
    int iy[s.h];


    for (int i = 0; i < s.w; ++i)
    {
        ix[i]=i;
    }
    for (int i = 0; i < s.h; ++i)
    {
        iy[i]=i;
    }

    /*size_t i;
    for (i = 0; i < s.w - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (s.w - i) + 1);
        int t = ix[j];
        ix[j] = ix[i];
        ix[i] = t;
    }
    for (i = 0; i < s.h - 1; i++)
    {
        size_t j = i + rand() / (RAND_MAX / (s.h - i) + 1);
        int t = iy[j];
        iy[j] = iy[i];
        iy[i] = t;
    }*/
    //for (i = 0; i < 255 - 1; i++)
    //{
    //    size_t j = i + rand() / (RAND_MAX / (255 - i) + 1);
    //    int t = iy[j];
    //    iy[j] = iy[i];
    //    iy[i] = t;
    //}


    for (int i = 0; i < s.w; ++i)
    {
        for (int j = 0; j < s.h ; ++j)
        {
            sf::Vector2i pos = sf::Vector2i(ix[i],iy[j]);
            //std::cout << pos.x << ", " << pos.y << std::endl;
            Cell* cell = world.get_cell(pos);
            if (!cell->updated) {cell->update(pos, world);}
            cell->updated = true;
        }
    }

    for (int i = 0; i < s.w; ++i)
    {
        for (int j = 0; j < s.h; ++j)
        {
            world.get_cell(sf::Vector2i(i,j))->updated = false;
        }
    }
}

void render(sf::RenderWindow& window, World& world, DrawMode mode)
{
    window.clear();
    switch (mode) {
        case SHAPES:
            draw_shapes(window, world);
        case TEXTURE:
            draw_texture(window, world);
    }
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
