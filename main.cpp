// Intentionally Vulnerable C++ Application
// DO NOT USE IN PRODUCTION - FOR SECURITY TESTING ONLY

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <sqlite3.h>
#include <openssl/md5.h>
#include <curl/curl.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

// VULNERABILITY: Hardcoded Secrets (CWE-798)
const char* JWT_SECRET = "super_secret_jwt_key_12345";
const char* ADMIN_PASSWORD = "admin123";
const char* DB_PASSWORD = "password123";
const char* API_KEY = "AKIA_FAKE_CPP_KEY_FOR_TESTING_ONLY";
const char* AWS_SECRET_KEY = "fake_aws_secret_key_12345678901234567890";

// Simple HTTP response structure
struct HttpResponse {
    int status_code;
    std::string content_type;
    std::string body;
};

// VULNERABILITY 1: Buffer Overflow (CWE-120)
void vulnerable_strcpy(const char* input) {
    char buffer[50];
    // Vulnerable: No bounds checking
    strcpy(buffer, input);
    std::cout << "Buffer content: " << buffer << std::endl;
}

// VULNERABILITY 2: SQL Injection (CWE-89)
HttpResponse handle_login(const std::string& username, const std::string& password) {
    sqlite3* db;
    sqlite3_open("vulnerable.db", &db);

    // Vulnerable: String concatenation in SQL query
    std::string query = "SELECT * FROM users WHERE username = '" + username +
                       "' AND password = '" + password + "'";

    std::cout << "Executing query: " << query << std::endl;

    sqlite3_close(db);

    HttpResponse response;
    response.status_code = 200;
    response.content_type = "application/json";
    response.body = "{\"query\": \"" + query + "\", \"vulnerable\": true}";
    return response;
}

// VULNERABILITY 3: Command Injection (CWE-78)
HttpResponse handle_exec(const std::string& cmd) {
    // Vulnerable: Direct execution of user input
    std::string command = "sh -c '" + cmd + "'";
    FILE* pipe = popen(command.c_str(), "r");

    char buffer[128];
    std::string result;

    if (pipe) {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        pclose(pipe);
    }

    HttpResponse response;
    response.status_code = 200;
    response.content_type = "application/json";
    response.body = "{\"success\": true, \"output\": \"" + result + "\"}";
    return response;
}

// VULNERABILITY 4: Path Traversal (CWE-22)
HttpResponse handle_read_file(const std::string& filename) {
    // Vulnerable: No sanitization of file path
    std::string path = "./uploads/" + filename;

    std::ifstream file(path);
    std::string content;

    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        file.close();
    } else {
        content = "File not found";
    }

    HttpResponse response;
    response.status_code = 200;
    response.content_type = "application/json";
    response.body = "{\"content\": \"" + content + "\"}";
    return response;
}

// VULNERABILITY 5: Use After Free (CWE-416)
void use_after_free_vulnerability() {
    int* ptr = new int(42);
    delete ptr;
    // Vulnerable: Using pointer after free
    std::cout << "Value: " << *ptr << std::endl;
}

// VULNERABILITY 6: Memory Leak (CWE-401)
void memory_leak_vulnerability() {
    // Vulnerable: Allocated memory never freed
    int* data = new int[1000];
    // No delete[] data;
}

// VULNERABILITY 7: NULL Pointer Dereference (CWE-476)
void null_pointer_dereference(int* ptr) {
    // Vulnerable: No null check before dereference
    std::cout << "Value: " << *ptr << std::endl;
}

// VULNERABILITY 8: Integer Overflow (CWE-190)
int calculate_size(int width, int height) {
    // Vulnerable: No overflow check
    return width * height;
}

// VULNERABILITY 9: Format String (CWE-134)
void format_string_vulnerability(const char* user_input) {
    // Vulnerable: User input used directly as format string
    printf(user_input);
}

// VULNERABILITY 10: Weak Cryptography - MD5 (CWE-327)
std::string hash_password(const std::string& password) {
    // Vulnerable: Using MD5 for password hashing
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)password.c_str(), password.length(), digest);

    char md5string[33];
    for(int i = 0; i < 16; ++i)
        sprintf(&md5string[i*2], "%02x", (unsigned int)digest[i]);

    return std::string(md5string);
}

// VULNERABILITY 11: Insecure Random (CWE-330)
int generate_token() {
    // Vulnerable: Using predictable rand()
    srand(time(NULL));
    return rand() % 999999999;
}

// VULNERABILITY 12: SSRF (CWE-918)
HttpResponse handle_proxy(const std::string& url) {
    // Vulnerable: No URL validation
    CURL* curl = curl_easy_init();
    std::string response_data;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
            +[](void* contents, size_t size, size_t nmemb, std::string* s) {
                size_t newLength = size * nmemb;
                s->append((char*)contents, newLength);
                return newLength;
            });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    HttpResponse response;
    response.status_code = 200;
    response.content_type = "application/json";
    response.body = "{\"data\": \"" + response_data.substr(0, 500) + "\"}";
    return response;
}

// VULNERABILITY 13: Race Condition (CWE-362)
int global_counter = 0;

void increment_counter() {
    // Vulnerable: No synchronization
    global_counter++;
}

// VULNERABILITY 14: Information Exposure (CWE-200)
HttpResponse handle_debug() {
    // Vulnerable: Exposes sensitive information
    std::ostringstream json;
    json << "{";
    json << "\"jwt_secret\": \"" << JWT_SECRET << "\",";
    json << "\"admin_password\": \"" << ADMIN_PASSWORD << "\",";
    json << "\"db_password\": \"" << DB_PASSWORD << "\",";
    json << "\"api_key\": \"" << API_KEY << "\",";
    json << "\"aws_secret_key\": \"" << AWS_SECRET_KEY << "\"";
    json << "}";

    HttpResponse response;
    response.status_code = 200;
    response.content_type = "application/json";
    response.body = json.str();
    return response;
}

