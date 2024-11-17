#ifndef _APPMANAGER_
#define _APPMANAGER_

#include <vector>
#include <memory>
#include "Meteostation.h"
#include "constants.h"

using namespace std;

// метеоцентр
class AppManager final {
public:
// Получение единственного экземпляра класса
    static AppManager& getInstance() {
        static AppManager instance; // Создается единожды и живет до конца программы
        return instance;
    }

    // Удаление возможности копирования и перемещения
    AppManager(const AppManager&) = delete;             // Запрет конструктора копирования
    AppManager& operator=(const AppManager&) = delete;  // Запрет присваивания
    AppManager(AppManager&&) = delete;                  // Запрет конструктора перемещения
    AppManager& operator=(AppManager&&) = delete;       // Запрет перемещающего присваивания

    void set_user_kingdom_size();
    void set_user_num_of_vanes();
    void setup_meteosystem();
    void show_stations_list() const;
    void take_measures();
    void save_data_to_csv();
    void clear_csv();
    void launch_python_script();
    
    int get_kingdom_size() const {
        return kingdom_size;
    }

    int get_num_of_vanes() const {
        return num_of_vanes;
    }

private:
    AppManager():
        kingdom_size(DEFAULT_KINGDOM_SIZE),
        num_of_vanes(DEFAULT_NUM_OF_VANES)
    {
        stations = vector<unique_ptr<Weathervane>>();
    }
    // ~AppManager() {
    //     clearCSV();
    // }
    
    
    unsigned int kingdom_size;
    unsigned int num_of_vanes;
    vector<unique_ptr<Weathervane>> stations;
};

#endif