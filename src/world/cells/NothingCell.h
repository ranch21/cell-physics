//
// Created by ranch on 9/17/2024.
//

#ifndef NOTHINGCELL_H
#define NOTHINGCELL_H
#include "../Cell.h"


class NothingCell : public Cell {
public:
    NothingCell();
    void update(sf::Vector2i position, World& world) override;
};



#endif //NOTHINGCELL_H
