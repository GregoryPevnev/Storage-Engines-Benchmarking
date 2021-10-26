#include <string>
#include <ctime>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "se_bench/benchmarker.h++"

namespace fs = std::__fs::filesystem;

using namespace std;

using json = nlohmann::json;

// Working-Directories operations (Creation and deletion)

string new_working_directory_name() {
    time_t t = time(0);

    string time_suffix = to_string(t);

    return "data_" + time_suffix;
}

string create_working_directory() {
    fs::path tmp_directory = fs::temp_directory_path();
    
    string working_directory_name = new_working_directory_name();

     fs::path working_directory = tmp_directory / working_directory_name;

     fs::create_directories(working_directory);

     return working_directory.u8string();
}

void delete_working_directory(string working_directory) {
    fs::path del_path = fs::u8path(working_directory);

    fs::remove_all(del_path);
}

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
