#include <string>

#include "sqlite3.h"

#include "se_bench/data_stores/sqlite3_data_store.h++"
#include "se_bench/file_utilities.h++"

using namespace std;

// SQL

string setup_sql() {
    string table_setup = "CREATE TABLE store(key TEXT NOT NULL, value TEXT NOT NULL);";
    string index_setup = "CREATE INDEX idx ON store(key);";

    return table_setup + index_setup;
}

string selection_sql(string key) {
    return "SELECT value FROM store WHERE key = '" + key + "';";
}

string insertion_sql(string key, string value) {
    return "BEGIN;INSERT INTO store(key, value) VALUES ('" + key + "', '" + value + "');COMMIT;";
}

string deletion_sql(string key) {
    return "BEGIN;DELETE FROM store WHERE key = '" + key + "';COMMIT;";
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

void sqlite3_data_store::open(string working_directory) {
    string db_path = working_directory_path(working_directory, "bench.db");

    int rc = sqlite3_open(db_path.c_str(), &this->db);

    if(rc) {
        throw "Could not open SQLite database";
    }

    char* error_message;

    rc = sqlite3_exec(this->db, setup_sql().c_str(), NULL, 0, &error_message);

    if (rc) {
        throw error_message;
    }
}

string sqlite3_data_store::read(string key) {
    char* error_message;
    string value = "";

    int rc = sqlite3_exec(this->db, selection_sql(key).c_str(), selection_callback, &value, &error_message);

    if (rc) {
        throw error_message;
    }

    if (value == "") {
        throw "NOT FOUND";
    }

    return value;
}

void sqlite3_data_store::write(string key, string record) {
    char* error_message;

    int rc = sqlite3_exec(this->db, insertion_sql(key, record).c_str(), NULL, 0, &error_message);

    if (rc) {
        throw error_message;
    }
}

void sqlite3_data_store::remove(string key) {
    char* error_message;

    int rc = sqlite3_exec(this->db, deletion_sql(key).c_str(), NULL, 0, &error_message);

    if (rc) {
        throw error_message;
    }
}

void sqlite3_data_store::close() {
    sqlite3_close(this->db);
}
