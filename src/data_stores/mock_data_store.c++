#include <string>
#include <nlohmann/json.hpp>

#include "se_bench/data_stores/mock_data_store.h++"

#define MOCK_KEY_NAME "id"

using namespace std;

using json = nlohmann::json;

void mock_data_store::open(string working_directory_path) {}

string mock_data_store::read(string key) {
    json result = {{MOCK_KEY_NAME, key}};

    return result.dump();
}

void mock_data_store::write(string key, string record) {}

void mock_data_store::remove(string key) {}

void mock_data_store::close() {}
