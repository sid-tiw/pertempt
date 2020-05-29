/**
 * @file main.cpp
 * @author Siddhartha Tiwari (201851127@iiitvadodara.ac.in)
 * @brief entry point of the pertempt application
 * @version 0.1
 * @date 2020-05-28
 */
#define CURL_STATICLIB
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
#define __DELETE string("rm")
#ifdef WIN32
#undef __DELETE
#define __DELETE string("del")
#include <io.h>
#define CURL_STATICLIB
#ifdef _DEBUG
#pragma comment(lib, "C:/CURL/libcurl_a_debug.lib")
#else
#pragma comment(lib, "C:/CURL/libcurl_a.lib")
#endif
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "advapi32.lib")
#endif
/**
 * @brief The maximum depth to search for in the network tree
 * 
 */
#define MAX_LEVEL 1
/**
 * @brief The cost of deletion for calculating the levenshtein's distance
 * 
 */
#define _DELETE_ 0.2
/**
 * @brief The cost of replacement for calculating the levenshtein's distance
 * 
 */
#define _REPLACE_ 0.2
/**
 * @brief The cost of addition for calculating the levenshtein's distance
 * 
 */
#define _ADD_ 0.2
/**
 * @brief The weight given to the first property(in reference to rankings).
 * 
 */
#define _FIRSTPR_ 30
/**
 * @brief The weight given to the second property(in reference to rankings).
 * 
 */
#define _SECONDPR_ 100
/**
 * @brief calculates the rank according to the weights given to both the arguments
 * 
 */
#define calc_rank(first, second) first *_FIRSTPR_ + second *_SECONDPR_

/**
 * @brief finds the levenshtein's distance between two strings
 * 
 * @param first :::: the first string
 * @param second :::: the second string
 * @return double :::: levenshtein's distance between the two strings.
 */
