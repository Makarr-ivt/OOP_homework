#ifndef _APPMANAGER_
#define _APPMANAGER_

#include <vector>
#include "Meteostation.h"

#define DEFAULT_KINGDOM_SIZE 10
#define DEFAULT_NUM_OF_VANES 3

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

    unsigned int get_kingdom_size() const {
        return kingdom_size;
    }
    unsigned int get_num_of_vanes() const {
        return num_of_vanes;
    }

private:
    AppManager():
        kingdom_size(DEFAULT_KINGDOM_SIZE),
        num_of_vanes(DEFAULT_NUM_OF_VANES)
    {
        stations = std::vector<std::reference_wrapper<Weathervane>>();
    }
    // ~AppManager() {
    //     clearCSV();
    // }
    
    void set_user_kingdom_size();
    void set_user_num_of_vanes();
    void setup_meteosystem();
    void take_measures(); // обновляет значения всех метеостанций/флюгеров
    void save_data_to_csv();
    void clear_csv();
    void launch_python_script();
    


    unsigned int kingdom_size;
    unsigned int num_of_vanes;
    std::vector<std::reference_wrapper<Weathervane>> stations;
};

#endif