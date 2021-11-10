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
    // Validating the arguments

    if(argc != 5) {
        cout << "4 arguments are required:" << endl;
        cout << "1) Path to the configuration file" << endl;
        cout << "2) Number of documents to operate on" << endl;
        cout << "3) Whether to log or not ('yes')" << endl;
        cout << "4) # of seconds to sleep if needed" << endl;

        return 1;
    }

    // Parsing and checking the arguments

    string config_path = argv[1];
    string number_of_documents_str = argv[2];
    string show_info = argv[3];
    string seconds_to_wait_str = argv[4];

    int number_of_documents = stoi(number_of_documents_str);
    int seconds_to_wait = stoi(seconds_to_wait_str);

    if (number_of_documents <= 0) {
        throw "Number of documentsmust be a positive number";
    }

    // Waiting / Sleeping if specified by the input

    if (seconds_to_wait > 0) {
        wait_before_running(seconds_to_wait);
    }

    // Building configuration from the config-file and arguments

    benchmark_config config = load_benchmarking_config(config_path);

    config.number_of_documents = number_of_documents;

    // Running the actual benchmarking

    benchmark_data_store(ds, config, show_info == "yes");

    cout << "Finished (Close the console if it is still open)" << endl;

    return 0;
}
