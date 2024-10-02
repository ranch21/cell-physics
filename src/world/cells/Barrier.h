//
// Created by ranch on 9/17/2024.
//

#ifndef BARRIER_H
#define BARRIER_H
#include "../SolidImmovableCell.h"


class Barrier : public SolidImmovableCell {
public:
    Barrier();
    void step(sf::Vector2i position, World& world) override;
};



#endif //BARRIER_H
