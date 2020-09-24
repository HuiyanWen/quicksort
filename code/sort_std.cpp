#include "stdafx.h"
#include "init.h"
#include "utils.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int qsort_cmp(const void * p, const void * q)
{
	return (*(int *)p - *(int *)q);
}

void sort_std(char *init_path) {
	const char *data_path;
	long num;
	int num_chose;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "2");
	if (flag) {
		num = stoi(fname["num"]);
		num_chose = stoi(fname["num_chose"]);
		data_path = fname["data_path"].c_str();
	}
	else {
		cout << "Loading ini 2 error!" << endl;
		return;
	}
	int *A = (int *)malloc(num_chose * sizeof(int));
	//Load_file(data_path, A);
	Load_tf(data_path, A, num, num_chose);
	clock_t begin, end;
	begin = clock();
	qsort(A, num_chose, sizeof(int), qsort_cmp);
	end = clock();
	
	/*for (int i = 0; i < num_chose; i++) {
		cout << A[i] << " " << endl;
	}*/
	cout << "Sort time:" << end - begin << endl;
	cout << "ÊÇ·ñÓÐÐò:" << isSorted(A, num_chose) << endl;
}