/*
 * pjson.cpp
 *
 *  Created on: 2016-04-18
 *      Author: jiangKlijna
 */
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "pjson.h"

#define P(data) std::cout<<(data)<<std::endl
#define PL P(__LINE__)

//pjson::json_arr[5] not found
//pjson::json_obj[key] is not a bool
#define NOT_FOUND " not found"
#define NOT_A_TYPE " is not a "
#define NAME_BOOL "bool"
#define NAME_INT "int"
#define NAME_LONG "long"
#define NAME_DOUBLE "double"
#define NAME_OBJ "pjson::json_obj"
#define NAME_ARR "pjson::json_arr"
#define NAME_STR "pjson::json_str"

#define EMIPT ' '
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

#define ERROR(str) throw json_error(str)
#define CHECK(b, str) if(b){ERROR(str);}
#define CHECK_NULL(a, str) CHECK((nullptr == (a)), str)

using namespace std;
using namespace pjson;
//

json_node::json_node(json_status _status) :
	status(_status) {
}
/**
* class json_obj
*/
json_obj::json_obj() :
	json_node(json_status::obj), data(new map<string, json_node*>()) {
}
json_obj::json_obj(const string &str) :
	json_node(json_status::obj), data(json_tool::parser_obj(str)){
}
json_obj::json_obj(std::map<std::string, json_node*> *_data) :
	json_node(json_status::obj), data(_data){
}
json_obj::~json_obj(){
	delete data;
	P("json_obj::~json_obj");
}
//add or update element
json_obj* json_obj::put(const string &key, const char *value) {
	string str(value);
	delete (*data)[key];
	(*data)[key] = new json_str(str);
	return this;
}
json_obj* json_obj::put(const string &key, const string &value) {
	delete (*data)[key];
	(*data)[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const string &key, const bool &value) {
	delete (*data)[key];
	(*data)[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const string &key, const int &value) {
	delete (*data)[key];
	(*data)[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const string &key, const long &value) {
	delete (*data)[key];
	(*data)[key] = new json_str(value);
	return this;
}
json_obj* json_obj::put(const string &key, const double &value) {
	delete (*data)[key];
	(*data)[key] = new json_str(value);
	return this;
}
//erase element
json_obj* json_obj::erase(const string &key){
	delete (*data)[key];
	data->erase(key);
	return this;
}
//get element
string& json_obj::get_string(const string &key){
	map<string, json_node*>::iterator iter = data->find(key);
	CHECK(iter == data->end(), "is nullptr");
	// return iter->second->str();
	return *(new string("daksl"));
}
bool json_obj::get_bool(const string &key){
	map<string, json_node*>::iterator iter = data->find(key);
	CHECK(iter == data->end(), "is nullptr");
	CHECK(iter->second->status != json_status::str, "what type??");
	return json_tool::stob(key);
}
int json_obj::get_int(const string &key){
	map<string, json_node*>::iterator iter = data->find(key);
	CHECK(iter == data->end(), "is nullptr");
	CHECK(iter->second->status != json_status::str, "what type??");
	return json_tool::stoi(key);
}
long json_obj::get_long(const string &key){
	map<string, json_node*>::iterator iter = data->find(key);
	CHECK(iter == data->end(), "is nullptr");
	CHECK(iter->second->status != json_status::str, "what type??");
	return json_tool::stol(key);
}
double json_obj::get_double(const string &key){
	map<string, json_node*>::iterator iter = data->find(key);
	CHECK(iter == data->end(), "is nullptr");
	CHECK(iter->second->status != json_status::str, "what type??");
	return json_tool::stod(key);
}

string json_obj::str() {
	ostringstream buf;
	buf << CURLY_BRACES_L;
	map<string, json_node*>::iterator iter = data->begin();
	while (true) {
		buf << QUOTE << iter->first << QUOTE << COLON << iter->second->str();
		if (++iter == data->end()) {
			break;
		} else {
			buf << COMMA;
		}
	}
	buf << CURLY_BRACES_R;
	return buf.str();
}
json_obj::operator string(){
	return str();
}
unsigned json_obj::size(){
	return data->size();
}
bool json_obj::empty(){
	return data->empty();
}
void json_obj::clear(){
	data->clear();
}

/**
* class json_arr
*/
json_arr::json_arr() :
	json_node(json_status::arr), data(new list<json_node*>()) {
}
json_arr::json_arr(const string &str) :
	json_node(json_status::arr), data(json_tool::parser_arr(str)){
}
json_arr::json_arr(std::list<json_node*> *_data) :
	json_node(json_status::arr), data(_data){
}
json_arr::~json_arr(){
	// for(map<string, json_node*>::iterator iter = data->begin();){
	//
	// }
	delete data;
	P("json_arr::~json_arr");
}
//add element
json_arr* json_arr::put(const char *value) {
	string str(value);
	data->push_back(new json_str(str));
	return this;
}
json_arr* json_arr::put(const string &value) {
	data->push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const bool &value) {
	data->push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const int &value) {
	data->push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const long &value) {
	data->push_back(new json_str(value));
	return this;
}
json_arr* json_arr::put(const double &value) {
	data->push_back(new json_str(value));
	return this;
}
//erase element
json_arr* json_arr::erase(const unsigned &index){
	CHECK(index >= data->size(), "");
	// json_node *node = *(data->begin() + index);
	// data->erase(data->begin() + index);
	// delete node;
	return this;
}
	//update element
json_arr* json_arr::put(const int &value, const unsigned &index){

}

//to json string
string json_arr::str() {
	ostringstream buf;
	buf << SQUARE_BRACKETS_L;
	list<json_node*>::iterator iter = data->begin();
	while (*iter) {
		buf << (*iter)->str();
		if (++iter == data->end()) {
			break;
		} else {
			buf << COMMA;
		}
	}
	buf << SQUARE_BRACKETS_R;
	return buf.str();
}
json_arr::operator string(){
	return str();
}

unsigned json_arr::size(){
	return data->size();
}
bool json_arr::empty(){
	return data->empty();
}
void json_arr::clear(){
	data->clear();
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
json_str::~json_str(){
	P("json_str::~json_str::"+data);

}
string json_str::str() {
	return (str_t == json_str_t::json_s) ? (QUOTE + data + QUOTE) : (data);
}
json_str::operator string(){
	return data;
}
json_str::operator bool(){
	return json_tool::stob(data);
}
json_str::operator int(){
	return json_tool::stoi(data);
}
json_str::operator long(){
	return json_tool::stol(data);
}
json_str::operator double(){
	return json_tool::stod(data);
}

json_str* json_str::clone(){
	return new json_str(data, str_t);
}
unsigned json_str::size(){
	return data.size();
}
bool json_str::empty(){
	return data.empty();
}
void json_str::clear(){
	//TODO
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
inline int json_tool::stoi(const string &v){
	return atoi(v.c_str());
}
inline long json_tool::stol(const string &v){
	return atol(v.c_str());
}
inline double json_tool::stod(const string &v){
	return atof(v.c_str());
}
inline bool json_tool::stob(const string &v){
	if(v.size() == 4 && (v == "true" || v == "TRUE")){
		return true;
	}else if(v.size() == 5 && (v == "false" || v == "FALSE")){
		return false;
	}else{
		ERROR(v + " is not a bool");
	}
}

inline map<string, json_node*>* json_tool::parser_obj(const string &str){
	json_parser parser(str);
	return parser.read_obj();
}

inline list<json_node*>* json_tool::parser_arr(const string &str){
	json_parser parser(str);
	return parser.read_arr();
}

/**
* class json_error
*/
json_error::json_error(const std::string &s) : logic_error(s){}
json_error::operator string(){
	return what();
}
/**
* class json_parser
*/

json_parser::json_parser(const std::string &s) : str(s), pos(0), size(s.size()){}
void json_parser::trim(){
	while(str[pos] == EMIPT)
		pos++;
}
std::map<std::string, json_node*>* json_parser::read_obj(){
	trim();
	if(str[pos] != '{'){
		//TODO Exception
	}
	++pos;
	map<string, json_node*> *obj = new map<string, json_node*>();
	while(pos < size){

	}

	return obj;
}
std::list<json_node*>* json_parser::read_arr(){
	trim();
	if(str[pos] != '['){
		//TODO Exception
	}
	++pos;
	list<json_node*> *arr = new list<json_node*>();

	while(pos < size){
		json_node* node = nullptr;

		switch (str[pos]) {
			case ']':
			P("Num.2");
			++pos;
			return arr;
			case '{':

			node = new json_obj(read_obj());
			break;
			case '[':
			P("Num.1");

			node = new json_arr(read_arr());
			break;
			case ' ':
			case ',':
			P("Num.3");
			++pos;
			continue;
			default:
			node = read_str();
			break;
		}
		arr->push_back(node);
	}
	ERROR("no ]");
}

json_str* json_parser::read_str(){
	return nullptr;
}
void json_parser::read_key_value(std::map<std::string, json_node*>*){}
