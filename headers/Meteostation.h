#ifndef _METEOSTATION_
#define _METEOSTATION_

#include "Weathervane.h"
#include <vector>
#include <array>
#include "utils.h"

#define MIN_TEMPERATURE 250
#define MAX_TEMPERATURE 310
#define MIN_PRESSURE 700
#define MAX_PRESSURE 800


// Дочерний класс, наследник от Weathervane
class Meteostation : public Weathervane {
public:

    Meteostation(int x, int y) : Weathervane(x, y) {
        wind_speed = -1;
        wind_direction = -1;
        temperature = -1;
        pressure = -1;
        data = std::vector<std::array<int, 4>>();
    } // конструктор инициализации
    
    Meteostation() : Meteostation(0, 0) {} // конструктор по умолчанию

    Meteostation(const Meteostation& station) : Weathervane(station.x_coord, station.y_coord) {
        wind_speed = -1;
        wind_direction = -1;
        temperature = -1;
        pressure = -1;
        data = std::vector<std::array<int, 4>>();
    } // конструктор копирования

    Class_type get_type(void) const override {
        return Class_type::Meteostation;
    } // метод идентификации
    
    int get_data_size(void) const {
        return data.size();
    } // геттер для получения размера вектора с сохранёнными измерениями
    
    bool get_results(int &wind_speed,
                               int &wind_direction,\
                               int &temperature,\
                               int &pressure,\
                               int data_index = -1
                               ) const;
    /* геттер для получения результатов из вектора data.
    записывает значения последних измерений в переданные перепенные
    Возвращает true, если значения переданы, иначе false
    */
    
    void measure_all_metrics(void) override; // измерение характеристик

private:
    int temperature {-1};
    int pressure {-1};
    std::vector<std::array<int, 4>> data; // Вектор хранит несколько сделанных измерений метеостанции
    
    void measure_temperature(void) {
       measure_metric(temperature, MIN_TEMPERATURE, MAX_TEMPERATURE);
    };
    
    void measure_pressure(void) {
        measure_metric(pressure, MIN_PRESSURE, MAX_PRESSURE);
    };

};

#endif