//
// Created by ranch on 9/28/24.
//

#ifndef METAL_H
#define METAL_H
#include "../SolidImmovableCell.h"


class Metal : public SolidImmovableCell {
    public:
    Metal();
    void step(sf::Vector2i position, World& world) override;
};



#endif //METAL_H
