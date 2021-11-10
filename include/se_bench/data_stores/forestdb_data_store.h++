#ifndef FORESTDB_DATA_STORE
#define FORESTDB_DATA_STORE

#include <string>

#include "libforestdb/forestdb.h"

#include "se_bench/benchmarker.h++"

using namespace std;

class forestdb_data_store: public data_store {
private:
    fdb_file_handle *fhandle;
    fdb_kvs_handle *db;
    fdb_status status;
public:
    void open(string working_directory_path);

    string read(string key);

    void write(string key, string record);

    void remove(string key);

    void close();
};

#endif
