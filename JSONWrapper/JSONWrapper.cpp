// JSONWrapper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "./json_wrapper/JsonBase.h"

class Data : public JsonBase
{
public:
    DECLARE_NECESSARY_METHOD(Data);

    DECLARE_ATTR(int, success);
    DECLARE_ATTR(string, msg);
    DECLARE_ATTR(wstring, content);
};

class Response : public JsonBase
{
public:
    DECLARE_NECESSARY_METHOD(Response);

    DECLARE_OBJECT_ATTR(Data, data);
    DECLARE_OBJ_LIST_ATTR(Data, array);
};

class Model : public JsonBase
{
public:
    DECLARE_NECESSARY_METHOD(Model);

    DECLARE_ATTR(string, _string);
    DECLARE_ATTR(int, _int);
    DECLARE_ATTR(uint, _uint);
    DECLARE_ATTR(float, _float);
    DECLARE_ATTR(double, _double);
    DECLARE_ATTR(bool, _bool);
    DECLARE_LIST_ATTR(std::string, string_array);
    DECLARE_LIST_ATTR(double, doubld_list);
    DECLARE_LIST_ATTR(float, float_list);
    DECLARE_OBJECT_ATTR(Data, object);
    DECLARE_OBJ_LIST_ATTR(Data, data_list);
};

class YesterdayData : public JsonBase
{
public:
    DECLARE_NECESSARY_METHOD(YesterdayData);

    DECLARE_ATTR(wstring, fl);
    DECLARE_ATTR(wstring, fx);
    DECLARE_ATTR(wstring, high);
    DECLARE_ATTR(wstring, type);
    DECLARE_ATTR(wstring, low);
    DECLARE_ATTR(wstring, date);  
};

class ForecastData : public JsonBase
{
public:
    DECLARE_NECESSARY_METHOD(ForecastData);

    DECLARE_ATTR(wstring, fengxiang);
    DECLARE_ATTR(wstring, fengli);
    DECLARE_ATTR(wstring, high);
    DECLARE_ATTR(wstring, type);
    DECLARE_ATTR(wstring, low);
    DECLARE_ATTR(wstring, date);
};

class WeatherData : public JsonBase
{
public:
    DECLARE_NECESSARY_METHOD(WeatherData);

    DECLARE_ATTR(wstring, wendu);
    DECLARE_ATTR(wstring, ganmao);
    DECLARE_ATTR(wstring, aqi);
    DECLARE_ATTR(wstring, city);
    DECLARE_OBJ_LIST_ATTR(ForecastData, forecast);
    DECLARE_OBJECT_ATTR(YesterdayData, yesterday);
};

class WeatherResponse : public JsonBase
{
public:
    DECLARE_NECESSARY_METHOD(WeatherResponse);

    DECLARE_ATTR(wstring, desc);
    DECLARE_ATTR(int, status);
    DECLARE_OBJECT_ATTR(WeatherData, data);
};

