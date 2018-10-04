/*
 * json.cpp
 *
 *  Created on: 2016-04-18
 *      Author: jiangKlijna
 */
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "json.h"

#define EMIPT ' '
#define COMMA ","
#define QUOTE "\""
#define SINGLE_QUOTE "'"
#define COLON ":"
#define SQUARE_BRACKETS_L "["
#define SQUARE_BRACKETS_R "]"
#define CURLY_BRACES_L "{"
#define CURLY_BRACES_R "}"

#define ERROR(str) throw json_error(str)
#define CHECK(b, str) if(b){ERROR(str);}
#define CHECK_NULL(a, str) CHECK((nullptr == (a)), str)

using namespace std;
using namespace json;


/**
* class json_str
*/
json_str::json_str(const string &v, const json_str_type t) :
        json_node(json_type::str), type(t), value(v) {
}

json_str::json_str(const string &value) :
        json_node(json_type::str), type(json_str_type::json_string), value(value) {
}

json_str::json_str(const bool &value) :
        json_node(json_type::str), type(json_str_type::json_bool), value(json_tool::btos(value)) {
}

json_str::json_str(const int &value) :
        json_node(json_type::str), type(json_str_type::json_int), value(json_tool::xtos(&value)) {
}

json_str::json_str(const long &value) :
        json_node(json_type::str), type(json_str_type::json_long), value(json_tool::xtos(&value)) {
}

json_str::json_str(const double &value) :
        json_node(json_type::str), type(json_str_type::json_double), value(json_tool::xtos(&value)) {
}

json_str::operator std::string() {
    return (type == json_str_type::json_string) ? (QUOTE + value + QUOTE) : (value);
}

json_str::operator bool() {
    return json_tool::stob(value);
}

json_str::operator int() {
    return json_tool::stoi(value);
}

json_str::operator long() {
    return json_tool::stol(value);
}

json_str::operator double() {
    return json_tool::stod(value);
}

size_t json_str::size() {
    return value.size();
}

bool json_str::empty() {
    return value.empty();
}

void json_str::clear() {
    value.clear();
}

/**
* class json_obj
*/
json_obj::json_obj() :
        json_node(json_type::obj), data(map<string, json_node>()) {
}

json_obj::json_obj(const string &str) : json_obj() {
    json_tool::parser_obj(str, data);
}

json_obj::json_obj(map<string, json_node> &data) :
        json_node(json_type::obj), data(data) {
}

json_obj::~json_obj() {
    printf("json_obj::~json_obj");
}

//add or update element and return point
json_node *json_obj::put(const string &key, const json_str &value) {
    auto iter = data.find(key);
    json_node *prev = iter->second;
    data.insert(pair<string, json_node>(key, value));
    return prev;
}

json_node *json_obj::put(const string &key, const json_obj &value) {
    auto iter = data.find(key);
    json_node *prev = iter->second;
    data.insert(pair<string, json_node>(key, value));
    return prev;
}

json_node *json_obj::put(const string &key, const json_arr &value) {
    auto iter = data.find(key);
    json_node *prev = iter->second;
    data.insert(pair<string, json_node>(key, value));
    return prev;
}

//erase element and return point
json_node *json_obj::erase(const string &key) {
    auto node = data.find(key);
    data.erase(key);
    return node->second;
}

//get element
json_str &json_obj::get_json_str(const string &key) {
    auto iter = data.find(key);
    CHECK(iter == data.end(), key + " is nullptr");
    CHECK(iter->second.type != json_type::str, key + " is not json_str");
    return iter->second;
}

json_arr &json_obj::get_json_arr(const string &key) {
    auto iter = data.find(key);
    CHECK(iter == data.end(), key + " is nullptr");
    CHECK(iter->second.type != json_type::arr, key + " is not json_arr");
    return iter->second;
}

json_obj &json_obj::get_json_obj(const string &key) {
    auto iter = data.find(key);
    CHECK(iter == data.end(), key + " is nullptr");
    CHECK(iter->second.type != json_type::obj, key + " is not json_obj");
    return iter->second;
}

json_obj::operator std::string() {
    return "{}";
}

size_t json_obj::size() {
    return data.size();
}

bool json_obj::empty() {
    return data.empty();
}

void json_obj::clear() {
    data.clear();
}

/**
* class json_arr
*/
json_arr::json_arr() :
        json_node(json_type::arr), data(std::vector<json_node>()) {
}

json_arr::json_arr(const string &str) : json_arr() {
    json_tool::parser_arr(str, data);
}

json_arr::json_arr(std::vector<json_node> &data) :
        json_node(json_type::arr), data(data) {
}

//add element
json_arr &json_arr::add(const json_str &value) {
    data.push_back(value);
    return *this;
}

json_arr &json_arr::add(const json_obj &value) {
    data.push_back(value);
    return *this;
}

json_arr &json_arr::add(const json_arr &value) {
    data.push_back(value);
    return *this;
}

//erase element
json_node *json_arr::erase(const size_t &index) {
    CHECK(index >= data.size(), "index out of range");
    auto node = data.begin() + index;
    data.erase(node);
    return node.base();
}

//update element
json_arr &json_arr::put(const json_str &value, const size_t &index) {
    data.insert(data.begin() + index, value);
    return *this;
}

json_arr &json_arr::put(const json_obj &value, const size_t &index) {
    data.insert(data.begin() + index, value);
    return *this;
}

json_arr &json_arr::put(const json_arr &value, const size_t &index) {
    data.insert(data.begin() + index, value);
    return *this;
}

//get element
json_str &json_arr::get_json_str(const size_t &index) {
    CHECK(index >= data.size(), "index out of range");
    auto base = (data.begin() + index).base();
    CHECK(base->type != json_type::str, "json_arr[" + json_tool::xtos(&index) + "] is not json_str");
    return (json_str &) (*base);
}

json_arr &json_arr::get_json_arr(const size_t &index) {
    CHECK(index >= data.size(), "index out of range");
    auto base = (data.begin() + index).base();
    CHECK(base->type != json_type::arr, "json_arr[" + json_tool::xtos(&index) + "] is not json_arr");
    return (json_arr &) (*base);
}


json_obj &json_arr::get_json_obj(const size_t &index) {
    CHECK(index >= data.size(), "index out of range");
    json_node *base = (data.begin() + index).base();
    CHECK(base->type != json_type::obj, "json_arr[" + json_tool::xtos(&index) + "] is not json_obj");
    return (json_obj &) (*base);
}

// json_node
json_arr::operator std::string() {
    return "[]";
}

size_t json_arr::size() {
    return data.size();
}

bool json_arr::empty() {
    return data.empty();
}

void json_arr::clear() {
    data.clear();
}
