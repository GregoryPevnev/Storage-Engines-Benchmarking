#include <iostream>
#include "se_bench/benchmarker.h++"

using namespace std;

int run_benchmarking(data_store* ds, int argc, char** argv) {
    if(argc != 2 && argc != 3) {
        cout << "Invalid number of arguments: Provide a path to the configuration file" << endl;

        return 1;
    }

    benchmark_config config = load_benchmarking_config(argv[1]);

    benchmark_data_store(ds, config, argc == 3);

    return 0;
}
