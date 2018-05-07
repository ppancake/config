#pragma once
#include <string>
#include <map>
#include <iostream>  //标准流，它把程序跟标准I/O连接在一起
#include <fstream>   //程序跟文件关联起来，输入来自文件，输出到文件
#include <sstream>   //提供程序和string对象之间的I/O

using std::string;
using std::map;
using std::ostream;
using std::istream;
using std::endl;
using std::ofstream;
using std::cout;
using std::ifstream;

class Config;
//保存配置类中内容到输出流
ostream& operator<<(ostream& os, const Config& config);

//从输入流读取数据保存至配置类
istream& operator>>(istream& is, Config& config);


//去除空格啥的
void blankOff(string &s);


class Config {
public:
	friend ostream& operator<<(ostream& os, const Config &config);
	friend istream& operator>>(istream& os,  Config &config);
	friend void blankOff(string &s);
//方法
public:
	Config();
	Config(string filename, string delimiter="=", string comment="#");

	//相关读取函数
	template<typename T> 
	T read(const string &key);  //返回value值

	template<typename T> 
	bool readInto(const string &key,T &var) ; //根据key修改输入变量的value 

	void readFile(string filename, string delimiter = "=", string comment = "#") ; //读取文件
	bool fileExist(string filename) ;  //判断key是否存在
	void fileNotFind(string filename);
	void keyNotFind(string key);

	//相关修改函数
	template<typename T> 
	void add(const string &key,const T& value);  //增加一组键值
	void remove(const string &key);   //根据key删除一组键值

	//相关转换函数
	template<typename T>
	string T_to_string(const T&t);  //类型T转为string
	template<typename T>
	T string_to_T( string &s);

private:
	string m_delimeter;   //delimiter分隔符
	string m_comment;    //comment 注释符
	map<string, string> m_content;  //键值内容
};


template<typename T>
T Config::string_to_T( string& s)
{
	T t;
	std::istringstream ist(s);
	ist >> t;
	return t;
}

template<typename T>
T Config::read(const string &key)
{
	auto it = this->m_content.find(key);
	if (it == this->m_content.end())
		keyNotFind(key);
	return string_to_T<T>(it->second);
}

//获取key对应的值，并存于var中
template<typename T>
bool Config::readInto(const string &key, T& var)
{
	auto  it = this->m_content.find(key);
	if (it == this->m_content.end())
	{
		return false;
	}
	var = string_to_T<T>(it->second);
	return true;
}
template<typename T>
string Config::T_to_string(const T&t)
{
	std::ostringstream ost;
	ost << t;
	return ost.str();   //输出值字符串流?
}

template<typename T>
void Config::add(const string& key, const T& value)
{
	string tmpkey = key;
	string v = T_to_string(value);
	blankOff(tmpkey);
	blankOff(v);
	this->m_content[tmpkey] = v;
}