double find_difference(string first, string second)
{ //variable lavenshtein distance
	if (first.size() < 1 || second.size() < 1)
		return (double)LONG_MAX;
	const int m = first.size(), n = second.size();
	double **arr = new double *[m + 1];
	for (int i = 0; i <= m; i++)
		arr[i] = new double[n + 1];
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

/**
 * @brief Split the given target, when a space is encountered.
 * 
 * @param target :::: the target string, which to split
 * @return vector<string> :::: A list of strings split on spaces.
 */
vector<string> split_on_spaces(string target)
{
	vector<string> to_return;
	if (target.size() == 0)
		return to_return;
	int pre_ind = 0;
	for (int i = 0; i < target.size(); i++)
	{
		if (target[i] == ' ')
		{
			to_return.push_back(target.substr(pre_ind, i - pre_ind));
			pre_ind = i + 1;
		}
	}
	if (pre_ind < target.size())
		to_return.push_back(target.substr(pre_ind));
	return to_return;
}

/**
 * @brief finds the minimum of the levenshtein's distances from the target to the person's name and username.
 * 
 * @param indiv :::: pair containing the person object and its depth.
 * @param search_string :::: the target string
 * @return double :::: the minimum of the lavenshtein's distances
 */
double find_diff_index(pair<person, int> indiv, string search_string)
{
	vector<string> temp1 = split_on_spaces(indiv.first.get_name());
	vector<string> temp2 = split_on_spaces(indiv.first.get_uname());
	vector<string> temp3 = split_on_spaces(search_string);
	double n_n = find_difference(indiv.first.get_name(), search_string);
	double un_n = find_difference(indiv.first.get_uname(), search_string);
	double ans = min(un_n, n_n);
	for (int i = 0; i < temp1.size(); i++)
		for (int j = 0; j < temp3.size(); j++)
		{
			double temp = find_difference(temp1[i], temp3[j]);
			if (temp < ans)
				ans = temp;
		}
	for (int i = 0; i < temp2.size(); i++)
		for (int j = 0; j < temp3.size(); j++)
		{
			double temp = find_difference(temp2[i], temp3[j]);
			if (temp < ans)
				ans = temp;
		}
	return ans;
}

/**
 * @brief ranks persons according to their levenshtein distance
 * from the target and their depth in the relation tree.
 * 
 * @param list :::: list of the persons and their depth in a vector of pairs 
 * 
 * @param to_search :::: the target to search
 * 
 * @return vector<pair<person, int>> :::: The persons ranked according to the criteria given above and their depth.
 */
vector<pair<person, int>> rank_persons(vector<pair<person, int>> list, string to_search)
{
	sort(list.begin(), list.end());												//Sort the list personwise, i.e the person with lexicographically smallest user name would be first after sorting.
	vector<pair<pair<pair<pair<double, double>, double>, double>, person>> arr; //The main ranking array. The first
	vector<pair<int, person>> temp1;											//It will store the reverse of the corresponding pairs of the list array.
	vector<pair<double, person>> temp2;
	vector<pair<person, double>> arr1, arr2;
	for (int i = 0; i < list.size(); i++)
	{
		temp1.push_back(make_pair(list[i].second, list[i].first));
		temp2.push_back(make_pair(find_diff_index(list[i], to_search), list[i].first));
	}
	sort(temp1.begin(), temp1.end());
	sort(temp2.begin(), temp2.end());
	int *ranks1 = new int[temp1.size()];
	int *ranks2 = new int[temp2.size()];
	ranks1[0] = 1;
	ranks2[0] = 1;
	arr1.push_back(make_pair(temp1[0].second, (double)ranks1[0]));
	arr2.push_back(make_pair(temp2[0].second, (double)ranks2[0]));
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
	for (int i = 0; i < arr1.size(); i++)
	{
		double temp_rank_variable = (1.0 / (double)max(arr1[i].first.get_name().size(), arr1[i].first.get_uname().size()));
		arr.push_back(make_pair(make_pair(make_pair(make_pair(calc_rank(arr1[i].second, arr2[i].second), temp2[i].first), list[i].second), temp_rank_variable), arr1[i].first));
	}
	sort(arr.begin(), arr.end());
	vector<pair<person, double>> temp_arr;
	for (int i = 0; i < arr.size(); i++)
		temp_arr.push_back(make_pair(arr[i].second, (double)i));
	sort(temp_arr.begin(), temp_arr.end());
	vector<pair<person, int>> to_return;
	for (int i = 0; i < arr.size(); i++)
		to_return.push_back(make_pair(arr[i].second, list[i].second));
	return to_return;
}

/**
 * @brief Get the list of all followers and following of the user_name.
 * 
 * @param user_name :::: the user name of the person
 * @param pnt :::: the pointer returned by the global curl initializer.
 * @return pair<set<person>, int> :::: the pair containing the list of persons as the 
 * first value in the pair and the status code as the second.
 */
pair<set<person>, int> get_list(string user_name, CURL *pnt)
{
	pair<vector<person>, CURLcode> pers1, pers2;
	pers1 = fetch_list(user_name, _FIRST_, pnt);
	pers2 = fetch_list(user_name, _SECOND_, pnt);
	set<person> pers;
	for (int i = 0; i < pers1.first.size(); i++)
		pers.insert(pers1.first[i]);
	for (int i = 0; i < pers2.first.size(); i++)
		pers.insert(pers2.first[i]);
	return make_pair(pers, (!pers1.second) && (!pers2.second));
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
	set<person> status, person_status;
	pair<set<person>, int> check_error_first = get_list(user_name, pnt);
	if (check_error_first.second != 1)
	{
		fprintf(stderr, "some error occured. Exiting!!\n");
		return 0;
	}
	level[0] = check_error_first.first;
	for (auto &it : level[0])
	{
		person temp_person_object = it;
		if (temp_person_object.get_uname().size() >= 1)
		{
			driver.push(make_pair(it, 1));
			master.push_back(make_pair(it, 1));
		}
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
			level[i - 1] = get_list(driver.top().first.get_uname(), pnt).first;
			for (auto &it : level[i - 1])
			{
				if (person_status.find(it) == person_status.end())
				{
					person temp_person_object = it;
					if (temp_person_object.get_uname().size() >= 1)
					{
						master.push_back(make_pair(it, i));
						temp_driver.push(make_pair(it, i));
						person_status.insert(it);
					}
				}
			}
			status.insert(driver.top().first);
			driver.pop();
		}
		driver = temp_driver;
		cout << "Done level" << i << "\n";
	}
	cout << "Done\n\n";
	vector<pair<person, int>> result = rank_persons(master, to_search);
	/*
	Rank obtained. Do what is required here now.
	*/
	system((__DELETE + " *.txt").c_str());
	return 0;
}
