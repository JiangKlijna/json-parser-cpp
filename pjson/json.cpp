//============================================================================
// Name        : json.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
using namespace std;

#include "pjson.h"

int main() {
	pjson::json_arr *arr = new pjson::json_arr();
	string str("c++str");
	arr->put("cstr")->put(str)->put(0.2356)->put(-68)->put(false);
	cout << arr->toString() << endl;
	delete arr;

	pjson::json_obj *obj = new pjson::json_obj();
	obj->put("key","value")->put("number",66)->put("key", "v2")->put("key", "v3");
	cout << obj->toString() << endl;
	delete obj;

	exit(EXIT_SUCCESS);
}
