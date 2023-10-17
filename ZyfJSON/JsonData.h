#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;
//数据基类class
class Json {
public:
	virtual void setdata() {};
	//virtual void get() {};
	virtual void setdata(double value) {}
	virtual void setdata(char value) {}
	virtual void setdata(std::string value) {}
	virtual string getstr() { return ""; }
	virtual double getnum() { return 0; }
	virtual void setdata(bool value) {}
	virtual void setdata(Json* value) {}
	virtual void getdata(bool& value) {}
	virtual Json& operator[](int i) { return *new Json(); }
};

class JsonStr :public Json {
public:
	virtual void setdata(char value) { data.push_back(value); }
	virtual void setdata(std::string value) { data += value; }
	string getstr() { return data; }
	std::string data;
};

class JsonNum :public Json {
public:
	virtual void setdata(double value) { data = value; }
	virtual double getnum() { return data; }
	//double get() { return data; }
	double data;
};

class JsonLiteral :public Json {
public:
	virtual void setdata(bool value) { data = value; }
	virtual void getdata(bool& value) { value = data; }
	bool data;
};

class JsonArray :public Json {
public:
	virtual void setdata(Json* value) { 
		data.push_back(value); 
	}
	virtual void setdata(double value) {
		Json* dataNum = new JsonNum;
		dataNum->setdata(value);
		data.push_back(dataNum);
	}
	virtual void setdata(std::string value) {
		Json* dataStr = new JsonStr;
		dataStr->setdata(value);
		data.push_back(dataStr);
	}
	//virtual void getdata(double& value) { value = data; }
	std::vector<Json*> data;

	virtual JsonArray& operator[](int i)
	{
		if (i >= data.size())
		{
			std::cout << "索引超过最大值" << std::endl;
			// 返回第一个元素
			return *(JsonArray*)data[0];
		}
		return *(JsonArray*)data[i];
	}
};

class JsonObject :public Json {
public:

};