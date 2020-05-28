/**
 * @file person.h
 * @author Siddhartha Tiwari (201851127@iiitvadodara.ac.in)
 * @brief contains the definition of the person class's ember functions.
 * @version 0.1
 * @date 2020-05-28
 */

#include "person.h"

void person::init()
{
	name = "";
	image = "";
	user_name = "";
	about = "";
	loc_univ = "";
	tot_string = "";
	uname = "<span class=\"link-gray pl-1\">";
}
void person::allot_image()
{
	size_t ind = tot_string.find("src", 0);
	ind += 5;
	for (int i = ind; tot_string.at(i) != '\"'; i++)
		image += tot_string.at(i);
}
void person::allot_name()
{
	size_t ind = tot_string.find(_name_, 0);
	ind += _name_.size();
	for (int i = ind; tot_string.at(i) != '<'; i++)
		name += tot_string.at(i);
	if (name == "")
		uname = "<span class=\"link-gray\">";
	name = remove_trailing_spaces(name);
}
void person::allot_user_name()
{
	size_t ind = tot_string.find(uname, 0);
	ind += uname.size();
	for (int i = ind; tot_string.at(i) != '<'; i++)
		user_name += tot_string.at(i);
	user_name = remove_trailing_spaces(user_name);
}
void person::allot_loc_univ() {}
string person::remove_trailing_spaces(string strn)
{
	for (int i = 0; i < strn.size(); i++)
	{
		if (strn[i] == 32)
			strn.erase(i);
		else
			break;
		i--;
	}
	for (int i = strn.size() - 1; i >= 0; i--)
	{
		if (strn[i] == 32)
			strn.erase(i);
		else
			break;
		i++;
	}
	return strn;
}

person::person(FILE *ptr, long int pos)
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

person::person(string name, string user_name)
{
	this->name = name;
	this->user_name = user_name;
}
void person::print_details()
{
	cout << "-----------------\n";
	cout << "Name: " << name << "\n";
	cout << "User Name: " << user_name << "\n";
	cout << "Image link: " << image << "\n";
	cout << "-----------------\n";
}

bool person::operator==(person &som)
{
	if (user_name == som.user_name)
		return true;
	return false;
}