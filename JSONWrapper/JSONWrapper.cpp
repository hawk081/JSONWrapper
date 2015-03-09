// JSONWrapper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "json/json.h"
#include "json/config.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define DECLARE_NECESSARY_METHOD(clazz)\
    clazz(){}\
    clazz(Json::Value root) : JBase(root) {}\
    clazz(const clazz& base) {this->cur_root = base.cur_root;}\
    clazz(const JBase& base) {this->cur_root = base.cur_root;}\

#define DECLARE_OBJECT_ATTR(type, attr) type get##attr() {return type(cur_root[#attr]);}
#define DECLARE_STRING_ATTR(attr)       std::string get##attr() {return getString(#attr);}
#define DECLARE_INT_ATTR(attr)          int get##attr() {return getInt(#attr);}
#define DECLARE_UINT_ATTR(attr)         unsigned int get##attr() {return getUInt(#attr);}
#define DECLARE_INT64_ATTR(attr)        __int64 get##attr() {return getInt64(#attr);}
#define DECLARE_UINT64_ATTR(attr)       unsigned __int64 get##attr() {return getUInt64(#attr);}
#define DECLARE_LARGEINT_ATTR(attr)     __int64 get##attr() {return getLargestInt(#attr);}
#define DECLARE_LARGEUINT_ATTR(attr)    unsigned __int64 get##attr() {return getLargestUInt(#attr);}
#define DECLARE_FLOAT_ATTR(attr)        float get##attr() {return getFloat(#attr);}
#define DECLARE_DOUBLE_ATTR(attr)       double get##attr() {return getDouble(#attr);}
#define DECLARE_BOOL_ATTR(attr)         bool get##attr() {return getBool(#attr);}
#define DECLARE_LIST_ATTR(type, attr)   std::vector<type> get##attr()\
{\
    std::vector<type> attr;\
    Json::Value value = cur_root[#attr];\
    for (Json::ValueIterator it = value.begin(); it != value.end(); it++)\
    {\
    attr.push_back(type(*it));\
    }\
return attr;\
}

class JBase
{
public:
    Json::Value cur_root;

public:
    JBase(){}
    JBase(Json::Value root) {this->cur_root = root;}
    JBase(const JBase& base) {this->cur_root = base.cur_root;}
    ~JBase(){};
    
    std::string getString(std::string key) 
    {
        return cur_root[key].asString();
    }

    int getInt(std::string key) 
    {
        return cur_root[key].asInt();
    }

    unsigned int getUInt(std::string key) 
    {
        return cur_root[key].asUInt();
    }

    __int64 getInt64(std::string key) 
    {
        return cur_root[key].asInt64();
    }

    unsigned __int64 getUInt64(std::string key) 
    {
        return cur_root[key].asUInt64();
    }

    __int64 getLargestInt(std::string key) 
    {
        return cur_root[key].asLargestInt();
    }

    unsigned __int64 getLargestUInt(std::string key) 
    {
        return cur_root[key].asLargestUInt();
    }

    float getFloat(std::string key) 
    {
        return cur_root[key].asFloat();
    }

    double getDouble(std::string key) 
    {
        return cur_root[key].asDouble();
    }

    bool getBool(std::string key) 
    {
        return cur_root[key].asBool();
    }

    JBase getObject(std::string key)
    {
        return JBase(cur_root[key]);
    }
};

class Data : public JBase
{
public:
    DECLARE_NECESSARY_METHOD(Data);

    DECLARE_INT_ATTR(success);
    DECLARE_STRING_ATTR(msg);
};

class Response : public JBase
{
public:
    DECLARE_NECESSARY_METHOD(Response);

    DECLARE_OBJECT_ATTR(Data, data);
    DECLARE_LIST_ATTR(Data, array);
};

int _tmain(int argc, _TCHAR* argv[])
{
    Json::Reader reader;
    Json::Value root;
    bool ok = reader.parse("{\"status\":1,\"data\":{\"success\":1, \"msg\":\"null\"},\"array\":[{\"success\":11,\"msg\":\"hello1\"},{\"success\":19,\"msg\":\"hello2\"},{\"success\":29,\"msg\":\"hello3\"}]}", root);
    Response p(root);

    Data data = p.getObject("data");
    int success = data.getsuccess();

    std::string msg = data.getmsg();

    std::vector<Data> _list = p.getarray();
    int _s = _list.at(0).getsuccess();
    std::string _msg = _list.at(0).getmsg();
    int _s1 = _list.at(1).getsuccess();
    std::string _msg1 = _list.at(1).getmsg();
	return 0;
}

