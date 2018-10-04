/*
 * json.h
 *
 *  Created on: 2016-04-18
 *      Author: jiangKlijna
 */
#ifndef JIANGKLIJNA_JSON_H__
#define JIANGKLIJNA_JSON_H__

#include <map>
#include <vector>

namespace json {

    class json_node;

    class json_obj;

    class json_arr;

    class json_str;

    class json_tool;

    class json_error;

    enum json_type {
        arr, obj, str
    };

    enum json_str_type {
        json_string, json_bool, json_int, json_long, json_double
    };

    class json_node {
    protected:
        explicit json_node(json_type t) : type(t) {}

    public:
        const json_type type;

        virtual operator std::string() = 0;

        virtual size_t size() = 0;

        virtual void clear() = 0;

        virtual bool empty() = 0;
    };

    class json_str : public json_node {
        std::string value;
    public:
        const json_str_type type;

        json_str(const std::string &v, json_str_type t);

        json_str(const std::string &v);

        json_str(const bool &v);

        json_str(const int &v);

        json_str(const long &v);

        json_str(const double &v);

        operator bool();

        operator int();

        operator long();

        operator double();

        // json_node override func
        operator std::string() override;

        size_t size() override;

        void clear() override;

        bool empty() override;
    };

    class json_obj : public json_node {
        std::map<std::string, json_node> data;
    public:
        json_obj();

        explicit json_obj(const std::string &json);

        explicit json_obj(std::map<std::string, json_node> &data);

        ~json_obj();

        //add or update element
        json_node *put(const std::string &key, const json_str &value);

        json_node *put(const std::string &key, const json_obj &value);

        json_node *put(const std::string &key, const json_arr &value);

        //erase element and return point
        json_node *erase(const std::string &key);

        //get element
        json_str &get_json_str(const std::string &key);

        json_arr &get_json_arr(const std::string &key);

        json_obj &get_json_obj(const std::string &key);

        // json_node override func
        operator std::string() override;

        size_t size() override;

        void clear() override;

        bool empty() override;
    };

    class json_arr : public json_node {
        std::vector<json_node> data;
    public:
        json_arr();

        explicit json_arr(const std::string &json);

        explicit json_arr(std::vector<json_node> &data);

        ~json_arr();

        //add element
        json_arr &add(const json_str &value);

        json_arr &add(const json_obj &value);

        json_arr &add(const json_arr &value);

        //erase element and return point
        json_node *erase(const size_t &index);

        //update element
        json_arr &put(const json_str &value, const size_t &index);

        json_arr &put(const json_obj &value, const size_t &index);

        json_arr &put(const json_arr &value, const size_t &index);

        //get element
        json_str &get_json_str(const size_t &index);

        json_arr &get_json_arr(const size_t &index);

        json_obj &get_json_obj(const size_t &index);

        // json_node
        operator std::string() override;

        size_t size() override;

        void clear() override;

        bool empty() override;
    };

    struct json_error : public std::logic_error {
        explicit json_error(const std::string &s) : std::logic_error(s) {}
    };

    struct json_tool {

        inline static std::string xtos(const void *);

        inline static std::string btos(const bool &);

        inline static int stoi(const std::string &);

        inline static long stol(const std::string &);

        inline static double stod(const std::string &);

        inline static bool stob(const std::string &);

        static void parser_obj(const std::string &, std::map<std::string, json_node> &);

        static void parser_arr(const std::string &, std::vector<json_node> &);

        static const std::string to_json(std::map<std::string, json_node> &);

        static const std::string to_json(std::vector<json_node> &);
    };
}
#endif
