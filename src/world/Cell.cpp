//
// Created by ranch on 9/7/2024.
//

#include "Cell.h"

sf::Color Cell::color_offset(sf::Color color, unsigned char amount)
{
    int offset = (rand() % amount * 2 + 1) - amount;
    color.r = std::clamp(color.r + offset, 0, 255);

    color.g = std::clamp(color.g + offset, 0, 255);

    color.b = std::clamp(color.b + offset, 0, 255);

    return  color;
}

void Cell::transfer_heat(sf::Vector2i position, World &world) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            Cell* compare_cell = world.get_cell(position + sf::Vector2i(dx, dy));
            if (compare_cell->temperature < temperature) {continue;}
            float conduct = (get_hconductivity(this->id) + get_hconductivity(compare_cell->id)) / 2.0f;
            float temp_diff = compare_cell->temperature - temperature;
            float heat_transfer = temp_diff * conduct;
            temperature += heat_transfer;
            compare_cell->temperature -= heat_transfer;
        }
    }
}
