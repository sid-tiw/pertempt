#include <iostream>
#include <fstream>
#include <errno.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string>
#include <vector>
#ifdef WIN32
#include <unistd.h>
#endif

using namespace std;

string treasure = "d-table table-fixed col-12 width-full py-4 border-bottom border-gray-light";
string nm = "<span class=\"f4 link-gray-dark\">";

class person
{
private:
	string name, user_name, about, loc_univ, tot_string, image;
	string uname;
	void init()
	{
		name = "";
		image = "";
		user_name = "";
		about = "";
		loc_univ = "";
		tot_string = "";
		uname = "<span class=\"link-gray pl-1\">";
	}
	void allot_image()
	{
		size_t ind = tot_string.find("src", 0);
		ind += 5;
		for (int i = ind; tot_string.at(i) != '\"'; i++)
			image += tot_string.at(i);
	}
	void allot_name()
	{
		size_t ind = tot_string.find(nm, 0);
		ind += nm.size();
		for (int i = ind; tot_string.at(i) != '<'; i++)
			name += tot_string.at(i);
		if(name == "")
			uname = "<span class=\"link-gray\">";
	}
	void allot_user_name()
	{
		size_t ind = tot_string.find(uname, 0);
		ind += uname.size();
		for (int i = ind; tot_string.at(i) != '<'; i++)
			user_name += tot_string.at(i);
	}
	void allot_loc_univ() {}

public:
	person(FILE *ptr, long int pos)
	{
		init();
		fseek(ptr, pos, SEEK_SET);
		char ch;
		while (fscanf(ptr, "%c", &ch) != -1)
			if (ch == '<')
			{
				fseek(ptr, -1, SEEK_CUR);
				break;
			}
		int count = 0;
		for (int i = 0;; i++)
		{
			string temp = "";
			for (int j = 0; j < 4; j++)
			{
				fscanf(ptr, "%c", &ch);
				temp += ch;
			}
			if (temp == "<div")
				count++;
			else if (temp == "</di" && count == 0)
				break;
			else if (temp == "</di")
				count--;
			fseek(ptr, -3, SEEK_CUR);
			tot_string += temp.at(0);
		}
		allot_image();
		allot_name();
		allot_user_name();
		allot_loc_univ();
	}
	void print_details()
	{
		cout << "-----------------\n";
		cout << "Name: " << name << "\n";
		cout << "User Name: " << user_name << "\n";
		cout << "Image link: " << image << "\n";
		cout << "-----------------\n";
	}
};

vector<person> search(FILE *ptr, string srch)
{
	vector<int> positions;
	long int pos = 0;
	char ch;
	while (fscanf(ptr, "%c", &ch) != -1)
		pos++;
	cout << srch.size() << "\n";
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
	for(int i=0;i<positions.size();i++)
		p_list.push_back(person(ptr, positions.at(i)));
	return p_list;
}

int main()
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *pnt = curl_easy_init();
	FILE *fptr = fopen("i-msid.txt", "w");
	char mess[10000];
	curl_easy_setopt(pnt, CURLOPT_WRITEDATA, fptr);
	// curl_easy_setopt(pnt, CURLOPT_HEADER, 1);
	curl_easy_setopt(pnt, CURLOPT_ERRORBUFFER, mess);
	curl_easy_setopt(pnt, CURLOPT_URL, "https://github.com/i-msid?tab=followers");
	curl_easy_perform(pnt);
	cout << mess << "\n";
	FILE *fop = fopen("i-msid.txt", "r");
	vector<person> temp;
	temp = search(fop, treasure);
	for(int i=0;i<temp.size();i++)
		temp[i].print_details();
	// cout << search(fop, treasure).at(0) << "\n";
	return 0;
}