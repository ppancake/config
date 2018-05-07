#include "Config.h"

ostream& operator<<(ostream& os, const Config& config)
{
	for (auto it = config.m_content.begin(); it != config.m_content.end(); it++)
	{
		os << it->first << " " << config.m_delimeter << " " << it->second << endl;
	}
	return os;
}
istream& operator>>(istream& is, Config& config)
{
	string delimeter = config.m_delimeter;
	string comment = config.m_comment;
	int delimLen = delimeter.length();
	string nextline = "";
	while (is || nextline.length() > 0)
	{
		string line;
		if (nextline.length() > 0)
		{
			line = nextline;
			nextline = "";
		}
		else
		{
			getline(is, line); //���ж�ȡ
		}
		//ע�ͺ�����ݺ���
		line = line.substr(0, line.find(comment));

		//�����ָ������ַ���
		unsigned int delimPos = line.find(delimeter);//�ָ���λ��
		if (delimPos <string::npos)
		{
			string key = line.substr(0, delimPos);//�õ���ֵ
			line.replace(0, delimPos + delimLen, "");

			bool next = true;
			while (next && is)
			{
				getline(is, nextline);
				next = false;
				string tmpstr = nextline;
				blankOff(tmpstr);
				if (tmpstr == "")
					continue;
				nextline = nextline.substr(0, nextline.find(comment));
				if (nextline.find(delimeter) < string::npos)
					continue;

				tmpstr = nextline;
				blankOff(tmpstr);
				if (tmpstr != "")
					line += "\n";
				line += nextline;
				next = true;
			}
			blankOff(key);
			blankOff(line);
			config.m_content[key] = line;
		}
	}
	return is;
}

Config::Config()  //�����ļ��ĵĹ��캯��
{	
	m_delimeter = '=';
	m_comment = '#';
}

Config::Config(string filename, string delimeter, string comment) :m_delimeter(delimeter), m_comment(comment)
{
	ifstream in(filename);//����һ��ifstream���򿪸�ָ���ļ���������in�����ļ��ж�ȡ����
	if (!in)
		fileNotFind(filename);
	in >> (*this);
}


void Config::readFile(string filename, string delimiter , string comment)
{
	this->m_delimeter = delimiter;
	this->m_comment = comment;
	ifstream in(filename);
	if (!in)
		fileNotFind(filename);
	in >> (*this);
}

bool Config::fileExist(string filename)
{
	bool exist = false;
	ifstream in(filename);
	if (in)
		exist = true;
	return exist;
}

void Config::fileNotFind(string filename)
{
	cout << filename<<" not find" << endl;
}

void Config::keyNotFind(string key)
{
	cout << key<<"key not find" << endl;
}


void Config::remove(const string& key)
{
	this->m_content.erase(this->m_content.find(key));
}





void blankOff(string &s)
{
	const char blank[] = " \n\t\v\r\f";//ע��ո�
	s.erase(0, s.find_first_not_of(blank));//��������һ���ַ�����������ַ���λ�õ�ַ
	s.erase(s.find_last_not_of(blank) + 1U);
}

