//
// Created by ranch on 10/2/24.
//
#include <cstring>
#include <iostream>
#include <fstream>
#include "world/World.h"
#include "world/cells/Barrier.h"
#include "world/cells/Metal.h"
#include "world/cells/NothingCell.h"
#include "world/cells/Sand.h"
#include "world/cells/Water.h"

void save(World& world, std::string filename) {
    filename = filename + ".cellphys";
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&world.size.x), 4);
    file.write(reinterpret_cast<const char*>(&world.size.y), 4);
    for (int i = 0; i < world.size.x; ++i) {
        for (int j = 0; j < world.size.y; ++j) {
            Cell* cell = world.get_cell(sf::Vector2i(i, j));
            file.write(reinterpret_cast<const char*>(&cell->id), 4);
            file.write(reinterpret_cast<const char*>(&cell->temperature), 4);
        }
    }
    file.close();
}

Cell* get_cell_from_id(Cell_Table id) {
    Cell* cell;
    switch (id) {
        case AIR:
            cell = new NothingCell();
        break;
        case BARRIER:
            cell = new Barrier();
        break;
        case SAND:
            cell = new Sand();
        break;
        case WATER:
            cell = new Water();
        break;
        case METAL:
            cell = new Metal();
        break;
    }
    return cell;
}

World load(std::string filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open the file.\n";
        exit(1);
    }
    int world_width, world_height;

    file.read(reinterpret_cast<char*>(&world_width), 4);
    file.read(reinterpret_cast<char*>(&world_height), 4);

    auto world = World(world_width,world_height);

    for (int i = 0; i < world_width; ++i) {
        for (int j = 0; j < world_height; ++j) {
            Cell_Table id;
            file.read(reinterpret_cast<char*>(&id), 4);
            float temp;
            file.read(reinterpret_cast<char*>(&temp), 4);
            Cell* cell = get_cell_from_id(id);
            cell->temperature = temp;
            world.set_cell(sf::Vector2i(i, j), cell);
        }
    }

    return world;

    std::cout << world_width << "\n" << world_height << "\n";
    //auto world = World(world_width,world_height);
}
