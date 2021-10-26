#include <string>
#include <ctime>
#include <filesystem>

namespace fs = std::__fs::filesystem;

using namespace std;

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

string working_directory_path(string working_directory, string working_path) {
    fs::path wd(working_directory);
    fs::path wp(working_path);
    fs::path full = wd / wp;

    return full.u8string();
}
