#ifndef _WEATHERVANE_
#define _WEATHERVANE_

#include "class_type.h"
#include "utils.h"
#include "constants.h"



// Базовый класс
class Weathervane {
public:
    Weathervane() : x_coord(0), y_coord(0)
    { } // конструктор по умолчанию

    Weathervane(int x, int y) : x_coord(x), y_coord(y)
    { } // конструктор инициализации
    
    Weathervane(const Weathervane& prev_vane) : Weathervane(prev_vane.x_coord, prev_vane.y_coord) {
        wind_speed = -1;
        wind_direction = -1;
    } // конструктор копирования
    
    void get_coords(int &x, int &y) const;
    // геттер координат
    
    virtual Class_type get_type() const {
        return Class_type::Weathervane;
    } // метод идентификации
    
    bool get_results(int &wind_speed, int &wind_direction) const;
    /* геттер последних измерений
    записывает значения последних измерений в переданные перепенные
    Возвращает true, если значения переданы, иначе false
    */

    virtual void measure_all_metrics() {
        measure_wind_direction();
        measure_wind_speed();
    } // измерение характеристик
    
protected:
    int wind_direction {-1};
    int wind_speed {-1};
    int x_coord;
    int y_coord;
    
    
    void measure_wind_speed(void) {
        measure_metric(wind_speed, 0, MAX_WIND_SPEED);
    }
    
    void measure_wind_direction(void) {
        measure_metric(wind_direction, 0, MAX_WIND_DIRECTION);
    }
};

#endif