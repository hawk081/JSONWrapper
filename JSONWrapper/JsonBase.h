#pragma once

#include "JsonBaseUtils.h"
#include "json/json.h"
#include "json/config.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class JsonBase
{
public:
    Json::Value cur_root;

public:
    JsonBase(){}
    JsonBase(Json::Value root) {this->cur_root = root;}
    JsonBase(const JsonBase& base) {this->cur_root = base.cur_root;}
    ~JsonBase(){};

    operator Json::Value()
    {
        return cur_root;
    }

    operator Json::Value() const
    {
        return cur_root;
    }

    Json::Value getJsonValue()
    {
        return cur_root;
    }

    std::string getJson()
    {
        Json::FastWriter writer;
        return writer.write( cur_root );
    }

    std::string getStyledJson()
    {
        Json::StyledWriter writer;
        return writer.write( cur_root );
    }

    std::wstring getJsonW()
    {
        Json::FastWriter writer;
        return writer.writeW( cur_root );
    }

    std::wstring getStyledJsonW()
    {
        Json::StyledWriter writer;
        return writer.writeW( cur_root );
    }

    wstring getwstring(std::string key)
    {
        return cur_root[key].asWString();
    }

    string getstring(std::string key) 
    {
        return cur_root[key].asString();
    }

    int getint(std::string key) 
    {
        return cur_root[key].asInt();
    }

    uint getuint(std::string key) 
    {
        return cur_root[key].asUInt();
    }

    float getfloat(std::string key) 
    {
        return cur_root[key].asFloat();
    }

    double getdouble(std::string key) 
    {
        return cur_root[key].asDouble();
    }

    bool getbool(std::string key) 
    {
        return cur_root[key].asBool();
    }

    JsonBase getObject(std::string key)
    {
        return JsonBase(cur_root[key]);
    }

protected:
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(JsonBase);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(std::string);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(int);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(uint);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(int64);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(uint64);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(float);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(double);
    DECLARE_BUILT_IN_TYPE_VECTOR2JSON(bool);
};
