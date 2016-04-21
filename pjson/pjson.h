/*
 * pjson.h
 *
 *  Created on: 2016-04-18
 *      Author: jiangKlijna
 */
#ifndef JIANGKLIJNA_PJSON_H__
#define JIANGKLIJNA_PJSON_H__
#include <map>
#include <vector>

namespace pjson {

class json_node;
class json_obj;
class json_arr;
class json_str;
class json_error;
class json_tool;

enum json_status {
	arr, obj, str
};
enum json_str_t {
	json_s, json_bool, json_int, json_long, json_double
};

class json_node {
protected:
	json_node(json_status);
public:
	const json_status status;
	virtual std::string toString() = 0;
	virtual unsigned size() = 0;
	virtual bool empty() = 0;
	virtual ~json_node() = default;
};

class json_obj: public json_node {
private:
	std::map<std::string, json_node*> *data;
public:
	json_obj();
	json_obj(const std::string &str);
	~json_obj();
	//add or update element
	json_obj* put(const std::string &key, const char *value);
	json_obj* put(const std::string &key, const std::string &value);
	json_obj* put(const std::string &key, const bool &value);
	json_obj* put(const std::string &key, const int &value);
	json_obj* put(const std::string &key, const long &value);
	json_obj* put(const std::string &key, const double &value);
	// json_obj* put(const std::string &key, const json_obj &value);
	// json_obj* put(const std::string &key, const json_arr &value);

	//erase element
	json_obj* erase(const std::string &key);

	//get element
	std::string& get_string(const std::string &key);
	bool get_bool(const std::string &key);
	int get_int(const std::string &key);
	long get_long(const std::string &key);
	double get_double(const std::string &key);
	// json_arr& get_json_arr(const std::string &key);
	// json_obj& get_json_obj(const std::string &key);

	std::string toString();
	//json_obj* clone();
	unsigned size();
	bool empty();
};

class json_arr: public json_node {
private:
	std::vector<json_node*> *data;
public:
	json_arr();
	json_arr(const std::string &str);
	~json_arr();
	//add element
	json_arr* put(const char *value);
	json_arr* put(const std::string &value);
	json_arr* put(const bool &value);
	json_arr* put(const int &value);
	json_arr* put(const long &value);
	json_arr* put(const double &value);
	// json_arr* put(const json_obj &value);
	// json_arr* put(const json_arr &value);

	//erase element
	json_arr* erase(const unsigned &index);
	//update element
	json_arr* put(const char *value, const unsigned &index);
	json_arr* put(const std::string &value, const unsigned &index);
	json_arr* put(const bool &value, const unsigned &index);
	json_arr* put(const int &value, const unsigned &index);
	json_arr* put(const long &value, const unsigned &index);
	json_arr* put(const double &value, const unsigned &index);
	// json_arr* put(const json_obj &value, const unsigned &index);
	// json_arr* put(const json_arr &value, const unsigned &index);

	//get element
	// std::string& get_string(const unsigned &index);
	// bool& get_bool(const unsigned &index);
	// int& get_int(const unsigned &index);
	// long& get_long(const unsigned &index);
	// double& get_double(const unsigned &index);
	// json_arr& get_json_arr(const unsigned &index);
	// json_obj& get_json_obj(const unsigned &index);

	std::string toString();
	//json_arr* clone();
	unsigned size();
	bool empty();
};

class json_str: public json_node {
	friend class json_obj;
	friend class json_arr;
private:
	const json_str_t str_t;
	const std::string data;
	json_str(const std::string &value, const json_str_t _str_t);
	json_str(const std::string &value);
	json_str(const bool &value);
	json_str(const int &value);
	json_str(const long &value);
	json_str(const double &value);
public:
	std::string toString();
	json_str* clone();
	unsigned size();
	bool empty();
	~json_str();
};
struct json_tool {

	inline static std::string itos(const int &);
	inline static std::string ltos(const long &);
	inline static std::string dtos(const double &);

	inline static int stoi(const std::string &);
	inline static long stol(const std::string &);
	inline static double stod(const std::string &);
	inline static bool stob(const std::string &);

	inline static std::map<std::string, json_node*>* parse_obj(const std::string &);
	inline static std::vector<json_node*>* parse_arr(const std::string &);

};
struct json_error : public std::logic_error{
	json_error(const std::string &s) : std::logic_error(s){}
};
}
#endif
