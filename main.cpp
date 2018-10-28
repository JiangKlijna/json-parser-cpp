#include <iostream>
#include <cstdlib>
#include "json.h"

using namespace std;
using namespace json;

#define P(data) std::cout<<(data)<<std::endl
#define PR(str, data) std::cout<<__LINE__<<":\t"<<(str)<<(data)<<std::endl
#define PL P(__LINE__)

void testArray() {
    json_arr arr;
    arr.add(json_str(1))
            .add(json_str("string"))
            .add(json_str(0.3))
            .add(json_str(false));
    PR("arr->size() : ", arr.size());
    PR("arr->string() : ", arr.str());
    arr.erase(0);
    PR("arr->size() : ", arr.size());
    PR("arr->empty() : ", arr.empty());
    arr.put(json_str("new"), 0);
    PR("arr->string() : ", arr.str());
    json_arr arr1;
    arr1.add(json_str(1))
            .add(json_str("string"))
            .add(json_str(0.3))
            .add(json_str(false));
    json_obj obj1;
    obj1.put("key", "value");
    obj1.put("number", 66);
    obj1.put("bool", true);
    arr.add(arr1);
    arr.add(obj1);
    PR("arr->string() : ", arr.str());
    arr.clear();
    PR("arr->string() : ", arr.str());
}

void testObject() {
    json_obj obj;
    obj.put("key", "value");
    obj.put("number", 66);
    obj.put("bool", true);
    PR("obj->size() : ", obj.size());
    PR("obj->string() : ", obj.str());
    obj.erase("key");
    PR("obj->size() : ", obj.size());
    PR("obj->empty() : ", obj.empty());
    json_arr arr1;
    arr1.add(json_str(1))
            .add(json_str("string"))
            .add(json_str(0.3))
            .add(json_str(false));
    json_obj obj1;
    obj1.put("key", "value");
    obj1.put("number", 66);
    obj1.put("bool", true);
    obj.put("array", arr1);
    obj.put("object", obj1);
    PR("obj->string() : ", obj.str());
    obj.clear();
    PR("obj->string() : ", obj.str());
}

int main() {
    testArray();
    testObject();
    exit(EXIT_SUCCESS);
}
