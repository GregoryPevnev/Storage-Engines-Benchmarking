#ifndef LEVELDB_DATA_STORE
#define LEVELDB_DATA_STORE

#include <string>

#include "se_bench/benchmarker.h++"

using namespace std;

class leveldb_data_store: public data_store {
public:
    void open(string working_directory_path);

    string load(string key);

    void save(string key, string value);

    void close();
};


#endif
