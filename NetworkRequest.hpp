#pragma once

#include "Models.hpp"
#include "NetworkClient.hpp"
#include <memory>
class TokenInfo;
class NetworkRequest{
  NetworkClient networkClient;
  std::shared_ptr<Secrets> secret;
  std::shared_ptr<TokenInfo> token_info;
public:
  NetworkRequest();
  ~NetworkRequest();
};
