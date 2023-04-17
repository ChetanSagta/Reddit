#pragma once
#include <curl/curl.h>
#include <map>
#include <string>

class NetworkClient {
  CURL *curl=nullptr;
  long response_code;
  double elapsed=0;
  std::map<std::string, std::string> response_headers;
  static size_t header_callback(char*, size_t, size_t,void*);
  static size_t write_function(void*, size_t, size_t,std::string);
  std::string response_string;
  struct curl_slist *headers;

public:
  NetworkClient();
  ~NetworkClient();
  void getRequest(std::string);
  void postRequest(std::string, std::string);
  void postRequest(std::string , std::string, std::string, std::string);
  std::string getResponse();
  std::map<std::string, std::string> getHeaders();
};
