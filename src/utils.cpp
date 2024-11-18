#include <random>
#include <iostream>
using namespace std;

// Функция для генерации случайных целых чисел
int measure(int min, int max) {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max); // define the range
    return distr(gen);
}
// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range


// Функция для измерения абстрактного погодного показателя
void measure_metric(int &metric, int min_limit, int max_limit) {
    int change_factor = measure(0, 10);
    if (change_factor < 3 || metric == -1) { // Показатель принимает новое случайное значение
        metric = measure(min_limit, max_limit);
    } else {
        int delta = measure(-3, 3); // Ограничить дельту изменениями от -3 до 3
        metric += delta;
    }
    
    // Проверка на то, что показатель не вышел за пределы
    if (metric > max_limit) {
        metric = max_limit;
    } else if (metric < min_limit) {
        metric = min_limit;
    }
}


bool is_answer_yes(string question) {
    cout << question << " [y/n]:";
    //get user input
    string input;
    //check the input (not valid input will clear the user input)
    if (!(cin >> input)
        || ((tolower(input[0]) != 'y') && (tolower(input[0]) != 'n'))
        || (input.length() > 1)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please, try again!\n";
        return is_answer_yes(question);
    }
    //evalute input cases
    if (tolower(input[0]) == 'y') {
        return true;
    }
    return false;
} // https://stackoverflow.com/a/73790241


int ask_int_value(int min_v, int max_v) {
    int number;
    cout << "Enter an integer between "<<min_v<<" and "<<max_v<<": ";
    if (!(cin >> number) || number < min_v || number > max_v) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return ask_int_value(min_v, max_v);
    }
    return number;
}

pair<int, int> ask_int_pair(int min_v, int max_v) {
    int first, second;
    cout << "Enter two integers between " << min_v << " and " << max_v << " separated by space: ";
    
    if (!(cin >> first >> second)
        || first < min_v || first > max_v
        || second < min_v || second > max_v) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return ask_int_pair(min_v, max_v);
    }

    return make_pair(first, second);
}

pair<int, int> generate_int_pair(int min_v, int max_v) {
    return make_pair(measure(min_v, max_v), measure(min_v, max_v));
}