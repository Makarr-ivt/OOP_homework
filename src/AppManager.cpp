#include "AppManager.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <set>

using namespace std;


void AppManager::set_user_kingdom_size() {    
    string question = "Current size of kindom is "
                    + to_string(AppManager::kingdom_size)
                    + " * "
                    + to_string(AppManager::kingdom_size)
                    + "\nDo you want to change it?";
    if (!is_answer_yes(question)){
        return;
    }
    cout << "Enter new size for the kingdom!\n";
    AppManager::kingdom_size = ask_int_value(MIN_KINGDOM_SIZE, MAX_KINGDOM_SIZE);
    AppManager::set_user_kingdom_size();
}


void AppManager::set_user_num_of_vanes() {    
    string question = "Current num of vanes is "
                    + to_string(AppManager::num_of_vanes)
                    + "\nDo you want to change it?";
    if (!is_answer_yes(question)){
        return;
    }
    cout << "Enter new num of vanes!\n";
    AppManager::num_of_vanes = ask_int_value(0, AppManager::kingdom_size);
    AppManager::set_user_num_of_vanes();
}


void AppManager::setup_meteosystem() {
    string question = "Current num of vanes is "
                    + to_string(AppManager::num_of_vanes)
                    + "\nBy default they set in random places."
                    + "\nDo you want to set them explicitly?";

    set<pair<int, int>> vanes_coords;
    auto get_coords = generate_int_pair;
    if (is_answer_yes(question)){
        get_coords = ask_int_pair;
    }

    while (vanes_coords.size() < AppManager::num_of_vanes) {
        auto new_coords = get_coords(0, AppManager::kingdom_size - 1);
        if (!vanes_coords.count(new_coords)) {
            vanes_coords.insert(new_coords);
        }
    }

    for (auto x = 0; x < AppManager::kingdom_size; ++x) {
        for (auto y = 0; y < AppManager::kingdom_size; ++y) {
            pair<int, int> coord = {x, y};
            if (vanes_coords.count(coord)) {
                stations.emplace_back(make_unique<Weathervane>(x, y));
            } else {
                stations.emplace_back(make_unique<Meteostation>(x, y));
            }
        }
    }   
}


void AppManager::show_stations_list() const {
    for (auto& station_ptr : AppManager::stations) {
        auto station = station_ptr.get();
        int x, y;
        string type;
        station->get_coords(x, y);
        switch (station->get_type()) {
            case Class_type::Weathervane:
                type = "Weathervane";
                break;
            case Class_type::Meteostation:
                type = "Meteostation";
                break;
        }
        cout <<"("<< x << ", "<< y << ") station is " << type << endl;
    }
}

void AppManager::make_measurements() {
    cout << "Now let's take some measurements! How many do you want to make?\n";
    int times = ask_int_value(MIN_MEASUREMENTS, MAX_MEASUREMENTS);
    AppManager::update_stations(times);
}

void AppManager::update_stations(int times) {
    for (auto n = 0; n < times; ++n) {
        for (auto& station_ptr : AppManager::stations) {
            auto station = station_ptr.get();
            station->measure_all_metrics();
        }
    }
}

void AppManager::save_to_json(const string& filename) {
    json j;
    for (const auto& station : AppManager::stations) {
        j.push_back(station->to_json());
    }
    ofstream file(filename);
    file << j.dump(4); // С отступом в 4 пробела для читабельности
}

void AppManager::launch_python_script() {
    system(COMMAND_CALL_PYTHON_SCRIPT);
}