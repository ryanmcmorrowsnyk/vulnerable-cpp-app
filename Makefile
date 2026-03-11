CXX = clang++
CXXFLAGS = -std=c++14 -Wall

# Homebrew paths
OPENSSL_PREFIX = /opt/homebrew/Cellar/openssl@3/3.5.2
SQLITE_PREFIX = /opt/homebrew/Cellar/sqlite/3.50.4
CURL_PREFIX = /opt/homebrew/var/homebrew/tmp/.cellar/curl/8.19.0

INCLUDES = -I$(OPENSSL_PREFIX)/include \
           -I$(SQLITE_PREFIX)/include \
           -I$(CURL_PREFIX)/include

LDFLAGS = -L$(OPENSSL_PREFIX)/lib \
          -L$(SQLITE_PREFIX)/lib \
          -L$(CURL_PREFIX)/lib \
          -lssl -lcrypto -lsqlite3 -lcurl \
          -Wl,-rpath,$(OPENSSL_PREFIX)/lib \
          -Wl,-rpath,$(SQLITE_PREFIX)/lib \
          -Wl,-rpath,$(CURL_PREFIX)/lib

TARGET = vulnerable_cpp_app
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
