#include "test_modules.h"

void test_get_type() {
    Meteostation m;
    Weathervane w;
    assert(w.get_type() == Class_type::Weathervane);
    assert(m.get_type() == Class_type::Meteostation);
}

void test_meteostation() {
    test_meteostation_default_constructor();
    test_meteostation_initialization_constructor();
    test_meteostation_copy_constructor();
    test_meteostation_measure_all_metrics();
}

void test_meteostation_default_constructor() {
    Meteostation m;
    int x, y;
    m.get_coords(x, y);
    assert(x == 0);
    assert(y == 0);
    assert(m.get_data_size() == 0); // Нет сохраненных данных
}

void test_meteostation_initialization_constructor() {
    Meteostation m(10, 20);
    int x, y;
    m.get_coords(x, y);
    assert(x == 10);
    assert(y == 20);
    assert(m.get_data_size() == 0); // Нет сохраненных данных
}

void test_meteostation_copy_constructor() {
    Meteostation original(5, 15);
    Meteostation copy(original);
    
    int x, y;
    copy.get_coords(x, y);
    assert(x == 5);
    assert(y == 15);
    assert(copy.get_data_size() == 0); // Нет сохраненных данных
}

void test_meteostation_measure_all_metrics() {
    Meteostation m;
    m.measure_all_metrics();

    int wind_speed, wind_direction, temperature, pressure;
    bool result = m.get_results(wind_speed, wind_direction, temperature, pressure, 0);

    // Проверяем, что одно измерение записано
    assert(m.get_data_size() == 1); 

    // Проверяем корректность измерений
    assert(result);
    assert(wind_speed >= 0);
    assert(wind_direction >= 0 && wind_direction <= 359);
    assert(temperature != -1);
    assert(pressure != -1);
}
