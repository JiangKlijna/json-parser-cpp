#ifndef JIANGKLIJNA_PJSON_H__
#define JIANGKLIJNA_PJSON_H__
#include <iostream>
#include <map>
#include <vector>

#define PT std::cout<<__LINE__<<std::endl;

namespace pjson {

class json_obj;
class json_arr;
class json_str;

enum json_status {
	arr, obj, str
};
enum json_str_t {
	json_s, json_bool, json_int, json_long, json_double
};

class json_node {
protected:
	const json_status status;
	json_node(json_status);
public:
	virtual std::string toString() = 0;
	virtual ~json_node() = 0;
};

class json_obj: public json_node {
private:
	std::map<std::string, json_node*> data;
public:
	json_obj();
	json_obj* put(const std::string &key, const char *value);
	json_obj* put(const std::string &key, const std::string &value);
	json_obj* put(const std::string &key, const bool &value);
	json_obj* put(const std::string &key, const int &value);
	json_obj* put(const std::string &key, const long &value);
	json_obj* put(const std::string &key, const double &value);
	// json_obj* put(const std::string &key, const json_obj &value);
	// json_obj* put(const std::string &key, const json_arr &value);

	std::string toString();
	//json_obj clone();
	~json_obj();
};

class json_arr: public json_node {
private:
	std::vector<json_node*> data;
public:
	json_arr();
	json_arr(const std::string &data);
	json_arr* put(const char *value);
	json_arr* put(const std::string &value);
	json_arr* put(const bool &value);
	json_arr* put(const int &value);
	json_arr* put(const long &value);
	json_arr* put(const double &value);
	// json_arr* put(const json_obj &value);
	// json_arr* put(const json_arr &value);

	std::string toString();
	//json_arr clone();
	~json_arr();
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
	json_str clone();
	~json_str();
};
struct json_tool {

	inline static std::string itos(const int &);
	inline static std::string ltos(const long &);
	inline static std::string dtos(const double &);
};
}
#endif
