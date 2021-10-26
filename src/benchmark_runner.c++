#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "se_bench/benchmarker.h++"

using namespace std;

// Giving profiling some time to start if needed
void wait_before_running(int seconds) {
    this_thread::sleep_for(chrono::milliseconds(seconds * 1000));
}

int run_benchmarking(data_store* ds, int argc, char** argv) {
    if(argc != 4) {
        cout << "3 arguments are required:" << endl;
        cout << "1) Path to the configuration file" << endl;
        cout << "2) Whether to log or not ('yes')" << endl;
        cout << "3) # of seconds to sleep if needed" << endl;

        return 1;
    }

    string config_path = argv[1];
    string show_info = argv[2];
    string seconds_to_wait_str = argv[3];

    int seconds_to_wait = stoi(seconds_to_wait_str);

    if (seconds_to_wait > 0) {
        wait_before_running(seconds_to_wait);
    }

    benchmark_config config = load_benchmarking_config(config_path);

    benchmark_data_store(ds, config, show_info == "yes");

    cout << "Finished (Close the console if it is still open)" << endl;

    return 0;
}
