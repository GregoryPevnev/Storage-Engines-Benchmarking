#include <iostream>
#include <string>

#include "se_bench/benchmarker.h++"

using namespace std;

void benchmark_data_store(data_store* ds, benchmark_config config) {
    benchmarker bench(ds, config.document_prototype, config.document_key_name, config.number_of_documents);

    // TODO: Logging and Timing

    bench.setup();

    bench.write();

    bench.read();

    bench.teardown();
}