# 🧪 Unit Tests — `unittests/`

This directory contains unit tests for the `adastra_lib` library, organized by module (`utils`, `crypto`, `tools`, etc.).

## ✅ Purpose

Automatically validate the correct behavior of each library component using **GoogleTest** (and optionally **Catch2**).

---

## 📦 Dependencies

- [GoogleTest](https://github.com/google/googletest) (automatically included if `BUILD_TESTS=ON`)
- [Catch2](https://github.com/catchorg/Catch2) (optional, enabled with `ENABLE_CATCH2=ON`)

---

## ⚙️ Compilation

From the root of `adastra_lib`, use CMake to compile the tests:

```bash
mkdir -p build && cd build
cmake .. -DBUILD_TESTS=ON -DENABLE_CATCH2=OFF # or ON to enable Catch2
make
```

---

## 🚀 Running the tests

After compilation, run all tests with:

```bash
./bin/adastra_unittests
```

Or with CTest (integrated with CMake):

```bash
ctest --output-on-failure
```

---

## 🧩 Adding a Test

Create a new file in `unittests/<module>/`, for example:

Minimal example with GoogleTest:

```cpp
#include <gtest/gtest.h>
#include <adastra/utils/string/CaseConverter.hpp> // Example

TEST(StringUtils, ToUppercase) {
    std::string input = "softadastra";
    std::string result = adastra::to_upper(input);
    EXPECT_EQ(result, "SOFTADASTRA");
}
```

The file will automatically be detected and compiled by CMake (via `file(GLOB_RECURSE)`).

---

## 🗂 Recommended Structure

```
unittests/
├── utils/
│   └── test_string.cpp
├── crypto/
│   └── test_hash.cpp
├── tools/
│   └── test_logger.cpp
```

---

## 📌 Notes

- Each test must be isolated, clear, and reusable.
- You can mix GoogleTest and Catch2 tests (if `ENABLE_CATCH2=ON`), but prefer a single framework per test file.
- The generated binary is `bin/adastra_unittests`.

---

## 📞 Need Help?

Contact the project team or check documentation in `docs/` (coming soon).
