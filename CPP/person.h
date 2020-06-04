/**
 * @file person.h
 * @author Siddhartha Tiwari (201851127@iiitvadodara.ac.in)
 * @brief contains the person class declaration.
 * @version 0.1
 * @date 2020-05-28
 */

#ifndef __PERSON__
#define __PERSON__

#include <string>
#include <iostream>
#ifndef _treasure_
/**
 * @brief the string used to parse out an user of the github page.
 * 
 */
#define _treasure_ string("d-table table-fixed col-12 width-full py-4 border-bottom border-gray-light")
#endif
#ifndef _name_
#define _name_ string("<span class=\"f4 link-gray-dark\">")
#endif

using namespace std;

/**
 * @brief The person class. Defines all attributes of a github user.
 * 
 */
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
	/**
	 * @brief Construct a new person object. Parse the user's detail from the file
	 *
	 * @param file_ptr :::: the file pointer from which to read.
	 * @param pos :::: the position from which to read
	 */
	person(FILE *, long int);
	person(string, string);
	person(string, string, string, string);
	void print_details();
	bool operator==(person &som);
	bool operator!=(person &som) { return user_name != som.user_name; }
	bool operator<(const person &som) const { return user_name.compare(som.user_name) < 0; }
	bool operator>(const person &som) const { return user_name.compare(som.user_name) > 0; }
	bool operator<=(const person &som) const { return user_name.compare(som.user_name) <= 0; }
	bool operator>=(const person &som) const { return user_name.compare(som.user_name) >= 0; }
	string get_name() { return name; }
	string get_uname() { return user_name; }
	string get_image() { return image; }
	string get_about() { return about; }
	string get_locu() { return loc_univ; }
};

#endif