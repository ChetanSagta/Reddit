cmake_minimum_required(VERSION 3.22.1)
# set(CMAKE_C_COMPILER gcc)
# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Wextra -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Reddit)
# Search pkg-config utility first
find_package(PkgConfig REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)

# Then use pkg-config for locate specific package
pkg_check_modules(LIBFMT REQUIRED fmt)

include_directories(${CURL_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp NetworkClient.cpp NetworkClient.hpp Models.hpp NetworkRequest.cpp NetworkRequest.hpp)

# Link with the IMPORTED target created by 'pkg_check_modules'
# That target contains both include directories and actual libraries for link.
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBFMT_LINK_LIBRARIES})

