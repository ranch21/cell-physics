//
// Created by ranch on 9/17/2024.
//

#ifndef SOLIDIMMOVABLECELL_H
#define SOLIDIMMOVABLECELL_H
#include "World.h"
#include "SFML/System/Vector2.hpp"


class SolidImmovableCell : public Cell {
    virtual void step(sf::Vector2i position, World& world) = 0;
public:
    void update(sf::Vector2i position, World& world) override;
};



#endif //SOLIDIMMOVABLECELL_H
