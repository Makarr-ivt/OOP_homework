#include <random>

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
