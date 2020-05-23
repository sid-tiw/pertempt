#include <iostream>
#include <ctime>
#include <fstream>
#include <errno.h>
#include <set>
#include <curl/curl.h>
#include <stdlib.h>
#include "person.h"
#include "operations.h"
#ifdef WIN32
#include <unistd.h>
#endif

int main(int n_o_arg, char *arguments[])
{
	if (n_o_arg <= 1)
	{
		cout << "No user name supplied! Aborting!!";
		return 0;
	}
	string user_name = string(arguments[1]);
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *pnt = curl_easy_init();
	vector<person> pers1, pers2;
	pers1 = fetch_list(user_name, _FIRST_, pnt);
	pers2 = fetch_list(user_name, _SECOND_, pnt);
	set<person> pers;
	for (int i = 0; i < pers1.size(); i++)
		pers.insert(pers1[i]);
	for (int i = 0; i < pers2.size(); i++)
		pers.insert(pers2[i]);
	FILE *result = fopen("stlist.imd", "w");
	for (auto it : pers)
	{
		fprintf(result, "%s\n", it.get_name().c_str());
		fprintf(result, "%s\n", it.get_uname().c_str());
		fprintf(result, "%s\n", it.get_image().c_str());
		fprintf(result, "%s\n", it.get_about().c_str());
		fprintf(result, "%s\n", it.get_locu().c_str());
	}
	system("rm *.txt");
	return 0;
}