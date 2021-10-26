#include <iostream>
#include "se_bench/benchmarker.h++"
#include "se_bench/data_stores/mock_data_store.h++"

using namespace std;

int main(int argc, char** argv) {
    if(argc != 2 && argc != 3) {
        cout << "Invalid number of arguments: Provide a path to the configuration file" << endl;

        return 1;
    }

    data_store* mock = new mock_data_store();

    benchmark_config config = load_benchmarking_config(argv[1]);

    benchmark_data_store(mock, config, argc == 3);

    return 0;
}
