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
    arr.add(1).add("string").add(0.3).add(false);
    PR("arr->size() : ", arr.size());
    PR("arr->string() : ", string(arr));

    json_obj obj;
    obj.put("key", "value");
    obj.put("number", 66);
    obj.put("bool", true);
    PR("obj->size() : ", obj.size());
    PR("obj->string() : ", string(obj));

	exit(EXIT_SUCCESS);
}
