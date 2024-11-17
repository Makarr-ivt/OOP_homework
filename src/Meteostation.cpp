#include "Meteostation.hpp"
#include <iostream>

void Meteostation::measure_all_metrics() {
    Weathervane::measure_all_metrics();
    measure_temperature();
    measure_pressure();
    data.push_back({wind_speed, wind_direction, temperature, pressure});
};

bool Meteostation::get_results(int &wind_speed,
                               int &wind_direction,
                               int &temperature,
                               int &pressure,
                               int data_index
                               ) const {
    if (data.empty()) {
        return false;
    };
    
    while (data_index < 0) {
        data_index += data.size();
    };
    
    if (data_index >= data.size()) {
        return false;
    };
    
    wind_speed = data[data_index][0];
    wind_direction = data[data_index][1];
    temperature = data[data_index][2];
    pressure = data[data_index][3];
    return true;
};
