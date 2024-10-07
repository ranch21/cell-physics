//
// Created by ranch on 10/3/24.
//

#include "cell_info.h"

Cell_Type get_cell_type(const Cell_Table id) {
    switch (id) {
        case AIR:
            return NOTHING;
        case BARRIER:
            return SOLID_IMMOVABLE;
        case SAND:
            return SOLID_MOVABLE;
        case WATER:
            return LIQUID;
        case METAL:
            return SOLID_IMMOVABLE;
    }
    return NOTHING;
}

float get_hconductivity(const Cell_Table id) {
    switch (id) {
        case AIR:
            return 0.0f;
        case BARRIER:
            return 0.0f;
        case SAND:
            return 0.2f;
        case WATER:
            return 0.85f;
        case METAL:
            return 0.8f;
    }
    return 0.0f;
}

float get_mass(const Cell_Table id) {
    switch (id) {
        case AIR:
            return 0.0f;
        case BARRIER:
            return 9999.0f;
        case SAND:
            return 1.6f;
        case WATER:
            return 1.0f;
        case METAL:
            return 7.8f;
    }
    return 1.0f;
}
