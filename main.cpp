#include "Models.hpp"
#include "NetworkClient.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <spdlog/spdlog.h>
#include <stdlib.h>
#include <string>
int main() {

  NetworkClient networkClient;
  Secrets secret;
  secret.read_secret_file();

  std::string CODE = "xyz";
  std::string URI = "http://localhost:8080";
  // std::string authorization_url =
  //     "https://www.reddit.com/api/v1/"
  //     "authorize?client_id="+secret.get_client_id()+"&response_type=CODE&"
  //     "state=xyz&redirect_uri="+URI+"&duration=PERMANENT&scope=read";

  // networkClient.getRequest(authorization_url);

  // std::string relocation = networkClient.getHeaders().at("location");

  // std::system(("brave-browser "+ relocation).c_str());

  
  std::string access_token_url = "https://www.reddit.com/api/v1/access_token";
  std::string access_part =
      "grant_type=client_credentials&code=" + CODE + "&redirect_uri=" + URI;

  networkClient.postRequest(access_token_url, access_part, secret.get_client_id(), secret.get_secret());
  std::cout << networkClient.getResponse() << std::endl;
  return 0;
}
