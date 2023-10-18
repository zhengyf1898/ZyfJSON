#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;
//数据基类class
class Json {
public:
	virtual void gettype() {};
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
	virtual Json& operator[](string str) { return *new Json(); }
	virtual void setkey(std::string key){}
};

class JsonStr :public Json {
public:
	virtual void setdata(char value) { data.push_back(value); }
	virtual void setdata(std::string value) { data += value; }
	string getstr() { return data; }
	std::string data;
	virtual void gettype() {
		std::cout << "type is str;" << std::endl;
	}
};

class JsonNum :public Json {
public:
	virtual void setdata(double value) { data = value; }
	virtual double getnum() { return data; }
	//double get() { return data; }
	double data;
	virtual void gettype() {
		std::cout << "type is num;" << std::endl;
	}
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
	virtual void gettype() {
		std::cout << "type is arr;" << std::endl;
	}
};

class JsonObject :public Json {
public:
	virtual void setdata(Json* value) {
		if (key.length() != 0) {
			data.insert({ key, value });
		}
	}

	virtual void setdata(double value) {
		if (key.length() != 0) {
			Json* dataNum = new JsonNum;
			dataNum->setdata(value);
			data.insert({ key, dataNum });
		}
	}

	virtual void setdata(std::string value) {
		if (key.length() != 0) {
			Json* dataStr = new JsonStr;
			dataStr->setdata(value);
			data.insert({ key, dataStr });
		}
	}

	virtual void setkey(string _key) {
		key = _key;
	}
	std::unordered_map<std::string, Json*> data;
	std::string key;

	virtual Json& operator[](string str)
	{
		return *(Json*)data[str];
	}

	virtual void gettype() {
		std::cout << "type is obj;" << std::endl;
	}
};