#ifndef _METEOSTATION_
#define _METEOSTATION_

#include "Weathervane.h"
#include <vector>
#include <array>
#include "utils.h"
#include "constants.h"
using namespace std;

// Дочерний класс, наследник от Weathervane
class Meteostation : public Weathervane {
public:

    Meteostation(int x, int y) : Weathervane(x, y) {
        wind_speed = -1;
        wind_direction = -1;
        temperature = -1;
        pressure = -1;
        data = vector<array<int, 4>>();
    } // конструктор инициализации
    
    Meteostation() : Meteostation(0, 0) {} // конструктор по умолчанию

    Meteostation(const Meteostation& station) : Weathervane(station.x_coord, station.y_coord) {
        wind_speed = -1;
        wind_direction = -1;
        temperature = -1;
        pressure = -1;
        data = vector<array<int, 4>>();
    } // конструктор копирования

    Class_type get_type() const override {
        return Class_type::Meteostation;
    } // метод идентификации
    
    int get_data_size() const {
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
    
    void measure_all_metrics() override; // измерение характеристик

private:
    int temperature {-1};
    int pressure {-1};
    vector<array<int, 4>> data; // Вектор хранит несколько сделанных измерений метеостанции
    
    void measure_temperature() {
       measure_metric(temperature, MIN_TEMPERATURE, MAX_TEMPERATURE);
    };
    
    void measure_pressure() {
        measure_metric(pressure, MIN_PRESSURE, MAX_PRESSURE);
    };

};

#endif