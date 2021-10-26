#include "se_bench/benchmarker.h++"
#include "se_bench/data_stores/leveldb_data_store.h++"

int main() {
    test_benchmarker();
    
    test_leveldb_data_store();

    return 0;
}
