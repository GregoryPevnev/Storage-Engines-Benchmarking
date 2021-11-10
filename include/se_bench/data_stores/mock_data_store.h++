#ifndef MOCK_DATA_STORE
#define MOCK_DATA_STORE

#include <string>

#include "se_bench/benchmarker.h++"

using namespace std;

class mock_data_store: public data_store {
public:
    void open(string working_directory_path);

    string read(string key);

    void write(string key, string record);

    void remove(string key);

    void close();
};

#endif
