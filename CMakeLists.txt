cmake_minimum_required(VERSION 3.7...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_CXX_STANDARD 17)

project(ezip      VERSION 1.0
                  DESCRIPTION "AES encyption"
                  LANGUAGES CXX)

include_directories(include)

set(SOURCES src/driver.cpp src/util.cpp src/decrypt_util.cpp src/encrypt_util.cpp)

find_package(Boost 1.73 REQUIRED COMPONENTS filesystem)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(ezip ${SOURCES})
target_link_libraries(ezip PUBLIC Boost::filesystem)
target_link_libraries (ezip PUBLIC Eigen3::Eigen)

