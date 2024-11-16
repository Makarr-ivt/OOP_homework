#ifndef _TESTS_
#define _TESTS_
#include <cassert>
#include "Meteostation.h"

// Weathevane tests
void test_weathervane_default_constructor();
void test_weathervane_initialization_constructor();
void test_weathervane_copy_constructor();
void test_weathervane_get_results();
void test_weathervane_measure_all_metrics();

void test_weathervane();
// ------------------------------------------

// Meteostation tests
void test_meteostation_default_constructor();
void test_meteostation_initialization_constructor();
void test_meteostation_copy_constructor();
void test_meteostation_measure_all_metrics();

void test_meteostation();

void test_get_type();


#endif