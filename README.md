# 🚀 Softadastra

**Modular C++ backend** designed to build high-performance, secure, and scalable systems.  
It powers the **Softadastra** ecosystem: decentralized platform, e-commerce, chat, payments, P2P storage, and more.

---

## 📂 Project Structure

```
softadastra/
├── include/ # Public header files (adastra/ and softadastra/)
├── lib/ # Source code of modular libraries
├── src/ # Application entry point (main.cpp)
├── test/ # Integration tests (GoogleTest)
├── unittests/ # Modular unit tests
├── config/, architecture/ → Configuration and technical documentation
```

---

---

## 🔧 Compiled Libraries & Targets

| Target Name             | Type       | Description                              |
| ----------------------- | ---------- | ---------------------------------------- |
| `adastra`               | Static lib | Core: utils, crypto, core, network, etc. |
| `softadastra`           | Static lib | Ecosystem logic (chat, shop, pay, etc.)  |
| `softadastra_main`      | Executable | Main HTTP API (Crow)                     |
| `softadastra_tests`     | Executable | Integration tests (GoogleTest)           |
| `softadastra_unittests` | Executable | Unit tests (GoogleTest / Catch2)         |

---

## ⚙️ Build Instructions

### 🧪 Development build (with tests)

```bash
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make -j

```

🚀 Production build (without tests)
mkdir build && cd build
cmake .. -DBUILD_TESTS=OFF -DENABLE_OPTIMIZATION=ON
make -j

---

🧪 Optional CMake flags
-DENABLE_OPTIMIZATION=ON → Enables -O3 optimizations

-DENABLE_SANITIZERS=ON → Enables address/UB sanitizers (-fsanitize)

-DENABLE_CATCH2=ON → Enables Catch2 support

🧪 Running Tests

# Unit tests

./bin/softadastra_unittests

# Integration tests

./bin/softadastra_tests

# With CTest

ctest --output-on-failure

## 📥 Modules Softadastra inclus

| Module     | Description                      |
| ---------- | -------------------------------- |
| `box`      | Decentralized P2P storage        |
| `commerce` | E-commerce features              |
| `pay`      | Payment system, wallet, security |
| `chat`     | Real-time messaging system       |
| `map`      | Maps and geolocation tools       |
| `pme`      | Tools for small businesses       |
| `rh`       | User and permission management   |

---

## 🧱 Dependencies

- [nlohmann/json](https://github.com/nlohmann/json)
  Crow (local) (header-only, no Boost)(https://github.com/CrowCpp/crow)
- [GoogleTest](https://github.com/google/googletest)
- [Catch2 (optionnel)](https://github.com/catchorg/Catch2)
  ASIO standalone (https://think-async.com/Asio/)
- SQLite3, OpenSSL, Threads, MySQL Connector/C++

---

## 🛠 Development workflow

Use the provided `Makefile` for Git operations and testing:

make help # List available commands
make commit # Commit changes
make push # Push to dev
make release # Full release: commit + merge + tag

## 🔖 Versions

This project follows [Semantic Versioning](https://semver.org/lang/fr/).
See [CHANGELOG.md](./CHANGELOG.md) pour voir l’historique.

---

## 🧑‍💻 Author

**Softadastra**
https://softadastra.com
© 2025. All rights reserved.

---

## 📄 License

MIT or Softadastra-specific license (to be defined in LICENSE).

```

```

```

```
