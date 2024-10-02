//
// Created by ranch on 9/8/2024.
//

#include <functional>
#include <random>

int n1or1() {
    if (rand() > (RAND_MAX / 2))
    {
        return 1;
    }
    return -1;
}

int rand_bool() {
    return rand() > (RAND_MAX / 2);
}
