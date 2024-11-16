#include "test_modules.h"

void test_weathervane() {
    test_weathervane_default_constructor();
    test_weathervane_initialization_constructor();
    test_weathervane_copy_constructor();
    test_weathervane_get_results();
    test_weathervane_measure_all_metrics();
}

void test_weathervane_default_constructor() {
    Weathervane w;
    int x, y;
    w.get_coords(x, y);
    assert(x == 0);
    assert(y == 0);
}

void test_weathervane_initialization_constructor() {
    Weathervane w(10, 20);
    int x, y;
    w.get_coords(x, y);
    assert(x == 10);
    assert(y == 20);
}

void test_weathervane_copy_constructor() {
    Weathervane original_vane(5, 15);
    Weathervane copy_vane(original_vane);
    
    // Проверка, что скопированный и оригинальный имеют разные адреса
    assert(&original_vane != &copy_vane);
    
    int x, y, wind_speed, wind_direction;
    copy_vane.get_coords(x, y);
    assert(x == 5);
    assert(y == 15);
    
    // Проверка, что значения wind_speed и wind_direction инициализируюстя как -1
    assert(!copy_vane.get_results(wind_speed, wind_direction));
}

void test_weathervane_get_results() {
    Weathervane w;
    int wind_speed, wind_direction;
    bool result = w.get_results(wind_speed, wind_direction);
    
    // Поскольку мы только что создали объект, а измерения еще не проводились - ожидаем false
    assert(!result);
}

void test_weathervane_measure_all_metrics() {
    Weathervane w;
    w.measure_all_metrics();
    
    int wind_speed, wind_direction;
    bool result = w.get_results(wind_speed, wind_direction);
    
    // Так как мы произвели измерения, теперь значения должны быть установлены
    assert(result);
    assert(wind_speed >= 0); // скорость ветра неотрицательна
    assert(wind_direction >= 0 && wind_direction <= 359); // направление в пределах 0-359
}
