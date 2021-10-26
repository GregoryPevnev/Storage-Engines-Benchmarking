#include <fstream>
#include <streambuf>
#include <string>
#include <nlohmann/json.hpp>

#include "se_bench/benchmarker.h++"

using namespace std;

using json = nlohmann::json;

string load_config_from_file(string config_path) {
    ifstream t(config_path);

    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

    return str;
}

benchmark_config load_benchmarking_config(string config_path) {
    // TODO: Reading config from a file -> Parsing as JSON
    string config_data_str = load_config_from_file(config_path);

    json config_data = json::parse(config_data_str);

    benchmark_config config;

    config.number_of_documents = config_data["number_of_documents"].get<long>();
    config.document_key_name = config_data["document_key_name"].get<string>();
    config.document_prototype = config_data["document_prototype"];

    return config;
}
