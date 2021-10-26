#include "se_bench/benchmarker.h++"
#include "se_bench/data_stores/sqlite3_data_store.h++"
#include "se_bench/benchmark_runner.h++"

using namespace std;

int main(int argc, char** argv) {
    return run_benchmarking(new sqlite3_data_store(), argc, argv);
}
