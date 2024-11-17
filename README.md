Сейчас работа находится в разработке, данный файл будет использоваться как список задач.

TODO 17.11 update:
Реализована значительная часть класса AppManager
- `void set_user_kingdom_size();`
- `void set_user_num_of_vanes();`
- `void setup_meteosystem();`
- `void show_stations_list() const;`

Для их работы в `utils.cpp` реализованы фукнции:
- `bool is_answer_yes(string question);`
- `int ask_int_value(int min_v, int max_v);`
- `pair<int, int> ask_int_pair(int min_v, int max_v);`
- `pair<int, int> generate_int_pair(int min_v, int max_v);`
Всё это протестировано в `main.cpp`, работает.

### Сегодня надо:

1. Доделать класс `AppManager`. А именно методы:
- `void take_measures();`
- `void save_data_to_csv();`
- `void clear_csv();`
- `void launch_python_script();`
	- Сохранять данные в **CSV** или подключить **sqlite**?
	- Продумать, в каком виде сохранять данные.

2. **! делать только если остаётся время!!!** Реализовать в классе расчёт показателей в заданной пользователем точке, написать функции для расчёта поляризации. 


3. Сделать скрипт на `python`, используя библиотеку `plotly`. 
- отображение нескольких графиков: температуры, давления
- продумать, как показывать силу и направление ветра. Хочется сделать нечто вроде фазового портрета, векторы, направление и длина которых зависит от соответствующих значений.
4. Оформить документацию.

**update 16:05** -- Мария Андреевна разрешила не проводить тщательное Unit тестирование программы! Выкидываю этот пункт из плана!


# Решение проблемы со стабильностью **plotly**
**Проблема:** Plotly всё время открывает программу на разных портах, из-за чего она запускалась "через раз".

**Решение:** 
Решилась проблема изменением строки исходника `\plotly\io\_base_renderers.py` c 0 (рандом), например на **8080**:
```python
server = HTTPServer(("127.0.0.1", 8080), OneShotRequestHandler)
    browser.open(
        "http://127.0.0.1:%s" % server.server_port, new=new, autoraise=autoraise
    )
```

- [источник](https://www.cyberforum.ru/python-graphics/thread2504243.html)