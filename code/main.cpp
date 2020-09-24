#include "stdafx.h"
#include "utils.h"
#include <time.h>
#include "quicksort.h"
#include "init.h"
#include "generate_node.h"
#include "sort_std.h"

using namespace std;

int main()
{
	map<string, string>fname;
	CParseIniFile config;
	char* config_path = "config.ini";
	bool flag = config.ReadConfig(config_path, fname, "method");
	if (!flag) return -1;
	switch (stoi(fname["method"])) {
	case 0:
		generate_node(config_path);
		break;
	case 1:
		quicksort(config_path);
		break;
	case 2:
		sort_std(config_path);
		break;
	}
	cout << "Please click enter to exit." << endl;
	char ch;
	while (1) {
		if ((ch = getchar()) == '\n')
			break;
	}
    return 0;
}

