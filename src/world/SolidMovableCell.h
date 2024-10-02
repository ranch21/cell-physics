//
// Created by ranch on 9/15/2024.
//

#ifndef SOLIDMOVABLECELL_H
#define SOLIDMOVABLECELL_H
#include "Cell.h"


class SolidMovableCell : public Cell {
    virtual void step(sf::Vector2i position, World& world) = 0;
public:
    void update(sf::Vector2i position, World& world) override;
};



#endif //SOLIDMOVABLECELL_H
