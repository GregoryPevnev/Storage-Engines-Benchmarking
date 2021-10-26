#include <string>

#include "leveldb/db.h"

#include "se_bench/data_stores/leveldb_data_store.h++"
#include "se_bench/file_utilities.h++"

using namespace std;

void leveldb_data_store::open(string working_directory) {
    string db_path = working_directory_path(working_directory, "bench");

    leveldb::Options options;
    options.create_if_missing = true;

    this->status = leveldb::DB::Open(options, db_path, &this->db);

    if(!status.ok()) {
        string err = status.ToString();

        throw err;
    }
}

void leveldb_data_store::save(string key, string value) {
    leveldb::WriteOptions options;

    // Would make it as bad as SQLite (Even worse in some cases)
    // options.sync = true;

    this->status = this->db->Put(options, key, value);

    if(!status.ok()) {
        string err = status.ToString();

        throw err;
    }
}

string leveldb_data_store::load(string key) {
    leveldb::ReadOptions options;

    string value;

    this->status = this->db->Get(options, key, &value);

    if(!status.ok()) {
        string err = status.ToString();

        throw err;
    }

    return value;
}

void leveldb_data_store::close() {
    delete this->db;
}
