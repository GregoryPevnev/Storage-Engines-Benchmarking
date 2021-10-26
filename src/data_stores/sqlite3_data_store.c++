#include <string>

#include "sqlite3.h"

#include "se_bench/data_stores/sqlite3_data_store.h++"

using namespace std;

void sqlite3_data_store::open(string working_directory_path) {}

void sqlite3_data_store::save(string key, string value) {}

string sqlite3_data_store::load(string key) {
    return "";
}

void sqlite3_data_store::close() {}
