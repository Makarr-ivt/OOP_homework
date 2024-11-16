#include "test_modules.h"
#include <iostream>
#include "AppManager.h"
using namespace std;


static AppManager& Meteocenter = AppManager::getInstance();

int main()
{
    cout << Meteocenter.get_kingdom_size() << endl;
    cout << Meteocenter.get_num_of_vanes() << endl;

    // test_weathervane();
    // test_meteostation();
    // test_get_type();
    // cout << "All assertions have been passed!\n";
    return 0;
}
