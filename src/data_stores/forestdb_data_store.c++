#include <iostream>

#include "libforestdb/forestdb.h"

#include "se_bench/data_stores/forestdb_data_store.h++"

using namespace std;

void test_forestdb_data_store() {
    fdb_status status;
    fdb_config config;

    config = fdb_get_default_config();

    status = fdb_init(&config);

    cout << (status == FDB_RESULT_SUCCESS ? "OK" : "NOT OK") << endl;
}
