#ifndef __JSON_BASE_UTILS_H_
#define __JSON_BASE_UTILS_H_

// typedef int int;
typedef unsigned int uint;
typedef __int64 int64;
typedef unsigned __int64 uint64;
//typedef float float
//typedef double double

#define DECLARE_NECESSARY_METHOD_BASE(clazz, baseclazz)\
    clazz(){}\
    clazz(Json::Value root) : baseclazz(root) {}\
    clazz(const clazz& base) {this->cur_root = base.cur_root;}\
    clazz(const JsonBase& base) {this->cur_root = base.cur_root;}\

#define DECLARE_NECESSARY_METHOD(clazz)\
    clazz(){}\
    clazz(Json::Value root) : JsonBase(root) {}\
    clazz(const clazz& base) {this->cur_root = base.cur_root;}\
    clazz(const JsonBase& base) {this->cur_root = base.cur_root;}\

#define DECLARE_GETTER(type, attr)\
    type get_##attr()\
    {\
    return get##type(#attr);\
    }

#define DECLARE_OBJ_GETTER(type, attr)\
    type get_##attr()\
    {\
        return type(cur_root[#attr]);\
    }\

#define DECLARE_SETTER(type, attr)\
    void set_##attr(type attr)\
    {\
    cur_root[#attr] = attr;\
    }

/* For built-in type */
#define DECLARE_ATTR(type, attr) DECLARE_GETTER(type, attr) DECLARE_SETTER(type, attr)
/* Only for Object that extends JsonBase */
#define DECLARE_OBJECT_ATTR(type, attr) DECLARE_OBJ_GETTER(type, attr) DECLARE_SETTER(type, attr)

#define DECLARE_LIST_GETTER(type, attr)\
    std::vector<type> get_##attr()\
    {\
        std::vector<type> attr;\
        Json::Value value = cur_root[#attr];\
        for (Json::ValueIterator it = value.begin(); it != value.end(); it++)\
        {\
            attr.push_back(type(*it));\
        }\
        return attr;\
    }

#define DECLARE_LIST_SETTER(type, attr)\
    void set_##attr(std::vector<type> attr)\
    {\
        cur_root[#attr] = vector2json(attr);\
    }

#define DECLARE_OBJ_LIST_SETTER(type, attr)\
    void set_##attr(std::vector<type> attr)\
    {\
        std::vector<JsonBase> attr##s;\
        attr##s.assign(attr.begin(), attr.end());\
        cur_root[#attr] = vector2json(attr##s);\
    }

/* For built-in type */
#define DECLARE_LIST_ATTR(type, attr) DECLARE_LIST_GETTER(type, attr) DECLARE_LIST_SETTER(type, attr)
/* Only for Object that extends JsonBase */
#define DECLARE_OBJ_LIST_ATTR(type, attr) DECLARE_LIST_GETTER(type, attr) DECLARE_OBJ_LIST_SETTER(type, attr)

#define DECLARE_BUILT_IN_TYPE_VECTOR2JSON(type)\
    Json::Value vector2json(std::vector<type> listData)\
    {\
        Json::Value value;\
        for(std::vector<type>::const_iterator it = listData.begin(); it != listData.end(); it++)\
        {\
            value.append(*it);\
        }\
        return value;\
    }

#endif /* __JSON_BASE_UTILS_H_ */