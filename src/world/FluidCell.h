//
// Created by ranch on 9/18/2024.
//

#ifndef FLUIDCELL_H
#define FLUIDCELL_H
#include "Cell.h"

bool rand_bool();

class FluidCell : public Cell {
    bool direction = rand_bool();
    virtual void step(sf::Vector2i position, World& world) = 0;
public:
    void update(sf::Vector2i position, World& world) override;
};



#endif //FLUIDCELL_H
