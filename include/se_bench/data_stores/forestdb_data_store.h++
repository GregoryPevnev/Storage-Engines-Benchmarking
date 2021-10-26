#ifndef FORESTDB_DATA_STORE
#define FORESTDB_DATA_STORE

#include <string>

#include "se_bench/benchmarker.h++"

using namespace std;

class forestdb_data_store: public data_store {
public:
    void open(string working_directory_path);

    string load(string key);

    void save(string key, string value);

    void close();
};


#endif
