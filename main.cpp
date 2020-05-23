#include <iostream>
#include <ctime>
#include <fstream>
#include <errno.h>
#include <curl/curl.h>
#include <stdlib.h>
#include "person.h"
#include "operations.h"
#ifdef WIN32
#include <unistd.h>
#endif

int main()
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *pnt = curl_easy_init();
	fetch_list("sid-tiw", _FIRST_, pnt);
	return 0;
}