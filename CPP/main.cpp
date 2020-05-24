#include <iostream>
#include <ctime>
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
	cout << "Done\n";
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
	}
	for (int i = 0; i < master.size(); i++)
		master[i].first.print_details();
	system("rm *.txt");
	return 0;
}