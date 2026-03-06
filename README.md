# Vulnerable C++/Crow Application

**⚠️ WARNING: Intentionally vulnerable - NEVER deploy to production!**

## 🎯 Purpose

- **200+ dependency vulnerabilities**
- **18 code-level vulnerabilities** (OWASP Top 10 + C++ specific)

## 📊 Vulnerabilities

### Dependencies (SCA)
- **40+ vulnerable C++ libraries** from 2017-2019
- Boost 1.66, OpenSSL 1.1.0, CURL 7.58, zlib 1.2.11
- Expected **200+ total vulnerabilities**

### Code (SAST) - 18 Vulnerabilities

1. Buffer Overflow - main.cpp:33
2. SQL Injection - main.cpp:41
3. Command Injection - main.cpp:61
4. Path Traversal - main.cpp:84
5. Use After Free - main.cpp:108
6. Memory Leak - main.cpp:116
7. NULL Pointer Dereference - main.cpp:123
8. Integer Overflow - main.cpp:129
9. Format String - main.cpp:135
10. Weak Cryptography - MD5 - main.cpp:141
11. Insecure Randomness - main.cpp:154
12. SSRF - main.cpp:161
13. Race Condition - main.cpp:187
14. Information Exposure - main.cpp:195
15. Hardcoded Credentials - main.cpp:19-23, 214
16. Missing Authentication - main.cpp:220
17. IDOR - main.cpp:233
18. Unvalidated Redirects - main.cpp:248

## 🚀 Setup

```bash
git clone https://github.com/YOUR_USERNAME/vulnerable-cpp-app.git
cd vulnerable-cpp-app

# Install dependencies (Ubuntu/Debian)
sudo apt-get install -y cmake g++ libboost-all-dev libssl-dev \
    libcurl4-openssl-dev libsqlite3-dev zlib1g-dev libxml2-dev

cmake .
make
./vulnerable_cpp_app
```

Access: `http://localhost:8080`

## 🔍 Testing

```bash
snyk test
# Expected: 200+ vulnerabilities
```

## 📚 Endpoints

- POST /api/login - SQL Injection
- GET /api/exec?cmd=ls - Command Injection
- GET /api/files?filename=test.txt - Path Traversal
- GET /api/proxy?url=http://example.com - SSRF
- DELETE /api/admin/users/:id - Missing Auth
- GET /api/debug - Sensitive Data Exposure
- GET /api/redirect?url=http://example.com - Open Redirect

## ⚠️ Security Notice

Educational use only. DO NOT deploy to production.

MIT License - Testing purposes only.
