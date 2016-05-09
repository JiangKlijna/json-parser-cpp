#include <iostream>
#include <cstdlib>
using namespace std;

#include "pjson.h"

#define P(data) std::cout<<(data)<<std::endl
#define PR(str, data) std::cout<<(str)<<(data)<<std::endl
#define PL P(__LINE__)


int main(void) {
	pjson::json_arr *arr = new pjson::json_arr("[  [ ] ]");
	const char* cstr = "cstr";
	string cppstr("cppstr");
	arr->put(cstr)->put(cppstr)->put(0.2356)->put(-68)->put(false);
	// arr->erase(4);TODO
	PR("arr->size() : ", arr->size());
	PR("arr->str() : ", arr->str());
	delete arr;

	pjson::json_obj *obj = new pjson::json_obj();
	obj->put("key","value")->put("number",66)->put("key", "v2")->put("key", "v3");
	obj->erase("number");
	try{
		obj->get_string("null key");
	}catch(pjson::json_error &e){
		P((string) e);
	}
	P(obj->str());
	delete obj;

	exit(EXIT_SUCCESS);
}
