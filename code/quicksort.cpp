#include "stdafx.h"
#include "quicksort.h"
#include "utils.h"
#include "init.h"
#include <string>
#include <time.h>
#include "generate_node.h"
#include <map>
#include <algorithm>
#include <random>
#include <chrono> 
#include <vector>
#include <math.h>
#include <random>


using namespace std;

void swap_int(int *a, int *b) {
	if (*a != *b) {
		int temp;
		temp = *a;
		*a = *b;
		*b = temp;
	}	
}

int rand_partition(int *A, int p, int r) {
	srand((unsigned)time(0));
	int i = my_generate_node(p, r+1);
	swap_int(&A[r], &A[i]);
	int x = A[r];
	i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			swap_int(&A[i], &A[j]);
		}
	}
	swap_int(&A[i + 1], &A[r]);
	return i + 1;		
}

void rand_partition_improve(int *A, int p, int r, int *m, int *n) {	
	srand((unsigned)time(0));
	int v = my_generate_node(p, r + 1);
	int less = p - 1;
	int more = r;
	int idx = p;
	for (; idx<more;) {
		if (A[idx]<A[r]) {
			swap_int(&A[++less], &A[idx++]);
		}
		else  if (A[idx]>A[r]) {
			swap_int(&A[--more], &A[idx]);
		}
		else {
			idx++;
		}
	}
	swap_int(&A[idx], &A[r]);
	*m = less;
	*n = more;
}



void mysort(int *A, int p, int r, int whether_improve) {
	int q, m, n;
	if (!whether_improve) {
		if (p < r) {
			q = rand_partition(A, p, r);
			mysort(A, p, q - 1, whether_improve);
			mysort(A, q + 1, r, whether_improve);
		}
	}
	else {
		if (p < r) {
			rand_partition_improve(A, p, r, &m, &n);
			mysort(A, p, m, whether_improve);
			mysort(A, n, r, whether_improve);
		}
	}
}

bool check_repeate2(vector<int> &data, int temp) {
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == temp) return false;
	}
	return true;
}

void quicksort(char* init_path) {
	const char *data_path;
	int p, r, num, num_chose, whether_improve;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "1");
	if (flag) {
		num = stoi(fname["num"]);
		num_chose = stoi(fname["num_chose"]);
		whether_improve = stoi(fname["whether_improve"]);
		p = stoi(fname["p"]);
		r = stoi(fname["r"]);
		data_path = fname["data_path"].c_str();
	}
	else {
		cout << "Loading ini 1 error!" << endl;
		return;
	}
	//load dots
	int *A = (int *)malloc(num_chose * sizeof(int));
	
	Load_tf(data_path, A, num, num_chose);

	clock_t begin, end;
	begin = clock();
	mysort(A, p, r-1, whether_improve);
	end = clock();

	cout << "Sort time:" << end - begin << endl;
	cout << "ÊÇ·ñÓÐÐò:" << isSorted(A, num_chose) << endl;
}