# 🤝 Contributing to Softadastra

Welcome to the **Softadastra** project!  
We are thrilled that you want to contribute to this modular, high-performance, decentralized C++ ecosystem.

---

## 🔧 Development Environment

### Requirements

- CMake ≥ 3.16
- C++17
- GCC or Clang
- Git
- SQLite3
- MySQL (libmysqlclient / mysqlcppconn)
- OpenSSL
- Crow (local version included in `Crow/include`)

---

## ⚙️ Build the Project

```bash
# Clone the project
git clone https://github.com/softadastra-group/softadastra_backend.git
cd adastra_lib

# Development build
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make -j
./run.sh
```

---

## 🧪 Run Tests

```bash
# Unit tests (Catch2 or GoogleTest)
./bin/softadastra_unittests

# Integration tests
./bin/softadastra_tests

# Or via CTest
ctest --output-on-failure
```

---

## 🧱 Recommended Structure

- Each new module must go into `lib/softadastra/<module_name>/`
- Public headers should be placed in `include/softadastra/<module_name>/`
- Tests must be added in:
  - `unittests/` for internal logic
  - `test/` for routes/API

---

## 🗂️ Code Conventions

- Use `camelCase` for functions and variables
- Use `PascalCase` for classes
- All modules must be inside the namespace `softadastra::<module>`
- Debug logs should use `std::cout`, not `printf`
- Each `.cpp` file should have an associated `.hpp` if appropriate

---

## 🧑‍💻 Git Guidelines

- Create a branch from `main`
- Branch name: `feature/<name>` or `fix/<bug>`
- Use clear commits: `feat: add shop manager`, `fix: crash when no DB`, etc.
- Always use **pull requests**, even for small changes

---

## 🔍 Pull Request Checklist

- [ ] Code compiles successfully
- [ ] Tests pass (`ctest`)
- [ ] No unnecessary includes or missing headers
- [ ] No global `using namespace`
- [ ] Documentation or comments added if needed
- [ ] Commit messages are clear

---

## 📢 Discussions & Contact

- Internal Slack (or Discord)
- Email: dev@softadastra.com
- GitHub issues for bugs or suggestions

---

## 🙏 Thank You!

All contributions are welcome — whether it's a minor documentation fix or a complete new module.

**Softadastra** — Building the digital infrastructure of tomorrow for Africa.
