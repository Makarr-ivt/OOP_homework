#include <random>
#include <iostream>

// Функция для генерации случайных целых чисел
int measure(int min, int max)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range
    return distr(gen);
}
// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range


// Функция для измерения абстрактного погодного показателя
void measure_metric(int &metric, int min_limit, int max_limit) {
    int change_factor = measure(0, 10);
    if (change_factor < 2 or metric == -1) { // Показатель принимает новое случайное значение
        metric = measure(min_limit, max_limit);
    } else if (change_factor < 8) { // Показатель изменяется на дельту
        metric += measure(-10, 10);
    };
    if (metric > max_limit) { // Проверка на то, что показатель не вышел за пределы
        metric = max_limit - measure(1, 10);
    } else if (metric < min_limit) {
        metric = measure(1, 10);
    };
    // Если change_factor in {8, 9, 10}, показатель не меняется
}

bool is_answer_yes(std::string question) {
    std::cout << question << "[y/n]: ";
    //get user input
    char input;
    std::cin >> input;
    //convert the input to lowercase 
    char answer = tolower(input);
    //check the input (not valid input will clear the user input)
    while (!(std::cin >> input) || ((answer != 'y') && (answer != 'n'))) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please, try again!\n";
        std::cout << question << "[y/n]: ";
    }
    //evalute input cases
    switch (answer) {
    case 'y':
        return true;
    case 'n':
        return false;
    }
}