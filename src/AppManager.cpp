#include "AppManager.h"
#include "utils.h"
#include <iostream>
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
