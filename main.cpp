#include "Config.h"

int main()
{
	string filename("config");
	ofstream out(filename); // 打开/创建文件
	out << "# new config \n";
	out << "name = zwk\n";
	out.close();

	Config config(filename);
	string key = "name";
	string value;
	value = config.read<string>(key);
	cout << "key=" << key << " value" << value << endl;

	string  key1 = "year";
	int value1 = 2018;
	config.add<int>(key1, value1);
	//写入文件
	out.open(filename);
	if (out.is_open())
	{
		out << config;
		cout << "写入数据" << endl;

	}
	out.close();
	return 0;
}