/*
 * pjson.cpp
 *
 *  Created on: 2016-04-18
 *      Author: jiangKlijna
 */
#include <iostream>
#include <sstream>
#include "pjson.h"

#define P(data) std::cout<<(data)<<std::endl;
#define PL P(__LINE__)

#define COMMA ","
#define QUOTE "\""
#define SINGLE_QUOTE "'"
#define COLON ":"
#define SQUARE_BRACKETS_L "["
#define SQUARE_BRACKETS_R "]"
#define CURLY_BRACES_L "{"
#define CURLY_BRACES_R "}"

#define btos(b) (b) ? "true" : "false"
#define xtos(x) ostringstream buf;buf << (x);return buf.str();

using namespace std;
using namespace pjson;
json_node::json_node(json_status _status) :
	status(_status) {
}
/**
* class json_obj
*/
json_obj::json_obj() :
	json_node(json_status::obj) {
}
json_obj::~json_obj(){
	P("json_obj::~json_obj");
}
//add or update element
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
json_obj* json_obj::put(const string &key, const bool &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const string &key, const int &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const string &key, const long &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const string &key, const double &value) {
	delete data[key];
	data[key] = new json_str(value);
	return this;
}

string json_obj::toString() {
	ostringstream buf;
	buf << CURLY_BRACES_L;
	map<string, json_node*>::iterator iter = data.begin();
	while (true) {
		buf << QUOTE << iter->first << QUOTE << COLON << iter->second->toString();
		if (++iter == data.end()) {
			break;
		} else {
			buf << COMMA;
		}
	}
	buf << CURLY_BRACES_R;
	return buf.str();
}
/**
* class json_arr
*/
json_arr::json_arr() :
	json_node(json_status::arr) {
}
json_arr::~json_arr(){
	P("json_arr::~json_arr");
}
//add element
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
//to json string
string json_arr::toString() {
	ostringstream buf;
	buf << SQUARE_BRACKETS_L;
	vector<json_node*>::iterator iter = data.begin();
	while (true) {
		buf << (*iter)->toString();
		if (++iter == data.end()) {
			break;
		} else {
			buf << COMMA;
		}
	}
	buf << SQUARE_BRACKETS_R;
	return buf.str();
}
/**
* class json_str
*/
json_str::json_str(const string &value, const json_str_t _str_t) :
	json_node(json_status::str), str_t(_str_t), data(value) {
}
json_str::json_str(const string &value) :
	json_node(json_status::str), str_t(json_str_t::json_s), data(value) {
}
json_str::json_str(const bool &value) :
	json_node(json_status::str), str_t(json_str_t::json_bool), data(btos(value)) {
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

string json_str::toString() {
	return (str_t == json_str_t::json_s) ? (QUOTE + data + QUOTE) : (data);
}
json_str json_str::clone(){
	return new json_str(data, str_t);
}
/**
* class json_tool
*/
inline string json_tool::itos(const int &i) {
	xtos(i);
}
inline string json_tool::ltos(const long &l) {
	xtos(l);
}
inline string json_tool::dtos(const double &d) {
	xtos(d);
}
