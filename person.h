#ifndef __PERSON__
#define __PERSON__

#include <string>
#include <iostream>
#ifndef _treasure_
#define _treasure_ string("d-table table-fixed col-12 width-full py-4 border-bottom border-gray-light")
#endif
#ifndef _name_
#define _name_ string("<span class=\"f4 link-gray-dark\">")
#endif

using namespace std;

class person
{
private:
	string name, user_name, about, loc_univ, tot_string, image;
	string uname;
	void init();
	void allot_image();
	void allot_name();
	void allot_user_name();
	void allot_loc_univ();
	string remove_trailing_spaces(string);

public:
	person(FILE *, long int);
	person(string, string);
	void print_details();
	bool operator==(person &som);
};

#endif