#include "test_modules.hpp"
#include <iostream>
#include "AppManager.hpp"
using namespace std;


static AppManager& Meteocenter = AppManager::getInstance();

int main()
{
    test_weathervane();
    test_meteostation();
    test_get_type();
    cout << "All assertions from 2 lab have been passed!\n";

    cout << Meteocenter.get_kingdom_size() << endl;
    Meteocenter.set_user_kingdom_size();
    cout << Meteocenter.get_kingdom_size() << endl;
    cout << Meteocenter.get_num_of_vanes() << endl;
    Meteocenter.set_user_num_of_vanes();
    cout << Meteocenter.get_num_of_vanes() << endl;
    Meteocenter.setup_meteosystem();
    //Meteocenter.show_stations_list();
    Meteocenter.make_measurements();
    Meteocenter.save_to_json();

    return 0;
}
