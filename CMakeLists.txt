cmake_minimum_required(VERSION 3.10)
project(VulnerableCppApp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 40+ vulnerable C++ dependencies from 2017-2019
# Expected 200+ total vulnerabilities including transitive dependencies

# Boost (old vulnerable version from 2017)
find_package(Boost 1.66 REQUIRED COMPONENTS
    system
    filesystem
    thread
    date_time
    regex
    program_options
    iostreams
    serialization
    log
    random
)

# OpenSSL (old vulnerable version from 2018)
find_package(OpenSSL 1.1.0 REQUIRED)

# CURL (vulnerable version)
find_package(CURL 7.58.0 REQUIRED)

# SQLite3 (old version)
find_package(SQLite3 REQUIRED)

# Threads
find_package(Threads REQUIRED)

# zlib (old vulnerable version)
find_package(ZLIB 1.2.11 REQUIRED)

# libxml2 (old vulnerable version)
find_package(LibXml2 2.9.4 REQUIRED)

# Include directories
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
    ${LIBXML2_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Additional vulnerable libraries (would be installed via vcpkg or manually)
# - Crow web framework (old version)
# - jsoncpp 1.8.4 (2018 - has vulnerabilities)
# - yaml-cpp 0.6.2 (2018 - has vulnerabilities)
# - libpng 1.6.34 (2017 - has vulnerabilities)
# - libjpeg-turbo 1.5.3 (2017 - has vulnerabilities)
# - protobuf 3.6.1 (2018 - has vulnerabilities)
# - grpc 1.14.0 (2018 - has vulnerabilities)
# - poco 1.9.0 (2018 - has vulnerabilities)
# - cpprestsdk 2.10.10 (2018 - has vulnerabilities)
# - websocketpp 0.8.1 (2018 - has vulnerabilities)

# Source files
set(SOURCES
    main.cpp
)

# Create executable
add_executable(vulnerable_cpp_app ${SOURCES})

# Link libraries
target_link_libraries(vulnerable_cpp_app
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${CURL_LIBRARIES}
    ${SQLite3_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${ZLIB_LIBRARIES}
    ${LIBXML2_LIBRARIES}
)

# Compiler warnings (intentionally minimal for vulnerable app)
if(MSVC)
    target_compile_options(vulnerable_cpp_app PRIVATE /W0)
else()
    target_compile_options(vulnerable_cpp_app PRIVATE -w)
endif()

# Install targets
install(TARGETS vulnerable_cpp_app DESTINATION bin)
