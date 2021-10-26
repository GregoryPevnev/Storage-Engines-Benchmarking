#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "se_bench/benchmarker.h++"

using namespace std;

using json = nlohmann::json;

void benchmarker::setup() {
    // TODO: Create randomly based on a timestamp -> "[timestamp]_data"

    // TODO: Creating the current working directory -> "working_directory"
    this->working_directory = "test_working_directory";

    this->ds->open(this->working_directory);
}

long benchmarker::write() {
    string key;
    json document;
    string value;

    long total_size_written;

    for(long document_num = 1; document_num <= this->number_of_documents; document_num++) {
        key = to_string(document_num);

        document = this->document_prototype;
        document[this->document_key_name] = key;

        value = document.dump();

        this->ds->save(key, value);

        total_size_written += value.size();
    }

    return total_size_written;
}

void benchmarker::read() {
    string key;
    string value;
    json document;
    string check_key;

    for(long document_num = 1; document_num <= this->number_of_documents; document_num++) {
        key = to_string(document_num);

        value = this->ds->load(key);

        document = json::parse(value);

        check_key = document[this->document_key_name].get<string>();

        if(check_key != key) {
            // TODO: Throwing an error
            cout << "MISMATCH" << endl;
            cout << key << endl;
            cout << value << endl;
        }
    }
}

void benchmarker::teardown() {
    // TODO: Removing the current working directory -> "working_directory"
    this->ds->close();
}

benchmark_config load_benchmarking_config() {
    // TODO: Reading config from a file -> Parsing as JSON
    json config_data = {
        {"number_of_documents", 1},
        {"document_key_name", "key"},
        {
            {"key", "KEY"},
            {"value", "some value for testing"}
        }
    };

    benchmark_config config;

    config.number_of_documents = config_data["number_of_documents"].get<long>();
    config.document_key_name = config_data["document_key_name"].get<string>();
    config.document_prototype = config_data["document_prototype"];

    return config;
}

void benchmark_data_store(data_store* ds, benchmark_config config) {
    benchmarker bench(ds, config.document_prototype, config.document_key_name, config.number_of_documents);

    // TODO: Logging and Timing

    bench.setup();

    bench.write();

    bench.read();

    bench.teardown();
}
