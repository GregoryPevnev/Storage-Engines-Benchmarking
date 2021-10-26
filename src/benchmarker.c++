#include <string>
#include <nlohmann/json.hpp>

#include "se_bench/file_utilities.h++"
#include "se_bench/benchmarker.h++"

using namespace std;

using json = nlohmann::json;

// Mismatch error

struct mismatch_error {
    string key;
    string value;

    string expected_key;

    mismatch_error(string key, string value, string expected_key): key(key), value(value), expected_key(expected_key) {}
};

// Implementation

void benchmarker::setup() {
    this->working_directory = create_working_directory();

    this->ds->open(this->working_directory);
}

long benchmarker::write() {
    string key;
    string value;

    long total_size_written = 0;

    for(long document_num = 1; document_num <= this->number_of_documents; document_num++) {
        key = to_string(document_num);

        this->document_prototype[this->document_key_name] = key;

        value = this->document_prototype.dump();

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
            throw mismatch_error(key, value, check_key);
        }
    }
}

void benchmarker::teardown() {
    this->ds->close();

    delete_working_directory(this->working_directory);
}
