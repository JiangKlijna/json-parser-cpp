/*
 * pjson.cpp
 *
 *  Created on: 2016-04-18
 *      Author: jiang
 */
#include <sstream>
#include "pjson.h"
using namespace std;
using namespace pjson;
json_node::json_node(json_status _status) :
	status(_status) {
}
json_node::~json_node(){
	
}

//class json_obj
json_obj::json_obj() :
	json_node(json_status::obj) {
}
json_obj::~json_obj(){
}

json_obj* json_obj::put(const string &key, const char *value) {
	string str(value);
	delete data[key];
	data[key] = new json_str(str);
	return this;
}
json_obj* json_obj::put(const string &key, const string &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const std::string &key, const bool &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const std::string &key, const int &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const std::string &key, const long &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const std::string &key, const double &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}

string json_obj::toString() {
	ostringstream buf;
	buf << "{";
	map<std::string, json_node*>::iterator iter = data.begin();
	while (true) {
		json_str* node = dynamic_cast<json_str*>(iter->second);
		buf << "\"";
		buf << iter->first;
		buf << "\":";
		buf << node->toString();
		if (++iter == data.end()) {
			break;
		} else {
			buf << ",";
		}
	}
	buf << "}";
	return buf.str();
}
//class json_arr
json_arr::json_arr() :
	json_node(json_status::arr) {
}
json_arr::~json_arr(){
}

json_arr* json_arr::put(const char *value) {
	string str(value);
	data.push_back(new json_str(str));
	return this;
}
json_arr* json_arr::put(const string &value) {
	data.push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const bool &value) {
	data.push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const int &value) {
	data.push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const long &value) {
	data.push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const double &value) {
	data.push_back(new json_str(value));
	return this;
}

string json_arr::toString() {
	ostringstream buf;
	buf << "[";
	vector<json_node*>::iterator iter = data.begin();
	while (true) {
		json_str* node = dynamic_cast<json_str*>(*iter);
		buf << node->toString();
		if (++iter == data.end()) {
			break;
		} else {
			buf << ",";
		}
	}
	buf << "]";
	return buf.str();
}

//class json_str
json_str::json_str(const std::string &value, const json_str_t _str_t) :
	json_node(json_status::str), str_t(_str_t), data(value) {
}
json_str::json_str(const string &value) :
	json_node(json_status::str), str_t(json_str_t::json_s), data(value) {
}
json_str::json_str(const bool &value) :
	json_node(json_status::str), str_t(json_str_t::json_bool), data(value ? "true" : "false") {
}
json_str::json_str(const int &value) :
	json_node(json_status::str), str_t(json_str_t::json_int), data(json_tool::itos(value)) {
}
json_str::json_str(const long &value) :
	json_node(json_status::str), str_t(json_str_t::json_long), data(json_tool::ltos(value)) {
}
json_str::json_str(const double &value) :
	json_node(json_status::str), str_t(json_str_t::json_double), data(json_tool::dtos(value)) {
}
json_str::~json_str(){
}

string json_str::toString() {
	return (str_t == json_str_t::json_s) ? ("\"" + data + "\"") : (data);
}
json_str json_str::clone(){
	return new json_str(data, str_t);
}

//class json_tool
inline string json_tool::itos(const int &i) {
	char buf[12];
	sprintf(buf, "%d", i);
	string str(buf);
	return str;
}
inline string json_tool::ltos(const long &l) {
	char buf[24];
	sprintf(buf, "%ld", l);
	string str(buf);
	return str;
}
inline string json_tool::dtos(const double &d) {
	char buf[28];
	sprintf(buf, "%f", d);
	string str(buf);
	return str;
}
