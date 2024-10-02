//
// Created by ranch on 9/17/2024.
//

#ifndef SAND_H
#define SAND_H
#include "../SolidMovableCell.h"


class Sand : public SolidMovableCell
{
public:
    Sand();
    void step(sf::Vector2i position, World& world) override;
};



#endif //SAND_H
