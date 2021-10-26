#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "se_bench/data_stores/mock_data_store.h++"

using namespace std;

using json = nlohmann::json;

void mock_data_store::open(string working_directory_path) {
    cout << "Opening" << endl;
    cout << working_directory_path << endl;
}

void mock_data_store::save(string key, string value) {
    cout << "Saving" << endl;
    cout << key << endl;
    cout << value << endl;
}

string mock_data_store::load(string key) {
    cout << "Loading" << endl;
    cout << key << endl;

    json result = {{"key", key}};

    return result.dump();
}

void mock_data_store::close() {
    cout << "Closing" << endl;
}
