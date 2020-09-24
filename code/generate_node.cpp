#include "stdafx.h"
#include "generate_node.h"
#include <time.h>
#include "init.h"
#include "utils.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 

using namespace std;

long my_generate_node(long p, long r) {
	return myrandom(r - p) + p;
}

bool check_repeate(vector<int> &data, int temp) {
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == temp) return false;
	}
	return true;
}

void generate_node(char* init_path) {
	const char *data_path;
	long num, range_l, range_r;
	float ratio;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "0");
	if (flag) {
		num = stoi(fname["num"]);
		ratio = stof(fname["ratio"]);
		range_l = stoi(fname["range_l"]);
		range_r = stoi(fname["range_r"]);
		data_path = fname["data_path"].c_str();
	}
	else {
		cout << "Loading ini 0 error!" << endl;
		return;
	}
	srand((unsigned)time(0));
	vector <int> data;
	//generate data repeately.
	flag = false;
	int gnt_data = my_generate_node(range_l, range_r+1);
	cout << "Generating data..." << endl;
	for (int i = 0; i < num; i++) {
		Print_process(num, i, 100);
		if (i < num*ratio) {
			data.push_back(gnt_data);
		}
		else{
			flag = false;
			do {
				gnt_data = my_generate_node(range_l, range_r+1);
				if (check_repeate(data, gnt_data)) flag = true;
			} while (!flag);
			data.push_back(gnt_data);
		}		
	}
	cout << endl;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng(seed);
	srand((unsigned)time(0));
	shuffle(data.begin(), data.end(), rng);

	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, data_path, "ab+")) != 0)
		printf("Open dst file failed.\n");

	cout << "Writing tf..." << endl;
	fwrite(&num, sizeof(int), 1, fp);
	for (int i = 0; i < num; ++i)
	{
		fwrite(&data[i], sizeof(int), 1, fp);
		Print_process(num, i, 100);
	}
	cout << endl;
	fclose(fp);
	cout << "Finished." << endl;
}