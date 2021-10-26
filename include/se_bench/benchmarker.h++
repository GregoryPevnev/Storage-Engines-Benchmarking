#ifndef BENCHMARKER
#define BENCHMARKER

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

class data_store {
public:
    virtual void open(string working_directory_path) = 0;

    virtual string load(string key) = 0;

    virtual void save(string key, string value) = 0;

    virtual void close() = 0;
};

struct benchmark_config {
    long number_of_documents;
    string document_key_name;
    json document_prototype;
};

class benchmarker {
private:
    data_store* ds;

    json document_prototype;
    string document_key_name;
    long number_of_documents;

    string working_directory; // TODO: Using path + Creating on setup
public:
    benchmarker(data_store* ds, json document_prototype, string document_key_name, long number_of_documents):
        ds(ds), document_prototype(document_prototype), document_key_name(document_key_name), number_of_documents(number_of_documents) {}

    void setup(); // Preparing for reading and writing

    long write(); // Writing the specified number of documents according to the prototype -> Returning the total size

    void read(); // Reading all the written documents and verifying their correctness

    void teardown(); // Cleaning up the connections, data and files
};

benchmark_config load_benchmarking_config(string config_path);

void benchmark_data_store(data_store* ds, benchmark_config config, bool with_info = false);

#endif
