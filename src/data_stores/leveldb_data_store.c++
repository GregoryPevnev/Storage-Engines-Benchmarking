#include <iostream>

#include "leveldb/db.h"

#include "se_bench/data_stores/leveldb_data_store.h++"

using namespace std;

void test_leveldb_data_store() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);

    cout << (status.ok() ? "OK" : "NOT OK") << endl;
}
