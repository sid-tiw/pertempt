#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <errno.h>
#include <set>
#include <curl/curl.h>
#include <stdlib.h>
#include <stack>
#include "person.h"
#include "operations.h"
#ifdef WIN32
#include <unistd.h>
#endif
#define MAX_LEVEL 2
#define _DELETE_ 0.2
#define _REPLACE_ 0.1
#define _ADD_ 0.2
#define _FIRSTPR_ 30
#define _SECONDPR_ 30
#define calc_rank(first, second) first *_FIRSTPR_ + second *_SECONDPR_

double find_difference(string first, string second)
{ //variable lavenshtein distance
	int m = first.size(), n = second.size();
	double arr[m + 1][n + 1];
	for (int i = 0; i <= m; i++)
		arr[i][0] = i;
	for (int i = 0; i <= n; i++)
		arr[0][i] = i;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			double add = arr[i][j - 1] + _ADD_;
			double repl = arr[i - 1][j - 1];
			if (first.at(i - 1) != second.at(j - 1))
				repl += _REPLACE_;
			double del = arr[i - 1][j] + _DELETE_;
			arr[i][j] = min(min(add, repl), del);
		}
	}
	return arr[m][n];
}

double find_diff_index(pair<person, int> A, string search_string)
{
	double n_n = find_difference(A.first.get_name(), search_string);
	double un_n = find_difference(A.first.get_uname(), search_string);
	double ans = min(n_n, un_n);
	return ans;
}

vector<pair<person, int>> rank(vector<pair<person, int>> list, string to_search)
{
	sort(list.begin(), list.end());
	vector<pair<pair<pair<double, double>, double>, person>> arr;
	vector<pair<int, person>> temp1;
	vector<pair<double, person>> temp2;
	vector<pair<person, int>> arr1, arr2;
	for (int i = 0; i < list.size(); i++)
	{
		temp1.push_back(make_pair(list[i].second, list[i].first));
		temp2.push_back(make_pair(find_diff_index(list[i], to_search), list[i].first));
	}
	sort(temp1.begin(), temp1.end());
	sort(temp2.begin(), temp2.end());
	int ranks1[temp1.size()], ranks2[temp2.size()];
	ranks1[0] = 1;
	ranks2[0] = 1;
	for (int i = 1; i < temp1.size(); i++)
	{
		if (temp1[i].first == temp1[i - 1].first)
			ranks1[i] = ranks1[i - 1];
		else
			ranks1[i] = ranks1[i - 1] + 1;
		if (temp2[i].first == temp2[i - 1].first)
			ranks2[i] = ranks2[i - 1];
		else
			ranks2[i] = ranks2[i - 1] + 1;
		arr1.push_back(make_pair(temp1[i].second, (double)ranks1[i]));
		arr2.push_back(make_pair(temp2[i].second, (double)ranks2[i]));
	}
	sort(arr1.begin(), arr1.end());
	sort(arr2.begin(), arr2.end());
	for (int i = 0; i < temp1.size(); i++)
		arr.push_back(make_pair(make_pair(make_pair(calc_rank(arr1[i].second, arr2[i].second), list[i].second), temp2[i].first), arr1[i].first));
	vector<pair<person, int>> to_return;
	for (int i = 0; i < arr.size(); i++)
		to_return.push_back(make_pair(arr[i].second, list[i].second));
	return to_return;
}

set<person> get_list(string user_name, CURL *pnt)
{
	vector<person> pers1, pers2;
	pers1 = fetch_list(user_name, _FIRST_, pnt);
	pers2 = fetch_list(user_name, _SECOND_, pnt);
	set<person> pers;
	for (int i = 0; i < pers1.size(); i++)
		pers.insert(pers1[i]);
	for (int i = 0; i < pers2.size(); i++)
		pers.insert(pers2[i]);
	return pers;
}

int main(int n_o_arg, char *arguments[])
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *pnt = curl_easy_init();
	if (n_o_arg <= 2)
	{
		cout << "No user name supplied! Aborting!!";
		return 0;
	}
	string user_name = string(arguments[1]);
	string to_search = string(arguments[2]);
	vector<pair<person, int>> master;
	stack<pair<person, int>> driver, temp_driver;
	set<person> level[MAX_LEVEL];
	set<person> status;
	level[0] = get_list(user_name, pnt);
	for (auto &it : level[0])
	{
		driver.push(make_pair(it, 1));
		master.push_back(make_pair(it, 1));
	}
	cout << "Done level1\n";
	for (int i = 2; i <= MAX_LEVEL; i++)
	{
		while (!driver.empty()) //Yeah, BFS
		{
			if (status.find(driver.top().first) != status.end() || driver.top().first.get_uname() == user_name)
			{
				driver.pop();
				continue;
			}
			level[i - 1] = get_list(driver.top().first.get_uname(), pnt);
			for (auto &it : level[i - 1])
			{
				temp_driver.push(make_pair(it, i));
				master.push_back(make_pair(it, i));
			}
			status.insert(driver.top().first);
			driver.pop();
		}
		driver = temp_driver;
		cout << "Done level" << i << "\n";
	}
	for (int i = 0; i < master.size(); i++)
		master[i].first.print_details();
	system("rm *.txt");
	return 0;
}