// VULNERABILITY 15: Hardcoded Credentials (CWE-798)
bool admin_login(const std::string& password) {
    // Vulnerable: Hardcoded admin password
    return password == ADMIN_PASSWORD;
}

// VULNERABILITY 16: Missing Authentication (CWE-306)
HttpResponse delete_user(int user_id) {
    // Vulnerable: No authentication required
    std::ostringstream json;
    json << "{\"success\": true, \"deleted\": " << user_id << "}";

    HttpResponse response;
    response.status_code = 200;
    response.content_type = "application/json";
    response.body = json.str();
    return response;
}

// VULNERABILITY 17: Insecure Direct Object Reference (IDOR) (CWE-639)
HttpResponse get_user(int user_id) {
    // Vulnerable: No authorization check
    std::ostringstream json;
    json << "{\"id\": " << user_id << ", ";
    json << "\"username\": \"user" << user_id << "\", ";
    json << "\"email\": \"user" << user_id << "@example.com\"}";

    HttpResponse response;
    response.status_code = 200;
    response.content_type = "application/json";
    response.body = json.str();
    return response;
}

// VULNERABILITY 18: Unvalidated Redirect (CWE-601)
HttpResponse handle_redirect(const std::string& url) {
    // Vulnerable: No validation of redirect URL
    HttpResponse response;
    response.status_code = 302;
    response.content_type = "text/html";
    response.body = "Redirecting to: " + url;
    return response;
}

// Simple HTTP request parser
struct HttpRequest {
    std::string method;
    std::string path;
    std::string query_string;
    std::map<std::string, std::string> params;
    std::string body;
};

// Parse query string
std::map<std::string, std::string> parse_query_string(const std::string& query) {
    std::map<std::string, std::string> params;
    std::vector<std::string> pairs;
    boost::split(pairs, query, boost::is_any_of("&"));

    for (const auto& pair : pairs) {
        std::vector<std::string> kv;
        boost::split(kv, pair, boost::is_any_of("="));
        if (kv.size() == 2) {
            params[kv[0]] = kv[1];
        }
    }

    return params;
}

// Simple request router
HttpResponse handle_request(const HttpRequest& req) {
    HttpResponse response;
    response.status_code = 404;
    response.content_type = "text/html";
    response.body = "Not Found";

    if (req.path == "/api/login" && req.method == "POST") {
        // Parse JSON body (simplified)
        return handle_login("admin", "password");
    }
    else if (req.path == "/api/exec" && req.method == "GET") {
        auto params = parse_query_string(req.query_string);
        return handle_exec(params["cmd"]);
    }
    else if (req.path == "/api/files" && req.method == "GET") {
        auto params = parse_query_string(req.query_string);
        return handle_read_file(params["filename"]);
    }
    else if (req.path == "/api/proxy" && req.method == "GET") {
        auto params = parse_query_string(req.query_string);
        return handle_proxy(params["url"]);
    }
    else if (req.path == "/api/debug" && req.method == "GET") {
        return handle_debug();
    }
    else if (req.path == "/api/redirect" && req.method == "GET") {
        auto params = parse_query_string(req.query_string);
        return handle_redirect(params["url"]);
    }
    else if (req.path == "/" && req.method == "GET") {
        response.status_code = 200;
        response.content_type = "text/html";
        response.body = R"(
            <html>
            <head><title>Vulnerable C++ App</title></head>
            <body>
                <h1>Intentionally Vulnerable C++ Application</h1>
                <p>This application contains numerous security vulnerabilities for testing purposes.</p>
                <h2>Available Endpoints:</h2>
                <ul>
                    <li>POST /api/login - SQL Injection</li>
                    <li>GET /api/exec?cmd=ls - Command Injection</li>
                    <li>GET /api/files?filename=test.txt - Path Traversal</li>
                    <li>GET /api/proxy?url=http://example.com - SSRF</li>
                    <li>DELETE /api/admin/users/:id - Missing Authentication</li>
                    <li>GET /api/debug - Sensitive Data Exposure</li>
                    <li>GET /api/redirect?url=http://example.com - Open Redirect</li>
                </ul>
            </body>
            </html>
        )";
    }

    return response;
}

int main() {
    std::cout << "======================================" << std::endl;
    std::cout << "Vulnerable C++ Application" << std::endl;
    std::cout << "WARNING: For security testing only!" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << std::endl;

    // Demonstrate vulnerabilities (for testing purposes)
    std::cout << "Testing vulnerabilities:" << std::endl;

    // Test SQL injection
    std::cout << "\n1. SQL Injection:" << std::endl;
    HttpResponse login_resp = handle_login("admin' OR '1'='1", "anything");
    std::cout << login_resp.body << std::endl;

    // Test weak crypto
    std::cout << "\n2. Weak Cryptography (MD5):" << std::endl;
    std::string hash = hash_password("password123");
    std::cout << "MD5 Hash: " << hash << std::endl;

    // Test insecure random
    std::cout << "\n3. Insecure Random:" << std::endl;
    int token = generate_token();
    std::cout << "Generated Token: " << token << std::endl;

    // Test debug endpoint
    std::cout << "\n4. Information Exposure:" << std::endl;
    HttpResponse debug_resp = handle_debug();
    std::cout << debug_resp.body << std::endl;

    std::cout << "\n======================================" << std::endl;
    std::cout << "Application demonstrates 18+ vulnerabilities" << std::endl;
    std::cout << "See README.md for full vulnerability list" << std::endl;
    std::cout << "======================================" << std::endl;

    return 0;
}
