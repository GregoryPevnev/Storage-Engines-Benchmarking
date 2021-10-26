#include <string>

#include "leveldb/db.h"

#include "se_bench/data_stores/leveldb_data_store.h++"

using namespace std;

void leveldb_data_store::open(string working_directory_path) {}

void leveldb_data_store::save(string key, string value) {}

string leveldb_data_store::load(string key) {
    return "";
}

void leveldb_data_store::close() {}
