#include "Weathervane.h"

bool Weathervane::get_results(int &wind_speed, int &wind_direction) const {
    if (this->wind_speed == -1 || this->wind_direction == -1) {
        return false;
    };
    wind_speed = this->wind_speed;
    wind_direction = this->wind_direction;
    return true;
}

void Weathervane::get_coords(int &x, int &y) const {
    x = x_coord;
    y = y_coord;
}