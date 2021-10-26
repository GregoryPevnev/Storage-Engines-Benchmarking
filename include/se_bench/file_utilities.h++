#ifndef FILE_UTILS
#define FILE_UTILS

#include <string>

using namespace std;

string create_working_directory();

void delete_working_directory(string working_directory);

string working_directory_path(string working_directory, string working_path);

#endif
