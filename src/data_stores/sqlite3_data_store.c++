#include <iostream>

#include "sqlite3.h"

#include "se_bench/data_stores/sqlite3_data_store.h++"

using namespace std;

void test_sqlite3_data_store() {
    cout << sqlite3_libversion() << endl;
}
