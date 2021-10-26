#include <iostream>
#include <string>

#include "sqlite3.h"

#include "se_bench/data_stores/sqlite3_data_store.h++"

using namespace std;

// SQL

string setup_sql() {
    string table_setup = "CREATE TABLE store(key TEXT NOT NULL, value TEXT NOT NULL);";
    string index_setup = "CREATE INDEX idx ON store(key);";

    return table_setup + index_setup;
}

string insertion_sql(string key, string value) {
    return "BEGIN;INSERT INTO store(key, value) VALUES ('" + key + "', '" + value + "');COMMIT;";
}

string selection_sql(string key) {
    return "SELECT value FROM store WHERE key = '" + key + "';";
}

// Query Processing

// Called for EACH resulting record
static int selection_callback(void* data, int columns, char** values, char** column_names) {
    string* result_data = (string*) data;

    // Only taking the first value - Others are UNEEDED
    *result_data = values[0];

    return 0;
}

// Data Store

void sqlite3_data_store::open(string working_directory_path) {
    string db_path = working_directory_path + "/bench.db";

    int rc = sqlite3_open(db_path.c_str(), &this->db);

    if(rc) {
        throw "Could not open SQLite database";
    }

    char* error_message;

    rc = sqlite3_exec(this->db, setup_sql().c_str(), NULL, 0, &error_message);

    if(rc) {
        throw error_message;
    }
}

void sqlite3_data_store::save(string key, string value) {
    char* error_message;

    int rc = sqlite3_exec(this->db, insertion_sql(key, value).c_str(), NULL, 0, &error_message);

    if(rc) {
        throw error_message;
    }
}

string sqlite3_data_store::load(string key) {
    char* error_message;
    string value = "";

    int rc = sqlite3_exec(this->db, selection_sql(key).c_str(), selection_callback, &value, &error_message);

    if(rc) {
        throw error_message;
    }

    if (value == "") {
        throw "NOT FOUND";
    }

    return value;
}

void sqlite3_data_store::close() {
    sqlite3_close(this->db);
}
