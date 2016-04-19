/*
 * pjson.cpp
 *
 *  Created on: 2016-04-18
 *      Author: jiang
 */
#include "pjson.h"
using namespace pjson;
json_node::json_node(json_status _status):status(_status){}

//class json_obj
json_obj* json_obj::put(const string str, const string value){
		data[str] = new json_str(value);
		return this;
}
string json_obj::toString(){
	return "{}";
}
//class json_arr
json_arr::json_arr():json_node(json_status::arr){}

json_arr* json_arr::put(const string value){
		data.push_back(new json_str(value));
		return this;
}

string json_arr::toString(){
	string s("[");
	for (vector<json_node*>::iterator iter = data.begin(); iter != data.end(); iter++){
		json_str* node = dynamic_cast<json_str*>(*iter);
		s+=node->toString();
    }
	s+="]";
	return s;
}

//class json_str
json_str::json_str(string str):json_node(json_status::str),data(str){}

string json_str::toString(){
	return "\""+data+"\"";
}