int _tmain(int argc, _TCHAR* argv[])
{
    Json::Reader reader;
    Json::Value root;
    bool ok = reader.parse(L"{\"status\":1,\"data\":{\"content\":\"\x55\x6E\x69\x63\x6F\x64\x65\u5185\u5BB9\u6D4B\u8BD5\",\"success\":1, \"msg\":\"\u6211\u4EEC\"},\"array\":[{\"success\":11,\"msg\":\"hello1\"},{\"success\":19,\"msg\":\"hello2\"},{\"success\":29,\"msg\":\"hello3\"}]}", root);
    Response p(root);

    std::string js = p.getJson();

    Data data = p.getObject("data");
    int success = data.get_success();

    std::wstring content = data.get_content();
    std::string msg = data.get_msg();
    std::wstring wmsg = data.cur_root["msg"].asWString();

    std::vector<Data> _list = p.get_array();
    int _s = _list.at(0).get_success();
    std::string _msg = _list.at(0).get_msg();
    int _s1 = _list.at(1).get_success();
    std::string _msg1 = _list.at(1).get_msg();

    Json::Value serializeRoot;
    serializeRoot["string"] = "123";
    serializeRoot["int"] = 3;
    serializeRoot["float"] = 3.14159;
    serializeRoot["obj"] = serializeRoot;
    //serializeRoot["list"] = _list;

    Json::StyledWriter writer;
    std::string output = writer.write( serializeRoot );

    Model model;
    Data object;
    object.set_msg("data's message");
    object.set_success(false);

    model.set_object(object);
    model.set__string("string");
    model.set__int( -123 );
    model.set__uint( 34 );
    model.set__float( 3.1415f );
    model.set__double( 3.141592653 );
    model.set__bool( false );
    std::vector<std::string> string_a = model.get_string_array();
    string_a.push_back("123");
    string_a.push_back("1231111111111111");
    string_a.push_back("123xxxxxxxxxxxxxxxxxxxxxxxx");
    string_a.push_back("123--------fasfdfadfa");
    model.set_string_array(string_a);
    std::vector<Data> _dlist = model.get_data_list();
    data.set_msg("x");
    _dlist.push_back(data);
    _dlist.push_back(data);
    _dlist.push_back(data);
    _dlist.push_back(data);
    model.set_data_list(_dlist);

    std::vector<double> _double_list = model.get_doubld_list();
    _double_list.push_back(1.0);
    _double_list.push_back(2.0);
    _double_list.push_back(1131.0111111111);
    _double_list.push_back(1.011111);
    model.set_doubld_list(_double_list);

    std::string _output = model.getJson();
    Json::Value _root;
    reader.parse(_output, _root);
    Model _model(_root);

    cout << _model.get_object().get_msg() << endl;
    vector<double> __double_list = _model.get_doubld_list();
    for(vector<double>::iterator it = __double_list.begin();it != __double_list.end(); it++)
    {
        cout << *it << endl;
    }
    vector<std::string> __string_list = _model.get_string_array();
    for(vector<std::string>::iterator it = __string_list.begin();it != __string_list.end(); it++)
    {
        cout << *it << endl;
    }
    vector<Data> __data_list = _model.get_data_list();
    for(vector<Data>::iterator it = __data_list.begin();it != __data_list.end(); it++)
    {
        cout << it->get_msg() << " " << it->get_success() << endl;
    }

    std::wstring _content(L"{\"desc\":\"OK\",\"status\":1000,\"data\":{\"wendu\":\"19\",\"ganmao\":\"昼夜温差很大，易发生感冒，请注意适当增减衣服，加强自我防护避免感冒。\",\"forecast\":[{\"fengxiang\":\"南风\",\"fengli\":\"微风级\",\"high\":\"高温 19℃\",\"type\":\"多云\",\"low\":\"低温 5℃\",\"date\":\"13日星期五\"},{\"fengxiang\":\"南风\",\"fengli\":\"微风级\",\"high\":\"高温 19℃\",\"type\":\"阴\",\"low\":\"低温 8℃\",\"date\":\"14日星期六\"},{\"fengxiang\":\"南风\",\"fengli\":\"微风级\",\"high\":\"高温 19℃\",\"type\":\"多云\",\"low\":\"低温 8℃\",\"date\":\"15日星期天\"},{\"fengxiang\":\"南风\",\"fengli\":\"微风级\",\"high\":\"高温 20℃\",\"type\":\"阴\",\"low\":\"低温 13℃\",\"date\":\"16日星期一\"},{\"fengxiang\":\"南风\",\"fengli\":\"微风级\",\"high\":\"高温 21℃\",\"type\":\"阴\",\"low\":\"低温 9℃\",\"date\":\"17日星期二\"}],\"yesterday\":{\"fl\":\"微风\",\"fx\":\"南风\",\"high\":\"高温 20℃\",\"type\":\"晴\",\"low\":\"低温 4℃\",\"date\":\"12日星期四\"},\"aqi\":\"91\",\"city\":\"成都\"}}");
    if(reader.parse(_content, root))
    {
        WeatherResponse wres(root);

        std::wstring desc = wres.get_desc();
        int status = wres.get_status();
        WeatherData wdata = wres.get_data();

        std::vector<ForecastData> flist = wdata.get_forecast();

        ForecastData fd = flist.at(0);
        std::wstring fengli = fd.get_fengli();

        YesterdayData yd = wdata.get_yesterday();
        std::wstring wdate_ = yd.get_date();

        std::string styledJson = wres.getStyledJson();
        std::wstring styledJsonW = wres.getStyledJsonW();

        std::wstring jsonw = wres.getJsonW();
    }
	return 0;
}

