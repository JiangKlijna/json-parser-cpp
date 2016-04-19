#ifndef JIANGKLIJNA_PJSON_H__
#define JIANGKLIJNA_PJSON_H__
#include <iostream>
#include <map>
#include <vector>

using namespace std;
namespace pjson {

class json_obj;
class json_arr;
class json_str;

enum json_status {arr,obj,str};

class json_node {
private:
	
public:
	const json_status status;
	json_node(json_status);
	
	virtual string toString() = 0;
	//virtual string clone() = 0;
	
};

class json_obj: public json_node {
private:
	map<string, json_node*> data;
public:
	json_obj* put(const string, const string);
	// json_obj* put(const string&, const bool&);
	// json_obj* put(const string&, const char&);
	// json_obj* put(const string&, const int&);
	// json_obj* put(const string&, const long&);
	// json_obj* put(const string&, const float&);
	// json_obj* put(const string&, const double&);
	// json_obj* put(const string&, const json_obj&);
//	json_obj* put(const string&, const json_arr&);

string toString();
};

class json_arr: public json_node {
private:
	vector<json_node*> data;
public:
	json_arr();
	json_arr* put(const string);
	// json_arr* put(const bool&);
	// json_arr* put(const char&);
	// json_arr* put(const int&);
	// json_arr* put(const long&);
	// json_arr* put(const float&);
	// json_arr* put(const double&);
//	json_arr* put(const json_obj&);
	// json_arr* put(const json_arr&);

string toString();
};

class json_str: public json_node {
	friend class json_obj;
	friend class json_arr;
	string data;
public:

	json_str(string);
	string toString();
};
}
#endif
