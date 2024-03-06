#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using namespace std;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *response);
string getCompletion(const string &prompt, const string &model);
void accept_input(const string &val);
