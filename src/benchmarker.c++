#include <iostream>
#include <nlohmann/json.hpp>

#include "se_bench/benchmarker.h++"

using namespace std;

using json = nlohmann::json;

void test_benchmarker() {
    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

    cout << j.dump(4) << endl;
}
