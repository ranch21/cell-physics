//
// Created by ranch on 9/28/24.
//

#include "Metal.h"

Metal::Metal() {
    mass = 0;
    color = sf::Color(200,200,200);
    type = SOLID_IMMOVABLE;
    temperature = 22;
    heat_conductivity = 0.85f;
}

void Metal::step(sf::Vector2i position, World &world) {

}
