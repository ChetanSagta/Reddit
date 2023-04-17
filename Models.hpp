#pragma once

#include <fstream>
#include <map>
#include <spdlog/spdlog.h>
#include <string>

class Secrets {
  std::string client_id;
  std::string password;
  std::string secret;
  std::string user;
public:
  void read_secret_file() {
    const std::string file_path = "/home/chetan/Code/Reddit/secret.txt";
    std::ifstream file(file_path, std::ios::binary);

    if (!file) {
      spdlog::error("Error while reading file: {}", file_path);
      return;
    }

    std::map<std::string, std::string> secrets;
    std::string line;
    while (std::getline(file, line)) {
      int index = line.find("=");
      std::string key = line.substr(0, index);
      std::string value = line.substr(index + 1, line.length());
      secrets[key] = value;
    }

    client_id = secrets.at("client_id");
    password = secrets.at("password");
    secret = secrets.at("secret");
    user = secrets.at("user");
  }

  std::string get_client_id(){
    return client_id;
  }
  std::string get_password(){
    return password;
  }
  std::string get_secret(){
    return secret;
  }
  std::string get_user(){
    return user;
  }
};
