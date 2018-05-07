#pragma once
#include <string>
#include <map>
#include <iostream>  //��׼�������ѳ������׼I/O������һ��
#include <fstream>   //������ļ��������������������ļ���������ļ�
#include <sstream>   //�ṩ�����string����֮���I/O

using std::string;
using std::map;
using std::ostream;
using std::istream;
using std::endl;
using std::ofstream;
using std::cout;
using std::ifstream;

class Config;
//���������������ݵ������
ostream& operator<<(ostream& os, const Config& config);

//����������ȡ���ݱ�����������
istream& operator>>(istream& is, Config& config);


//ȥ���ո�ɶ��
void blankOff(string &s);


class Config {
public:
	friend ostream& operator<<(ostream& os, const Config &config);
	friend istream& operator>>(istream& os,  Config &config);
	friend void blankOff(string &s);
//����
public:
	Config();
	Config(string filename, string delimiter="=", string comment="#");

	//��ض�ȡ����
	template<typename T> 
	T read(const string &key);  //����valueֵ

	template<typename T> 
	bool readInto(const string &key,T &var) ; //����key�޸����������value 

	void readFile(string filename, string delimiter = "=", string comment = "#") ; //��ȡ�ļ�
	bool fileExist(string filename) ;  //�ж�key�Ƿ����
	void fileNotFind(string filename);
	void keyNotFind(string key);

	//����޸ĺ���
	template<typename T> 
	void add(const string &key,const T& value);  //����һ���ֵ
	void remove(const string &key);   //����keyɾ��һ���ֵ

	//���ת������
	template<typename T>
	string T_to_string(const T&t);  //����TתΪstring
	template<typename T>
	T string_to_T( string &s);

private:
	string m_delimeter;   //delimiter�ָ���
	string m_comment;    //comment ע�ͷ�
	map<string, string> m_content;  //��ֵ����
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

//��ȡkey��Ӧ��ֵ��������var��
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
	return ost.str();   //���ֵ�ַ�����?
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