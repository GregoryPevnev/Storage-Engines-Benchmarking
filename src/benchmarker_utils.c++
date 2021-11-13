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
    long total_read_time, total_write_time, total_delete_time, mixed_time;
    long total_volume, mixed_volume;

    benchmarker bench(ds, config.document_prototype, config.document_key_name, config.number_of_documents);

    // Setup

    if (with_info) {
        cout << "Setting up the benchmarking environment" << endl;
    }

    bench.setup();

    // Writing

    if (with_info) {
        cout << "Writing workload" << endl;
    }

    start_time = current_time();

    total_volume = bench.write();

    total_write_time = time_diff(start_time, current_time());

    // Reading

    if (with_info) {
        cout << "Reading workload" << endl;
    }

    start_time = current_time();

    bench.read();

    total_read_time = time_diff(start_time, current_time());

    // Deleting

    if (with_info) {
        cout << "Deleting workload" << endl;
    }

    start_time = current_time();

    bench.remove();

    total_delete_time = time_diff(start_time, current_time());

    // Mixed

    if (with_info) {
        cout << "Mixed operations workload" << endl;
    }

    start_time = current_time();

    mixed_volume = bench.mixed();

    mixed_time = time_diff(start_time, current_time());

    // Cleanup

    if (with_info) {
        cout << "Cleaning up the benchmarking environment" << endl;
    }

    bench.teardown();

    // Information

    if (!with_info) return;

    // Rounding up (At least some time was taken)
    total_write_time = total_write_time == 0 ? 1 : total_write_time;
    total_read_time = total_read_time == 0 ? 1 : total_read_time;
    total_delete_time = total_delete_time == 0 ? 1 : total_delete_time;
    mixed_time = mixed_time == 0 ? 1 : mixed_time;

   

    cout << endl << "Total time of operations:" << endl;
    cout << "Writing workload total time: " << total_write_time << " ms" << endl;
    cout << "Reading workload total time: " << total_read_time << " ms" << endl;
    cout << "Deleting workload total time: " << total_delete_time << " ms" << endl;
     cout << "Total bytes: " << total_volume << endl;

    cout << endl << "Mixed workload total time: " << mixed_time << " ms" << endl;
    cout << "Mixed bytes: " << mixed_volume << endl;

    cout << endl << "Throughput of operations:" << endl;
    cout << "Writing workload throughput: " << ((long)(total_volume / total_write_time)) << " bytes/ms" << endl;
    cout << "Reading workload throughput: " << ((long)(total_volume / total_read_time)) << " bytes/ms" << endl;
    cout << "Deleting workload throughput: " << ((long)(total_volume / total_delete_time)) << " bytes/ms" << endl;
    cout << "Mixed workload throughput: " << ((long)(mixed_volume / mixed_time)) << " bytes/ms" << endl;
}