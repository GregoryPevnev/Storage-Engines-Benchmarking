#include "se_bench/benchmarker.h++"
#include "se_bench/data_stores/mock_data_store.h++"

int main() {
    data_store* mock = new mock_data_store();

    benchmark_config config = load_benchmarking_config();

    benchmark_data_store(mock, config);

    return 0;
}
