#include <string>

#include "libforestdb/forestdb.h"

#include "se_bench/data_stores/forestdb_data_store.h++"

using namespace std;

void forestdb_data_store::open(string working_directory_path) {}

void forestdb_data_store::save(string key, string value) {}

string forestdb_data_store::load(string key) {
    return "";
}

void forestdb_data_store::close() {}
