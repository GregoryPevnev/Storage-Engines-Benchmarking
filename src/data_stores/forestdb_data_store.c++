#include <string>

#include "libforestdb/forestdb.h"

#include "se_bench/data_stores/forestdb_data_store.h++"

using namespace std;

void forestdb_data_store::open(string working_directory_path) {
    fdb_config config = fdb_get_default_config();
    fdb_kvs_config kvs_config = fdb_get_default_kvs_config();

    this->status = fdb_open(&this->fhandle, "/tmp/db_filename", &config);

    if (this->status != FDB_RESULT_SUCCESS) {
        throw "Could not open a ForestDB database file";
    }

    this->status = fdb_kvs_open_default(this->fhandle, &this->db, &kvs_config);

    if (this->status != FDB_RESULT_SUCCESS) {
        throw "Could not open a ForestDB key-value store";
    }
}

void forestdb_data_store::save(string key, string value) {
    this->status = fdb_set_kv(this->db, key.c_str(), key.size(), value.c_str(), value.size());

    if (this->status != FDB_RESULT_SUCCESS) {
        throw "Could not save a key-value pair in ForestDB";
    }

    this->status = fdb_commit(this->fhandle, FDB_COMMIT_NORMAL);

    if (this->status != FDB_RESULT_SUCCESS) {
        throw "Could not commit a key-value pair in ForestDB";
    }
}

string forestdb_data_store::load(string key) {
    size_t value_len;
    void *value;

    this->status = fdb_get_kv(this->db, key.c_str(), key.size(), &value, &value_len);

    if (this->status != FDB_RESULT_SUCCESS) {
        throw "Could not load a key-value pair in ForestDB";
    }

    string str_value((char*) value, value_len);

    return str_value;
}

void forestdb_data_store::close() {
    this->status = fdb_close(this->fhandle);

    if (this->status != FDB_RESULT_SUCCESS) {
        throw "Could not close a ForestDB database file";
    }
}
