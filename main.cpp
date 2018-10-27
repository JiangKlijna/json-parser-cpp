#include <iostream>
#include <cstdlib>
#include "json.h"

using namespace std;
using namespace json;

#define P(data) std::cout<<(data)<<std::endl
#define PR(str, data) std::cout<<(str)<<(data)<<std::endl
#define PL P(__LINE__)

int main() {
    json_arr arr;
    arr.add(json_str(1))
            .add(json_str("string"))
            .add(json_str(0.3))
            .add(json_str(false));
    PR("arr->size() : ", arr.size());
    PR("arr->string() : ", arr.str());

    json_obj obj;
    obj.put("key", "value");
    obj.put("number", 66);
    obj.put("bool", true);
    PR("obj->size() : ", obj.size());
    PR("obj->string() : ", obj.str());

    exit(EXIT_SUCCESS);
}
