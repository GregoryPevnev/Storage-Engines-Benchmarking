#include "se_bench/benchmarker.h++"
#include "se_bench/data_stores/sqlite3_data_store.h++"

int main() {
    test_benchmarker();
    
    test_sqlite3_data_store();

    return 0;
}
