#ifndef LEVELDB_DATA_STORE
#define LEVELDB_DATA_STORE

#include <string>

#include "leveldb/db.h"

#include "se_bench/benchmarker.h++"

using namespace std;

class leveldb_data_store: public data_store {
private:
    leveldb::DB* db;
    leveldb::Status status;
public:
    void open(string working_directory_path);

    string read(string key);

    void write(string key, string record);

    void remove(string key);

    void close();
};

#endif
