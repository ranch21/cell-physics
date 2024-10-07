//
// Created by ranch on 10/3/24.
//

#ifndef CELL_ENUMS_H
#define CELL_ENUMS_H

enum Cell_Type {
    SOLID_MOVABLE,
    SOLID_IMMOVABLE,
    LIQUID,
    NOTHING
};

enum Cell_Table {
    AIR,
    BARRIER,
    SAND,
    WATER,
    METAL
};

Cell_Type get_cell_type(const Cell_Table id);
float get_hconductivity(const Cell_Table id);
float get_mass(const Cell_Table id);

#endif //CELL_ENUMS_H