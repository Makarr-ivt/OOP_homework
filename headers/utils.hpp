#ifndef _TOOLS_
#define _TOOLS_
#include <string>
using namespace std;

void measure_metric(int &metric, int min_limit, int max_limit);
bool is_answer_yes(string question);
int ask_int_value(int min_v, int max_v);
pair<int, int> ask_int_pair(int min_v, int max_v);
pair<int, int> generate_int_pair(int min_v, int max_v);
#endif