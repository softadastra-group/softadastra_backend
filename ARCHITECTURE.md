# 🧱 Softadastra – Architecture Overview

This document outlines the modular architecture of the Softadastra backend system.

---

## 🧩 1. Core Design Principles

- **Modularity**: Each domain is encapsulated in a separate module (e.g., `chat`, `pay`, `commerce`).
- **Scalability**: Designed to support large numbers of users and concurrent requests.
- **Maintainability**: Clear separation of responsibilities and reusable utilities.
- **Performance**: Lightweight HTTP server (Crow), optimized build flags, optional cache layers.
- **Security**: Uses OpenSSL, input validation, JWT authentication (planned).

---

## 📁 2. Folder Structure

```
softadastra/
├── include/                # Public headers
│   ├── adastra/            # Core libraries
│   └── softadastra/        # Ecosystem modules
├── lib/                    # Source code of libraries
│   ├── adastra/            # Base (utils, crypto, core, network...)
│   └── softadastra/        # Chat, Pay, Commerce, etc.
├── src/                    # Entrypoint (main.cpp)
├── test/                   # Integration tests (GoogleTest)
├── unittests/              # Unit tests (GoogleTest / Catch2)
├── config/                 # Environment, API secrets, flags
├── architecture/           # Diagrams and technical docs
├── build/                  # Compiled output
└── Crow/include/           # Local version of Crow (header-only)
```

---

## 🔗 3. Key Modules and Responsibilities

### 🔹 `adastra`
| Module      | Responsibility                     |
|-------------|-------------------------------------|
| `utils`     | Helpers (string, filesystem, time) |
| `core`      | Algorithms, validation, formats    |
| `crypto`    | AES/RSA encryption, hashing        |
| `network`   | Retry strategy, sockets, wrappers  |
| `config`    | Load environment variables, keys   |

### 🔸 `softadastra`
| Module      | Responsibility                      |
|-------------|--------------------------------------|
| `chat`      | WebSocket logic, threads, messages  |
| `pay`       | Wallets, payments, subscriptions    |
| `box`       | Decentralized P2P file system       |
| `commerce`  | Products, categories, filters       |
| `pme`       | Tools for small businesses          |
| `map`       | Store locator, geodata              |
| `rh`        | User auth, permissions, shop admin  |

---

## 🌐 4. API Layer

Built using [Crow](https://crowcpp.org/), a C++ microframework:

- Each route file defines RESTful endpoints per module
- JSON I/O using `nlohmann/json`
- CORS handled via middleware
- Crow runs asynchronously (FastCGI planned)

---

## 🛡️ 5. Security & Config

- JWT Authentication for users and shops
- Configurable with `.env`-style files
- Secure API keys, P2P shared secrets

---

## 📈 6. Planned Improvements

- Add Redis cache support
- Separate admin & public APIs
- Support for clustering/load-balancing
- End-to-end encryption for chat and storage
