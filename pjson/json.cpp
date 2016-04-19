//============================================================================
// Name        : json.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include <cstdlib>
using namespace std;

#include "pjson.h"

int main() {
	pjson::json_arr *arr = new pjson::json_arr();
	arr->put("123")->put("abc")->put("!@#");
	cout << arr->toString() << endl; // prints !!!Hello World!!!
	delete arr;
	return 0;
	//exit(EXIT_SUCCESS);
}
