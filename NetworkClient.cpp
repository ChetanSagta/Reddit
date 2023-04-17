#include "NetworkClient.hpp"

#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <map>
#include <spdlog/spdlog.h>
#include <stddef.h>
#include <string>
#include <utility>

NetworkClient::NetworkClient() {
  curl = curl_easy_init();
  if (!curl)
    spdlog::error("Error Initialising CURL");
}

size_t NetworkClient::write_function(void *ptr, size_t size, size_t nmemb,
                                     std::string data) {
  data.append((char *)ptr, size * nmemb);
  return size * nmemb;
}

size_t NetworkClient::header_callback(char *buffer, size_t size, size_t nitems,
                                      void *userdata) {
  std::string header_string = buffer;
  std::map<std::string, std::string> *header =
      (std::map<std::string, std::string> *)userdata;
  size_t index = header_string.find(":");
  if (index != std::string::npos) {
    std::string key = header_string.substr(0, index);
    std::string value = header_string.substr(index + 1, header_string.length());
    header->insert({key, value});
    // curl_slist_append(headers, "Accept: application/json");
  }
  return nitems * size;
}

void NetworkClient::getRequest(std::string url) {
  // if (curl) {
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &this->response_string);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &this->response_headers);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
  // // curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  curl_easy_setopt(curl, CURLOPT_USERAGENT,
                   "linux myredditapp:v0.0.1 (by /u/R3dd1tN00b101)");
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    spdlog::error("Error while creating getQuery: {}", res);
  }
  // }
}

void NetworkClient::postRequest(std::string url, std::string data) {
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_setopt(curl, CURLOPT_USERAGENT,
                     "linux myredditapp:v0.0.1 (by /u/R3dd1tN00b101)");
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      spdlog::error("Error while creating getQuery: {}", res);
    }
  }
}

void NetworkClient::postRequest(std::string url, std::string data,
                                std::string user, std::string password) {
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_setopt(curl, CURLOPT_USERPWD, (user + ":" + password).c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT,
                     "linux myredditapp:v0.0.1 (by /u/R3dd1tN00b101)");
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      spdlog::error("Error while creating getQuery: {}", res);
    }
  }
}

NetworkClient::~NetworkClient() { curl_easy_cleanup(curl); }

std::string NetworkClient::getResponse() { return response_string; }

std::map<std::string, std::string> NetworkClient::getHeaders() {
  return response_headers;
}
