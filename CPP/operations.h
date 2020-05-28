/**
 * @file operations.h
 * @author Siddhartha Tiwari (201851127@iiitvadodara.ac.in)
 * @brief defining operations related to curl. Declaration file only.
 * @version 0.1
 * @date 2020-05-28
 */

#ifndef __OPERATIONS__
#define __OPERATIONS_

#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "person.h"
/**
 * @brief The max size of the error produced by CURL.
 */
#define MAX_SIZE 10000
#define _FIRST_ "followers"
#define _SECOND_ "following"

/**
 * @brief parse out the list of github's persons from a github page of followers/following
 * 
 * @param ptr :::: a pointer to the file in which the fetched page is written. 
 * @param srch :::: the string criteria defining the person in the page
 * @return vector<person> :::: list of persons in form of vectors
 */
vector<person> parse(FILE*, string);

/**
 * @brief fetch the list of followers/following of a user
 * 
 * @param user_name :::: the user name of the user
 * @param tab :::: either "followers" or "following"
 * @param pnt :::: pointer returned by the global curl initializer
 * @return pair<vector<person>, CURLcode> :::: a pair containing the list of persons and the status code
 */
pair<vector<person>, CURLcode> fetch_list(string, string, CURL*);

#endif