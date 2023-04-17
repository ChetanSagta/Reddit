#include"NetworkRequest.hpp"
#include "Models.hpp"
#include <memory>

NetworkRequest::NetworkRequest(){
  secret = std::make_shared<Secrets>();
  // token_info = std::make_shared<TokenInfo>();
}
