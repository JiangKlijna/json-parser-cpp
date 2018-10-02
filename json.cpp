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
