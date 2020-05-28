#include "operations.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include "person.h"

vector<person> parse(FILE *ptr, string srch)
{
	vector<int> positions;
	long int pos = 0;
	char ch;
	while (fscanf(ptr, "%c", &ch) != -1)
		pos++;
	for (long int i = 0; i <= pos - srch.size(); i++)
	{
		fseek(ptr, i, SEEK_SET);
		string temp = "";
		for (long int j = 0; j < srch.size(); j++)
		{
			fscanf(ptr, "%c", &ch);
			temp += ch;
		}
		if (temp == srch)
			positions.push_back(i);
	}
	vector<person> p_list;
	for (int i = 0; i < positions.size(); i++)
		p_list.push_back(person(ptr, positions.at(i)));
	return p_list;
}

pair<vector<person>, CURLcode> fetch_list(string user_name, string tab, CURL *pnt)
{
	vector<person> temp_person;
	string url_link = "https://github.com/" + user_name + "?tab=" + tab;
	FILE *fptr = fopen((user_name + "_" + tab + ".txt").c_str(), "w");
	fstream log("error.log", ios::app);
	char err[MAX_SIZE];
	curl_easy_setopt(pnt, CURLOPT_WRITEDATA, fptr);
	curl_easy_setopt(pnt, CURLOPT_HEADER, 0);
	curl_easy_setopt(pnt, CURLOPT_ERRORBUFFER, err);
	curl_easy_setopt(pnt, CURLOPT_FAILONERROR, 1);
	curl_easy_setopt(pnt, CURLOPT_URL, url_link.c_str());
	CURLcode status = curl_easy_perform(pnt);
	if(status != 0)
	{
		time_t now = time(NULL);
		string current_time = ctime(&now);
		log << current_time << " ";
		log << "failed to fetch " << url_link <<  "\n";
		return make_pair(temp_person, status);
	}
	log << err;
	FILE *fop = fopen((user_name + "_" + tab + ".txt").c_str(), "r");
	temp_person = parse(fop, _treasure_);
	return make_pair(temp_person, status);
}