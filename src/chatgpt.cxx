/*
 * This program demonstrates how to programatically interact with OpenAI GPT using C++.
 * The program uses the curl library for making HTTP requests, and the nlohmann json
 * library for handling JSON data.
 */
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "chatgpt.h"
#include "chatgpt_key.cxx"

using nlohmann::json;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;


// Handle data received from the server
size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *response)
{
    size_t totalSize = size * nmemb;
    response->append((char *)contents, totalSize);
    return totalSize;
}

// Construct a POST request to the chat model endpoint and process the response.
string getCompletion(const string &prompt, const string &model = "gpt-3.5-turbo")
{
    string apiKey = info::code; // add your API key, the app will not work without it
    string baseUrl = "https://api.openai.com/v1/chat/completions";
    string response;
    CURL *curl = curl_easy_init();

    if (curl)
    {
        json requestData;
        requestData["model"] = model;
        requestData["messages"][0]["role"] = "user";
        requestData["messages"][0]["content"] = prompt;
        requestData["temperature"] = 0;

        string requestDataStr = requestData.dump().c_str();

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        curl_easy_setopt(curl, CURLOPT_URL, baseUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestDataStr.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestDataStr.length());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            cerr << "Curl request failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    std::cout << response << endl;

    // return response;
    json jresponse = json::parse(response);
    return jresponse["choices"][0]["message"]["content"].get<string>();
}

void accept_input(const string &val)
{
    string response = getCompletion(val);
    cout << response << endl;
}
