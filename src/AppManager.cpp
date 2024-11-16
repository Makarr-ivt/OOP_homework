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

void AppManager::set_user_num_of_vanes() {    
    string question = "Current size of vanes is "
                            + to_string(AppManager::num_of_vanes)
                            + "\nDo you want to change it?";
    if (!is_answer_yes(question)){
        return;
    }
    cout << "Enter new num of vanes!\n";
    AppManager::num_of_vanes = ask_int_value(0, AppManager::kingdom_size);
    AppManager::set_user_num_of_vanes();
}
