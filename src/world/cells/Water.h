//
// Created by ranch on 9/18/2024.
//

#ifndef WATER_H
#define WATER_H
#include "../FluidCell.h"


class Water : public FluidCell {

public:
    Water();
    void step(sf::Vector2i position, World& world) override;
};



#endif //WATER_H
