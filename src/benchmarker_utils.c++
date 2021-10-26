#include <iostream>
#include <string>
#include <chrono>

#include "se_bench/benchmarker.h++"

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point current_time() {
    return high_resolution_clock::now();
}

long time_diff(high_resolution_clock::time_point start_time, high_resolution_clock::time_point end_time) {
    duration<double> time_span = duration_cast<duration<double>>(end_time - start_time);

    double seconds = time_span.count();

    return seconds * 1000;
}

void benchmark_data_store(data_store* ds, benchmark_config config, bool with_info) {
    high_resolution_clock::time_point start_time, end_time;
    long total_read_time, total_write_time;
    long total_volume;

    benchmarker bench(ds, config.document_prototype, config.document_key_name, config.number_of_documents);

    // Setup

    cout << "Setting up the benchmarking environment" << endl;

    bench.setup();

    // Writing

    cout << "Writing mock data" << endl;

    start_time = current_time();

    total_volume = bench.write();

    total_write_time = time_diff(start_time, current_time());

    // Reading

    cout << "Reading mock data" << endl;

    start_time = current_time();

    bench.read();

    total_read_time = time_diff(start_time, current_time());

    // Cleanup

    cout << "Cleaning up the benchmarking environment" << endl;

    bench.teardown();

    // Information

    if (with_info) {
        cout << "Total bytes written and read: " << total_volume << endl;

        cout << endl << "Speed of writing and reading" << endl;
        cout << "Writing total time: " << total_write_time << " ms" << endl;
        cout << "Reading total time: " << total_read_time << " ms" << endl;

        cout << endl << "Throughput of writing and reading" << endl;
        cout << "Writing throughput: " << (total_volume / total_write_time) << " bytes/ms" << endl;
        cout << "Reading throughput: " << (total_volume / total_read_time) << " bytes/ms" << endl;
    }
}