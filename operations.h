#ifndef __OPERATIONS__
#define __OPERATIONS_

#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "person.h"
#define MAX_SIZE 10000
#define _FIRST_ "followers"
#define _SECOND_ "following"

vector<person> parse(FILE*, string);
vector<person> fetch_list(string, string, CURL*);

#endif